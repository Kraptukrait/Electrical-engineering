//int button = 7;

void setup() {
  Serial.begin(9600);

  DDRD &= ~(0b10000000);   // INPUT
  PORTD |= 0b10000000;     // PULLUP
}

void loop() {
  Serial.println((PIND & 0b10000000));
  delay(1000);
}
