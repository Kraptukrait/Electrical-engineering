#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

String licensePlate;
String licensePlateList[10];
int counter = 0;

WiFiClient wifi;
MqttClient mqtt(wifi);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  // Replace with your WiFi credentials
  WiFi.begin("YOUR_WIFI_NAME", "YOUR_WIFI_PASSWORD");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");

  // Replace with your MQTT broker IP and port
  if (!mqtt.connect("BROKER_IP_ADDRESS", 1883)) {
    Serial.println("MQTT connection failed!");
  } else {
    Serial.println("MQTT connected!");
    mqtt.subscribe("autos/#");
  }
}

void loop() {

  if (!mqtt.connected()) {
    Serial.println("Reconnecting MQTT...");
    mqtt.connect("BROKER_IP_ADDRESS", 1883);
    mqtt.subscribe("autos/#");
  }

  mqtt.poll();
  while (mqtt.parseMessage()) {
    licensePlate = "";
    while (mqtt.available()) {
      licensePlate += (char)mqtt.read();
    }

    Serial.print("Received: ");
    Serial.println(licensePlate);

    if (counter < 10) {
      licensePlateList[counter] = licensePlate;
      counter++;
    }

    /*
    Serial.println("Stored license plates:");
    for (int i = 0; i < counter; i++) {
      Serial.println(licensePlateList[i]);
    }
    Serial.println("-------------------");
    */
  }
}
