/*
  运行该代码，先修改文件名为合法的变量名。
  
  模拟红绿灯实验。
  
  1 tab = 2 space
*/

#define D5 5
#define D6 6
#define D7 7

int Pins[] = { D5, D6, D7 }; //红，黄，绿

int flag = 1;

void setup() {
  
  for (int i = 0; i < 3; i++)
  {
    pinMode(Pins[i], OUTPUT);
    digitalWrite(Pins[i], LOW);
  }
}

void loop() {
  if (1 == flag)
  {
    digitalWrite(Pins[0], HIGH);    //红灯亮
    delay(5000);

    flag = 0;
  }
  else
  {
    digitalWrite(Pins[2], HIGH);    //绿灯亮
    delay(5000);

    flag = 1;
  }

  //红灯灭
  digitalWrite(Pins[0], LOW);
 
  digitalWrite(Pins[2], LOW);     //绿灯灭

  digitalWrite(Pins[1], HIGH);    //黄灯亮
 
  delay(3000);

  digitalWrite(Pins[1], LOW);     //黄灯灭
}
