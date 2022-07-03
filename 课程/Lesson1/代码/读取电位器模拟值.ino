/*
   运行该代码，先修改文件名为合法的变量名。

   读取电位器值实验

   1 tab = 2 space
 */

int potpin = 0;                 //使用模拟端口0
int val    = 0;                 //存储从A0获取的模拟值

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  val = analogRead(potpin);     //读取模拟端口 A0 的值，值得范围为 0~1023
  Serial.println(val);          //使用串口监视器显示电位器的值
}
