/*
 *
 *  MQ-9 可燃气传感器。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>
#include "mq9.h"

static float ratio;
static int _d0_pin;

void mq9_init(int d0_pin) {
  _d0_pin = d0_pin;
  pinMode(d0_pin, INPUT);
}

void mq9_task(int analog_pin, float R0) {
  float sensor_volt;
  float RS_gas;

  int sensorValue = analogRead(analog_pin);
  sensor_volt = ((float)sensorValue / 1024) * 5.0;
  RS_gas = (5.0 - sensor_volt) / sensor_volt; // Depend on RL on yor module


  ratio = RS_gas / R0; // ratio = RS/R0

  Serial.print("MQ9 sensor_volt = ");
  Serial.print(sensor_volt);
  Serial.print("V, ");
  Serial.print("RS_gas = ");
  Serial.print(RS_gas);
  Serial.print(", Rs/R0 = ");
  Serial.println(ratio);
}

int is_mq9_alarm() {
  return digitalRead(_d0_pin);
}

float get_mq9_rs_r0_ratio() {
    return ratio;
}
