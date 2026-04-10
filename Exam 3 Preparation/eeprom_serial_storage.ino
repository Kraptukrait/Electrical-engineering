#include "EEPROM.h"

String input;
int number;
int memoryAddress = 0;
int memoryReadAddress = 0;
int output;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    input = Serial.readString();
    number = input.toInt();
    Serial.println(number);

    EEPROM.put(memoryAddress, number);
    memoryAddress += sizeof(number);

    delay(2000);

    EEPROM.get(memoryReadAddress, output);
    Serial.println(output);
    memoryReadAddress += sizeof(output);
  }
}
