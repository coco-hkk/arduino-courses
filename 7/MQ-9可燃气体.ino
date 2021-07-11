/*
  运行该代码，先修改文件名为合法的变量名。
  
  MQ-9可燃气体实验。
  
  1 tab = 2 space
*/

#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13

void setup() 
{ 
  Serial.begin(115200);
}

void loop() 
{
  int val;
  val = analogRead(A0);
  Serial.println(val ,DEC);
  delay(100);
}
