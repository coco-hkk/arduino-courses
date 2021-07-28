/*
 *
 *  校准 MQ-9 气体传感器。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>

static float R0;  // R0 in 1000 ppm LPG

void mq9_calibration(int analog_pin) {
  float sensor_volt;
  float RS_air;         //  Rs in clean air
  float sensorValue = 0;

  Serial.println("开始校准 MQ-9 传感器……");
  //取100次传感器数据，求均值
  for(int x = 0 ; x < 100 ; x++)
  {
    sensorValue = sensorValue + analogRead(analog_pin);
  }
  sensorValue = sensorValue/100.0;

  sensor_volt = (sensorValue/1024)*5.0;         // +5V 电压
  RS_air = (5.0-sensor_volt) / sensor_volt;       // Depend on RL on yor module
  R0 = RS_air/9.9;                              // According to MQ9 datasheet table

  Serial.print("R0 = ");
  Serial.println(R0);
}

float get_mq9_R0() {
  return R0;
}
