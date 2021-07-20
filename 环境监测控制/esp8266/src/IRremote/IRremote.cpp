/*
 *
 *  红外遥控模块。
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>
#include <IRremote.h>
#include "../esp8266/esp8266.h"

IRrecv irrecv(IR_REMOTE);

decode_results results;

void IRremote_init()
{
  irrecv.enableIRIn();                    // Start the receiver
}

void ESP8266_reboot() {
  ESP.restart();    //软重启，硬重启 ESP.reset()
}

void IRremote_task() {
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);

    if (results.value == 0xFF30CF)        //1关灯
    {
      Serial.println("重启 ESP8266 服务器……");
      ESP8266_reboot();
    }
    else if (results.value == 0xFF18E7)   //2开灯
    {
      Serial.println("重启 Arduino UNO 采集数据端……");
      esp8266_reset_arduino();
    }
    irrecv.resume();                      // Receive the next value
  }
  delay(100);
}
