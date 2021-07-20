/*
 *
 *  esp8266 串口相关。
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include "esp12e.h"
#include "../common/soft_serial.h"

SoftwareSerial esp12eSerial(ESP12E_RX,ESP12E_TX);

void esp12e_serial_init() {
  esp12eSerial.begin(9600);
}

void read_serial_data(mcu_msg& data)
{
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  DeserializationError error = deserializeJson(doc, esp12eSerial);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  data.src                           = doc["src"];
  data.dst                           = doc["dst"];

  if (ESP8266_DEV != data.dst && ANY_DEV != data.dst)
      return;

  data.id                            = doc["id"];

  switch(data.id) {
    case ARDUINO_SENSOR_MSG:
      break;
  }
}
