void setup()
{
  pinMode(1, OUTPUT);
  TCCR0A = ((1 << COM0B1) | (1 << WGM00));
  TCCR0B = ((1 << WGM02) | (1 << CS00));
  OCR0A = 159;
  OCR0B = 0;
}
void loop()
{
  int sensorValue = analogRead(A1);
  int dutyCycle = map(sensorValue, 0, 1023, 0, 159);
  OCR0B = dutyCycle;
}
