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

#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#include <Servo.h>

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);

/////// please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;  
char pass[] = SECRET_PASS;  

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
Servo myservo;

const char broker[] = "BROKER_IP_ADDRESS";
int port = 1883;
const char topicPoti[] = "Pablo/Poti";
const char topicParkhaus[] = "Pablo/ParkingGarage";

const long interval = 3000;
const long interval200 = 200;
unsigned long previousMillis = 0;
unsigned long previousMillis200 = 0;

int poti = A0;
int potiValue;
int mappedValue;
int potiMqtt;
int buttonEntrance = 3;
int buttonEntranceClose = 4;
int ledEntrance = 7;
bool entrancePressed = false;
int entranceCounter;
int entranceMqtt;
int entranceMqttSteve;
bool entranceRead = false;
int maxParkingSpaces = 5;
int freeParkingSpaces;
int buttonExit = 2;
bool exitPressed = false;

void setup() {
  pinMode(poti, INPUT);
  pinMode(buttonEntrance, INPUT_PULLUP);
  pinMode(buttonEntranceClose, INPUT_PULLUP);
  pinMode(ledEntrance, OUTPUT);
  pinMode(buttonExit, INPUT_PULLUP);

  myservo.attach(9);
  myservo.write(0);

  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect (needed for native USB)
  }

  // attempt to connect to WiFi network:
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

  mqttClient.subscribe(topicPoti);
  mqttClient.subscribe(topicParkhaus);
  mqttClient.subscribe("Steve/ParkingGarage");

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  // Send the initial number of free parking spaces once via MQTT
  mqttClient.beginMessage(topicParkhaus);
  mqttClient.print(maxParkingSpaces);
  mqttClient.endMessage();
}

void loop() {
  mqttClient.poll();
  unsigned long currentMillis = millis();
  unsigned long currentMillis200 = millis();

  if (digitalRead(buttonEntrance) == 0 && entranceCounter < maxParkingSpaces) {
    entrancePressed = true;
    digitalWrite(ledEntrance, HIGH);
  } else if (digitalRead(buttonExit) == 0) {
    if (currentMillis200 - previousMillis200 >= interval200) {
      previousMillis200 = currentMillis200;
      exitPressed = true;
    }
  }

  // Possible issue: double reading during an open barrier phase
  if (entrancePressed == true) {
    if (Serial.available() > 0) {
      String input = Serial.readString();
      Serial.print("Keyboard input: ");
      Serial.println(input);
      myservo.write(90);
      entranceRead = true;
    }
    if (digitalRead(buttonEntranceClose) == 0 && entranceRead == true) {
      entrancePressed = false;
      entranceRead = false;
      digitalWrite(ledEntrance, LOW);
      myservo.write(0);
      entranceCounter += 1;
      freeParkingSpaces = (maxParkingSpaces - entranceCounter);
      Serial.print("Free spaces left: ");
      Serial.println(freeParkingSpaces);
      mqttClient.beginMessage(topicParkhaus);
      mqttClient.print(freeParkingSpaces);
      mqttClient.endMessage();
    }
  } else if (exitPressed == true) {
    if (entranceCounter > 0) {
      entranceCounter -= 1;
      freeParkingSpaces = (maxParkingSpaces - entranceCounter);
      Serial.print("Free spaces left: ");
      Serial.println(freeParkingSpaces);
      mqttClient.beginMessage(topicParkhaus);
      mqttClient.print(freeParkingSpaces);
      mqttClient.endMessage();
      exitPressed = false;
    }
  }

  // Every 3 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    potiValue = analogRead(poti);
    mappedValue = map(potiValue, 0, 1023, 0, 10);
    mqttClient.beginMessage(topicPoti);
    mqttClient.print(mappedValue);
    mqttClient.endMessage();
  }

  // Read own potentiometer value from MQTT
  if (mqttClient.messageTopic().equals("Pablo/Poti")) {
    String message = "";
    while (mqttClient.available()) {
      char c = (char)mqttClient.read();
      message += c;
    }
    potiMqtt = message.toInt();
  } else if (mqttClient.messageTopic().equals("Pablo/ParkingGarage")) {
    String message = "";
    while (mqttClient.available()) {
      char c = (char)mqttClient.read();
      message += c;
    }
    entranceMqtt = message.toInt();
  } else if (mqttClient.messageTopic().equals("Steve/ParkingGarage")) {
    String message = "";
    while (mqttClient.available()) {
      char c = (char)mqttClient.read();
      message += c;
    }
    entranceMqttSteve = message.toInt();
  }

  u8x8.setCursor(0, 0);
  u8x8.print("Poti = ");
  u8x8.print(potiMqtt);
  u8x8.setCursor(0, 1);
  u8x8.print("Entrance = ");
  u8x8.print(entranceMqtt);
  u8x8.setCursor(0, 2);
  u8x8.print("Steve = ");
  u8x8.print(entranceMqttSteve);
}
