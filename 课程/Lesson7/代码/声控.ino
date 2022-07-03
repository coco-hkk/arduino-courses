/*
   运行该代码，先修改文件名为合法的变量名。

   声控实验。
   声音模块可以看作是一个声音开关，有声音时传感器上标的D0脚输出1，无声音输出0

   1 tab = 2 space
 */

int sensorpin = 9;                      //声音模块的D0脚，也是数字输出脚，有声音输出1，无声音输出0
int ledPin    = 10;                     //Led灯的引脚

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(sensorpin, INPUT);

  digitalWrite(ledPin,LOW);
  Serial.begin(115200);
}

void loop()
{
  Serial.println(digitalRead(sensorpin));

  if(digitalRead(sensorpin) == HIGH)    //当有声音时，板载LED被点亮5秒
  {
    digitalWrite(ledPin,HIGH);
    delay(5000);
    digitalWrite(ledPin,LOW);
  }
  delay(10);
}
