/*
   运行该代码，先修改文件名为合法的变量名。

   跑马灯实验

   1 tab = 2 space
 */

int LED[] = {9,10,11};

void setup() {
  for(int i = 0;i <= 3;i++)
  {
    pinMode(LED[i],OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 3; i++)
  {
    //给引脚写入低电平
    digitalWrite(LED[i], LOW);

    //延迟1000毫秒
    delay(1000);

    //给引脚写入高电平
    digitalWrite(LED[i], HIGH);
  }
}
