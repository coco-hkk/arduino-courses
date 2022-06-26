/*
 * nodemcu 模块，连接 adafruit 服务器并且发送传感器采集数据。
 *
 * 1 tab = 2 space
 */

#include "src/esp12e/esp12e.h"
#include "src/iot/iot.h"
#include "src/lcd/lcd.h"
#include "src/led/led.h"

void setup() {
  Serial.begin(115200);
  esp12e_serial_init();

  led_init(LED_PIN);

  lcd_init();

  iot_init();
  Serial.println("初始化完成");
}

void loop()
{
  read_serial_data();

  iot_task();

  lcd_task();
}
