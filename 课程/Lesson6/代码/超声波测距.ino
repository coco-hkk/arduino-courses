/*
   运行该代码，先修改文件名为合法的变量名。

   超声波测距点亮LED 实验

   1 tab = 2 space
 */

const int trig = 12;    // 触发信号
const int echo = 11;    // 反馈信号
int   LedPin   = 10;    //小灯

void setup()
{
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);

  pinMode(LedPin, OUTPUT);
  Serial.begin(115200);

  digitalWrite(echo, LOW);
  digitalWrite(trig, LOW);
}

void loop()
{
  long  IntervalTime = 0;                   //定义一个时间变量
  float distance     = 0;

  digitalWrite(trig, HIGH);                 //置高电平
  delayMicroseconds(15);                    //延时15us
  digitalWrite(trig, LOW);                  //设为低电平

  IntervalTime = pulseIn(echo, HIGH);       //用自带的函数采样反馈的高电平的宽度，单位us
  float distance = IntervalTime * 0.017;    //使用浮点计算出距离，单位cm
  Serial.println(distance);                 //通过串口输出距离数值

  if(distance < 20.00)
  {
    delay(10);
    digitalWrite(LedPin, HIGH);
  }
  else
  {
    delay(10);
    digitalWrite(LedPin, LOW);
  }

  delay(500);                               //延时间隔决定采样的频率，根据实际需要变换参数
}
