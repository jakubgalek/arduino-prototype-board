int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int switchPin = 7;
int speed = 10; // Default speed value (can be set from 1 to 10)

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop()
{
  boolean reverse = digitalRead(switchPin);
  setMotor(speed, reverse);
}

void setMotor(int speed, boolean reverse)
{
  analogWrite(enablePin, map(speed, 1, 10, 0, 255));
  digitalWrite(in1Pin, !reverse);
  digitalWrite(in2Pin, reverse);
}
