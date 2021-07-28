/*
 *
 *  RGB三基色LED。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>
#include "led.h"

static int _led_r, _led_g, _led_b;

void rgb_init(int led_r, int led_g, int led_b) {
  _led_r = led_r;
  _led_g = led_g;
  _led_b = led_b;

  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);
}

void rgb_color(unsigned char data_color)
{
  switch (data_color)
  {
    case Color_R:    //青色
      digitalWrite(_led_r, LOW);
      digitalWrite(_led_g, HIGH);
      digitalWrite(_led_b, HIGH);
      break;
    case Color_G:    //紫色
      digitalWrite(_led_r, HIGH);
      digitalWrite(_led_g, LOW);
      digitalWrite(_led_b, HIGH);
      break;
    case Color_B:       //黄色
      digitalWrite(_led_r, HIGH);
      digitalWrite(_led_g, HIGH);
      digitalWrite(_led_b, LOW);
      break;
    case Color_RG:       //蓝色
      digitalWrite(_led_r, LOW);
      digitalWrite(_led_g, LOW);
      digitalWrite(_led_b, HIGH);
      break;
    case Color_RB:       //绿色
      digitalWrite(_led_r, LOW);
      digitalWrite(_led_g, HIGH);
      digitalWrite(_led_b, LOW);
      break;
    case Color_GB:       //红色
      digitalWrite(_led_r, HIGH);
      digitalWrite(_led_g, LOW);
      digitalWrite(_led_b, LOW);
      break;
    case Color_RGB:       //白色
      digitalWrite(_led_r, LOW);
      digitalWrite(_led_g, LOW);
      digitalWrite(_led_b, LOW);
      break;
    default:
      break;
    }
}
