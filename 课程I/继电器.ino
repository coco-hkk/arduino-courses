int RelayPin = 8;

void setup()
{
  pinMode(RelayPin, OUTPUT);
}

void loop()
{
  digitalWrite(RelayPin, HIGH);
  delay(1000);
  digitalWrite(RelayPin, LOW);
  delay(1000);
}
