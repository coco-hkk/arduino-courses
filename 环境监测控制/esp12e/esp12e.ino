/*
 * nodemcu 模块，连接 adafruit 服务器并且发送传感器采集数据。
 *
 * 1 tab = 2 space
 */

#include "src/esp12e/esp12e.h"
#include "src/iot/iot.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  iot_init();
}

void loop()
{
  iot_task();
}
