/*
 *
 *  舵机模块
 *
 *  2021/07/20 added by 郝宽宽
 *
 *  1 tab = 2 space
 */
#include <Arduino.h>
#include <Servo.h>

#include "../esp8266/esp8266.h"

Servo myservo;

void servo_init() {
  myservo.attach(SERVO_MOTOR);
}

void servo_control(int angle)
{
  angle = constrain(angle, 0, 180);
  Serial.print("servo turn angle: ");
  Serial.println(angle);
  
  myservo.write(angle);
}
