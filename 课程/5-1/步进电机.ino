/*
   运行该代码，先修改文件名为合法的变量名。

   电位器控制步进电机 实验

   1 tab = 2 space
 */

#include <Stepper.h>

#define STEPS 60        //这里设置步进电机旋转一圈是多少步

//定义引脚的连接
Stepper stepper(STEPS, 8, 9, 10, 11);   // IN1=8, IN2=10, IN3=9, IN4=11

//上一次的读取模拟量
int previous = 0;

//初始化电机转动速度
void setup()
{
  stepper.setSpeed(60);      // 初始化电机速度，单位min，rpm
}

void loop()
{
  //获取传感器参数
  int val = analogRead(A0);

  stepper.step(val - previous);      // 移动步数，正负表示方向相反

  previous = val;
}
