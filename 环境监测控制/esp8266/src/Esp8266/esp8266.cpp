/*
 *
 *  esp8266 串口相关。
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include "esp8266.h"
#include "../common/soft_serial.h"

#include "../server/server.h"


SoftwareSerial esp8266Serial(ESP8266_RX,ESP8266_TX);

void esp8266_serial_init() {
  esp8266Serial.begin(9600);
}

void esp8266_reset_arduino() {
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  doc["src"] = ESP8266_DEV;
  doc["dst"] = ARDUINO_DEV;
  doc["id"] = ESP8266_RESET_UNO_MSG;
  doc["uno_reset"] = 1;
  serializeJson(doc, esp8266Serial);
}

void read_serial_data(mcu_msg& data)
{
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  DeserializationError error = deserializeJson(doc, esp8266Serial);
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
      data.msg.uno_sensor_msg.temperature       = doc["temperature"];
      data.msg.uno_sensor_msg.humidity          = doc["humidity"];
      data.msg.uno_sensor_msg.obstacle_distance = doc["obstacle_distance"];
      data.msg.uno_sensor_msg.pm25_dust_denisty = doc["pm25_dust_denisty"];
      data.msg.uno_sensor_msg.mq9_ratio         = doc["mq9_ratio"];
      data.msg.uno_sensor_msg.mq9_alarm         = doc["mq9_alarm"];
      data.msg.uno_sensor_msg.yl69_analog_value = doc["yl69_analog_value"];
      data.msg.uno_sensor_msg.photoresistor     = doc["photoresistor"];
      get_sensor_data_from_arduino_uno(data);
      break;
  }
}
