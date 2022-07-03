/*
 *
 * 光敏电阻模块，检测光照强度。光照越强，电阻越小。电路可串联 1K-10K 电阻。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>

int Intensity = 0;  //光照度数值

float get_photoresistor_value(int pin) {
  Intensity = analogRead(pin);

  return Intensity;
}

void get_photoresistor_print() {
    Serial.print("光照强度模拟值： ");
    Serial.println(Intensity);
}
