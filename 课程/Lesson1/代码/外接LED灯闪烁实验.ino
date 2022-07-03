/*
   运行该代码，先修改文件名为合法的变量名。

   LED灯闪烁实验。

   1 tab = 2 space
 */

const int ledPin = 10;              //定义变量，这里表示外接LED将使用 Arduino 的数字端口

void setup()
{
  pinMode(ledPin, OUTPUT);          //初始化端口为输出模式，还可以初始化为输入模式INPUT和上拉模式INPUT_PULLUP
}

void loop()
{
  digitalWrite(ledPin, HIGH);       //点亮小灯，使用 digitalWrite 操纵数字端口的输出电平，数字端口10输出高电平，即5v电压
  delay(1000);                      //程序阻塞1000ms，即1s，相当于LED亮了1秒。

  digitalWrite(ledPin, LOW);        //熄灭小灯，数字端口输出低电平，即输出0v
  delay(1000);
}
