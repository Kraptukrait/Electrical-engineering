#include <Stepper.h>

const int stepsPerRevolution = 2048;
const int rolePerMinute = 15;  // 0 -> 17
volatile bool step = false;


Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  TCCR1A = 0;
  TCCR1B = 0b00001100;
  TIMSK1 = 0b00000010;
  OCR1A = 62500; // -> 1 * 16000000 / 256 = 62500

  myStepper.setSpeed(rolePerMinute);
}

void loop() {
  if (step == true) {
    step = false;
    myStepper.step(204);
  }
}

ISR(TIMER1_COMPA_vect) {
  step = true;
}
