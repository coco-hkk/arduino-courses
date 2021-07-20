/*
 *
 *  超声波测距。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */
#include <Arduino.h>

static float distance = 0;
static int _echo_pin, _trig_pin;

void ultrasonicwave_init(int trig_pin, int echo_pin) {
  _trig_pin = trig_pin;
  _echo_pin = echo_pin;

  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);

  digitalWrite(echo_pin, LOW);
  digitalWrite(trig_pin, LOW);
}

void ultrasonicwave_task() {
  long IntervalTime = 0;  //定义一个时间变量

  digitalWrite(_trig_pin, 1);  //置高电平
  delayMicroseconds(15);  //延时15us
  digitalWrite(_trig_pin, 0);  //设为低电平

  IntervalTime = pulseIn(_echo_pin, HIGH); //用自带的函数采样反馈的高电平的宽度，单位us
  distance = IntervalTime / 58.00;     //使用浮点计算出距离，单位cm

  delay(100);                         //延时间隔决定采样的频率，根据实际需要变换参数
}

float get_ultrasonicwave_distance() {
  return distance;
}

void get_ultrasonicwave_distance_print() {
  Serial.print("障碍物距离: ");
  Serial.print(distance);
  Serial.println("cm.");
}
