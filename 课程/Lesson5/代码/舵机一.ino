/*
   运行该代码，先修改文件名为合法的变量名。

   舵机180度转舵实验。

   1 tab = 2 space
 */

#include <Servo.h>

#define D6 6

Servo myservo;          //定义舵机对象，最多可以控制8路舵机
int   pos      = 0;     //用于存储舵机位置的变量

void setup()
{
  myservo.attach(D6);    //舵机控制信号引脚,连接舵机
  Serial.begin(115200);
}

void loop()
{
  for(pos = 0; pos < 180; pos += 1)  //从0度-180度
  {                                  //步进角度1度
    myservo.write(pos);              //输入对应的角度值，舵机会转到此位置

    delay(15);                       //15ms后进入下一个位置
    Serial.println(pos);
  }

  for(pos = 180; pos>=1; pos-=1)     //从180度-0度
  {
    myservo.write(pos);              //输入对应的角度值，舵机会转到此位置

    delay(15);                       //15ms后进入下一个位置
    Serial.println(pos);
  }
}
