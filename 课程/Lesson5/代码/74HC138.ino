/*
   运行该代码，先修改文件名为合法的变量名。

   3-8译码器实验。

   1 tab = 2 space
 */

int CA0 = 2;
int CA1 = 3;
int CA2 = 4;

void setup ()
{
  pinMode(CA0,OUTPUT);
  pinMode(CA1,OUTPUT);
  pinMode(CA2,OUTPUT);
}

void loop()
{
    // 输出 1，即 Y1 输出低电平
    digitalWrite(CA2,LOW);
    digitalWrite(CA1,LOW);
    digitalWrite(CA0,HIGH);
    delay(1000);
}
