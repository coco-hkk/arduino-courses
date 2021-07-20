/*
 *
 *  arduino 串口相关。
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include "arduino.h"
#include "../common/soft_serial.h"

SoftwareSerial arduinoSerial(SERIAL_RX,SERIAL_TX);

void arduino_serial_init() {
  arduinoSerial.begin(9600);
}

void esp8266_reset_arduino() {
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  doc["src"] = ESP8266_DEV;
  doc["dst"] = ARDUINO_DEV;
  doc["id"] = ESP8266_RESET_UNO_MSG;
  doc["uno_reset"] = 1;
  serializeJson(doc, arduinoSerial);
}

void arduino_send_sensor_data(const mcu_msg& data)
{
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  doc["src"] = ARDUINO_DEV;
  doc["dst"] = ESP8266_DEV;
  doc["id"] = ARDUINO_SENSOR_MSG;
  doc["temperature"] = data.msg.uno_sensor_msg.temperature;
  doc["humidity"] = data.msg.uno_sensor_msg.humidity;
  doc["obstacle_distance"] = data.msg.uno_sensor_msg.obstacle_distance;
  doc["pm25_dust_denisty"] = data.msg.uno_sensor_msg.pm25_dust_denisty;
  doc["mq9_ratio"] = data.msg.uno_sensor_msg.mq9_ratio;
  doc["mq9_alarm"] = data.msg.uno_sensor_msg.mq9_alarm;
  doc["yl69_analog_value"] = data.msg.uno_sensor_msg.yl69_analog_value;
  doc["photoresistor"] = data.msg.uno_sensor_msg.photoresistor;

/*
  Serial.println(data.id);
  Serial.println(data.msg.uno_sensor_msg.temperature);
  Serial.println(data.msg.uno_sensor_msg.humidity);
  Serial.println(data.msg.uno_sensor_msg.obstacle_distance);
  Serial.println(data.msg.uno_sensor_msg.pm25_dust_denisty);
  Serial.println(data.msg.uno_sensor_msg.mq9_ratio);
  Serial.println(data.msg.uno_sensor_msg.mq9_alarm);
  Serial.println(data.msg.uno_sensor_msg.yl69_analog_value);
  Serial.println(data.msg.uno_sensor_msg.photoresistor);
*/
  serializeJson(doc, arduinoSerial);
}

void read_serial_data(mcu_msg& data)
{
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  DeserializationError error = deserializeJson(doc, arduinoSerial);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  data.src                           = doc["src"];
  data.dst                           = doc["dst"];

  if (ARDUINO_DEV != data.dst && ANY_DEV != data.dst)
      return;

  data.id                            = doc["id"];

  switch(data.id) {
    case ESP8266_RESET_UNO_MSG:
      break;
  }
}
