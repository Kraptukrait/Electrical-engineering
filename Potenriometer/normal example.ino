int potentiometer = A0;

void setup() {
  Serial.begin(9600);
  pinMode(potentiometer, INPUT);
}

void loop() {
  int potiread = analogRead(potentiometer);
  int setmap = map(potiread, 0, 1023, 0, 30);  
  Serial.println(setmap);
  //Serial.println(analogRead(potentiometer)); // normal print from analogRead
  delay(1000);
}
