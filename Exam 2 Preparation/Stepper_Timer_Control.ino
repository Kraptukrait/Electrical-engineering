#include <Stepper.h>

const int stepsPerRevolution = 2048;  // 2048 steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0–17 rpm
int steps = 204;                      // 2048 / 10 = 204.8
int button = 2;
int potentiometer = A0;
volatile bool alarm = false;
volatile int countStart = 3036;
volatile bool step = false;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  PORTD |= 0b00000100; // pinMode(button, INPUT_PULLUP);
  pinMode(potentiometer, INPUT);
  myStepper.setSpeed(rolePerMinute);
  attachInterrupt(digitalPinToInterrupt(button), buttonStop, FALLING);

  TCCR1A = 0;
  TCCR1B = 0b00000100; // Prescaler of 256 => (16000000 * 1) / 256 = 62500 ; 65536 - 62500 = 3036 -> countStart
  TIMSK1 = 0b00000001;
}

void loop() {
  int potiread = analogRead(potentiometer);
  int setmap = map(potiread, 0, 1023, 8, 17);
  myStepper.setSpeed(setmap);

  while (alarm == true) {} // If the button was pressed, do nothing anymore

  if (step == true) {
    step = false;
    myStepper.step(steps);
  }
}

// Button interrupt
void buttonStop() {
  alarm = true;
}

// Timer1 interrupt
ISR(TIMER1_OVF_vect) {
  step = true;
}
