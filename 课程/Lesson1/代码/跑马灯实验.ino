/*
   运行该代码，先修改文件名为合法的变量名。

   跑马灯实验

   1 tab = 2 space
 */

int LED[] = {9,10,11};                  //定义将使用的Arduino数字端口

void setup() {
  for(int i = 0;i <= 3;i++)
  {
    pinMode(LED[i],OUTPUT);             //初始化数字端口为输出模式
  }
}

void loop() {
  /*
    代码需要和电路匹配，假设电路中LED灯的正极接 +5v，负极接初始化后的数字端口。
  */
  for (int i = 0; i < 3; i++)
  {
    //给端口写入低电平，即该端口输出0v
    digitalWrite(LED[i], LOW);

    //延迟1000毫秒
    delay(1000);

    //给端口写入高电平，即该端口输出5v
    digitalWrite(LED[i], HIGH);
  }
}
