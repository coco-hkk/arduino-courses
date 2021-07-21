/*
 *
 *  土壤湿度模块，获取模拟值。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>

static int YL69_D0 = 0;
static float YL69_A0 = 0.0;

static int _d0_pin,_a0_pin;
/*
 *  @func : 初始化YL69模块。
 */
void YL69_init(int d0_pin, int a0_pin) {
  _d0_pin = d0_pin;
  _a0_pin = a0_pin;
  pinMode(a0_pin, INPUT);
  pinMode(d0_pin, INPUT);
}

int get_YL69_D0_value() {
  YL69_D0 = analogRead(_d0_pin);

  return YL69_D0;
}

float get_YL69_A0_value() {
  YL69_D0 = analogRead(_a0_pin);

  return YL69_A0;
}

void get_YL69_print() {
  Serial.print("YL69 AO = ");
  Serial.print(YL69_A0);
  Serial.print(",YL69 DO = ");
  Serial.println(YL69_D0);
}
