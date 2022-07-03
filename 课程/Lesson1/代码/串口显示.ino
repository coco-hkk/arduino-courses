/*
   运行该代码，先修改文件名为合法的变量名。

   观察串口显示实验

   1 tab = 2 space
 */

void setup()
{
  Serial.begin(115200);              //设置波特率，必须和IDE设置相一致。
}

void loop()
{
  Serial.println("Hello World!");    //输出“Hello World！”字符串
}
