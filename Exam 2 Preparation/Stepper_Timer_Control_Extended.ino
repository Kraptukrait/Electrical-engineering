#include <Stepper.h>

const int stepsPerRevolution = 2048;  // 2048 steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0–17 rpm
int steps = 204;                      // 2048 / 10 = 204.8
int button = 2;
int button2 = 3;
int potentiometer = A0;
int zaehler = 0;
int tempPin = A1;
volatile bool alarm = false;
volatile int countStart = 3036;
volatile bool step = false;
volatile bool durchlauf = false;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  PORTD |= 0b00001100; // pinMode(button, INPUT_PULLUP);
  pinMode(potentiometer, INPUT);
  myStepper.setSpeed(rolePerMinute);
  attachInterrupt(digitalPinToInterrupt(button), buttonStop, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2), buttonStart, FALLING);

  TCCR1A = 0;
  TCCR1B = 0b00000100; // Prescaler 256 => (16000000 * 1) / 256 = 62500
                       // 65536 - 62500 = 3036 -> countStart
  TIMSK1 = 0b00000001;
}

void loop() {
  int potiread = analogRead(potentiometer);
  int setmap = map(potiread, 0, 1023, 6, 17);
  myStepper.setSpeed(setmap);
  
  int tempReading = analogRead(tempPin);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 +
              (0.000234125 +
              (0.0000000876741 * tempK * tempK)) * tempK); // Temperature in Kelvin
  float tempC = tempK - 273.15; // Temperature in Celsius
  Serial.println(tempC);
  delay(1000);

  if (tempC > 34) {
    myStepper.setSpeed(7);
  } else {
    myStepper.setSpeed(setmap);
  }

  if (alarm == true) {
    return;
  }

  if (durchlauf == true) {
    durchlauf = false;
    int test = 2048 - zaehler;
    Serial.println(test);
    myStepper.step(-zaehler); // or insert test
    test = 0;
    zaehler = 0;
  }

  if (step == true) {
    step = false;
    myStepper.step(steps);
    zaehler += 204;
    if (zaehler >= 2048) {
      zaehler = 0;
    }
  }
}

// Button interrupt
void buttonStop() {
  alarm = true;
}

void buttonStart() {
  Serial.println("Start");
  alarm = false;
  durchlauf = true;
}

// Timer1 interrupt
ISR(TIMER1_OVF_vect) {
  step = true;
  TCNT1 = countStart;
}
