#define PIN_X 0 //A0,A1,A2
#define PIN_Y 1
#define PIN_Z 2

void setup() {
  pinMode(PIN_X, INPUT);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_Z, INPUT);
  Serial.begin(115200);
}

void loop() {
  int x,y,z;

  x=analogRead(PIN_X);
  y=analogRead(PIN_Y);
  z=analogRead(PIN_Z);

  Serial.print("X = ");
  Serial.println(x);
  Serial.print("Y = ");
  Serial.println(y);
  Serial.print("Z = ");
  Serial.println(z);

  delay(1000);
}
