#include <Stepper.h>

const int stepsPerRevolution = 2048;
const int rolePerMinute = 15;  // 0 -> 17
volatile bool step = false;


Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  TCCR1A = 0;
  TCCR1B = 0b00000100;
  TIMSK1 = 0b00000001;
  TCNT1 = 3035;
  myStepper.setSpeed(rolePerMinute);
}

void loop() {
  if (step == true) {
    step = false;
    myStepper.step(204);
  }
}

ISR(TIMER1_OVF_vect) {
  step = true;
  TCNT1 = 3035;
}
