String input;
int number;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    input = Serial.readString();
    number = input.toInt();
    Serial.println(number);
  }
}
