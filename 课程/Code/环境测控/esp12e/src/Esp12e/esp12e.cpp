/*
 *
 *  esp12e 串口相关。
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
  delay(5);
}

void read_serial_data()
{
  mcu_msg data;

  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;
    
  esp12eSerial.setTimeout(10000);

  //Serial.print((char)client.read());
  //DeserializationError error = deserializeJson(doc, esp12eSerial);
  //ReadLoggingStream loggingStream(esp12eSerial, Serial);
  ReadBufferingStream bufferingStream(esp12eSerial, 64);
  DeserializationError error = deserializeJson(doc, bufferingStream);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    delay(5);
    return;
  }

  memset(&data, 0x00, sizeof(mcu_msg));

  data.src                           = doc["src"];
  data.dst                           = doc["dst"];

  if (ESP_12E_DEV != data.dst && ANY_DEV != data.dst)
      return;

  data.id                            = doc["id"];

  Serial.println(data.id);

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

      Serial.println(data.msg.uno_sensor_msg.temperature);
      Serial.println(data.msg.uno_sensor_msg.humidity);
      Serial.println(data.msg.uno_sensor_msg.obstacle_distance);
      Serial.println(data.msg.uno_sensor_msg.pm25_dust_denisty);
      Serial.println(data.msg.uno_sensor_msg.mq9_ratio);
      Serial.println(data.msg.uno_sensor_msg.mq9_alarm);
      Serial.println(data.msg.uno_sensor_msg.yl69_analog_value);
      Serial.println(data.msg.uno_sensor_msg.photoresistor);

      get_sensor_data(data);

      break;
  }
}
