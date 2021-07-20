/*
 *
 *  PM2.5传感器。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>

static int _ledpower_pin;

unsigned int samplingTime = 280; //3脚直接由单片机给脉冲波10ms周期，高电平0.32ms
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float dustDensity = 0;

void pm25_init(int ledpower_pin)
{
  _ledpower_pin = ledpower_pin;
  pinMode(ledpower_pin,OUTPUT);
}

void pm25_task(int measure_pin)
{
  float voMeasured = 0;
  float calcVoltage = 0;
  digitalWrite(_ledpower_pin,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measure_pin);

  delayMicroseconds(deltaTime);
  digitalWrite(_ledpower_pin,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured * 5.0 / 1023.0;
  dustDensity = 0.172 * calcVoltage - 0.1;       //0.172 是采用精确的仪器侦测出来的数值做线性正交所得公式斜率和截距

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }

  Serial.print("PM2.5: Voltage: ");
  Serial.print(calcVoltage);
  Serial.print("V, Dust Density: ");
  Serial.print(dustDensity * 1000);             //默认单位是mg/m3
  Serial.println("ug/m3");
}

float get_pm25_dust_density() {
  return dustDensity * 1000;
}

