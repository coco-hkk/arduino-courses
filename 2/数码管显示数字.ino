/*
  运行该代码，先修改文件名为合法的变量名。
  
  数码管显示数字实验。
  
  1 tab = 4 space
*/

int a = 2;                //定义数字接口2 连接a 段数码管
int b = 3;                // 定义数字接口3 连接b 段数码管
int c = 4;                // 定义数字接口4 连接c 段数码管
int d = 5;                // 定义数字接口5 连接d 段数码管
int e = 6;                // 定义数字接口6 连接e 段数码管
int f = 7;                // 定义数字接口7 连接f 段数码管
int g = 8;                // 定义数字接口8 连接g 段数码管
int dp = 9;               // 定义数字接口9 连接dp 段数码管

void setup()
{
  int i;                  //定义变量
  
  for(i = 2; i <= 9; i++)
    pinMode(i, OUTPUT);   //设置2～9 引脚为输出模式
}
void loop() 
{
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(dp,HIGH); 
  
  delay(2000);
}
