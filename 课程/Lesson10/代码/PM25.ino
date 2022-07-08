/*
   运行该代码，先修改文件名为合法的变量名。

   PM2.5实验。

   1 tab = 2 space
 */

#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13

int measurePin            = A0;
int ledPower              = D4;

unsigned int samplingTime = 280; //3脚直接由单片机给脉冲波10ms周期，高电平0.32ms
unsigned int deltaTime    = 40;
unsigned int sleepTime    = 9680;

float voMeasured          = 0;
float calcVoltage         = 0;
float dustDensity         = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPower,OUTPUT);
}

void loop()
{
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured * 5.0 / 1024.0;
  dustDensity = 0.172 * calcVoltage - 0.0999;    //0.172 是采用精确的仪器侦测出来的数值做线性正交所得公式斜率和截距

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }

  Serial.println();
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.println(voMeasured);

  Serial.print(" - Voltage: ");
  Serial.println(calcVoltage);

  Serial.print(" - Dust Density: ");
  Serial.print(dustDensity * 1000);             //默认单位是mg/m3
  Serial.println(" mg/m3");

  delay(1000);
}
