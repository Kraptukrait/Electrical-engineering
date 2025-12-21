//int led = 7;

void setup() {
  DDRD = 0b10000000; //pinMode(led, OUTPUT);
}

void loop() {
  PORTD |= 0b10000000; //digitalWrite(led, HIGH);
  delay(1000);
  PORTD &= ~(0b10000000); //digitalWrite(led, LOW);
  delay(1000);
}
