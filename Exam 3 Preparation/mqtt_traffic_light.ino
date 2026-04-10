#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
#include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
#include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_NICLA_VISION) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_GIGA) || defined(ARDUINO_OPTA)
#include <WiFi.h>
#elif defined(ARDUINO_PORTENTA_C33)
#include <WiFiC3.h>
#elif defined(ARDUINO_UNOR4_WIFI)
#include <WiFiS3.h>
#endif

#include "arduino_secrets.h"

/////// please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;  
char pass[] = SECRET_PASS;  

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "BROKER_IP_ADDRESS";
int port = 1883;
const char topic[] = "TrafficLight";

const long interval = 800;
unsigned long previousMillis = 0;

int ledRed = 11;
int ledYellow = 9;
int ledGreen = 10;
int ledBlue = 8;

char c;
String message;

void setup() {
  Serial.begin(9600);

  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  while (!Serial) {
    ; // wait for serial connection
  }

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  mqttClient.subscribe(topic);

  // Send initial state
  mqttClient.beginMessage(topic);
  mqttClient.print("Start");
  mqttClient.endMessage();
}

void loop() {
  mqttClient.poll();

  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    message = "";
    while (mqttClient.available()) {
      c = (char)mqttClient.read();
      message += c;
    }
    Serial.println(message);
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (message.equals("Start")) {
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);

      mqttClient.beginMessage(topic);
      mqttClient.print("Yellow");
      mqttClient.endMessage();

    } else if (message.equals("Yellow")) {
      digitalWrite(ledYellow, HIGH);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);

      mqttClient.beginMessage(topic);
      mqttClient.print("Green");
      mqttClient.endMessage();

    } else if (message.equals("Green")) {
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledBlue, LOW);

      mqttClient.beginMessage(topic);
      mqttClient.print("Blue");
      mqttClient.endMessage();

    } else if (message.equals("Blue")) {
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, LOW);

      mqttClient.beginMessage(topic);
      mqttClient.print("Start");
      mqttClient.endMessage();
    }
  }
}
