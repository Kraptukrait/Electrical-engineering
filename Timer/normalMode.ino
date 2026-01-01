unsigned int counterStart = 3036; 

void setup() {
  DDRD |= 0b10000000;


  TCCR1A = 0;
  TCCR1B = 0b00000100;  // Prescaler: 256
  TIMSK1 = 0b00000001;
  TCNT1 = counterStart;
}

void loop() {}

ISR(TIMER1_OVF_vect) {
  PORTD ^= 0b10000000;
  TCNT1 = counterStart;
}
