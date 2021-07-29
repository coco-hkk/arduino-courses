/*
   运行该代码，先修改文件名为合法的变量名。

   读取电位器值实验

   1 tab = 2 space
 */

int potpin = 0;       //定义模拟接口0
int val    = 0;       //将定义变量val,并赋初值0

void setup()
{
  Serial.begin(115200);       //设置波特率为115200
}

void loop()
{
  val = analogRead(potpin);     //读取模拟接口0 的值，并将其赋给val
  Serial.println(val);        //显示出val 的值
}
