/*
   运行该代码，先修改文件名为合法的变量名。

   LED灯闪烁实验。

   1 tab = 2 space
 */

int ledPin = 10;              //定义数字10 接口

void setup()
{
  pinMode(ledPin, OUTPUT);    //定义小灯接口为输出接口
}

void loop()
{
  digitalWrite(ledPin, HIGH); //点亮小灯
  delay(1000);

  digitalWrite(ledPin, LOW);  //熄灭小灯
  delay(1000);
}
