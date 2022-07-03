/*
 *
 *  led模块。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>

static int _led_pin;

void led_init(int led_pin) {
  _led_pin = led_pin;
  pinMode(led_pin, OUTPUT);
}

void led_write_high() {
  digitalWrite(_led_pin, HIGH);
}

void led_write_low() {
  digitalWrite(_led_pin, LOW);
}
