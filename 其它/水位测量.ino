int sensorPin   = A0;
int ledPin      = 2;
int sensorValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);

  if(sensorValue > 100)
  {
    digitalWrite(ledPin, HIGH);
  }else
  {
    digitalWrite(ledPin, LOW);
  }

  Serial.println(sensorValue);
  delay(1000);
}
