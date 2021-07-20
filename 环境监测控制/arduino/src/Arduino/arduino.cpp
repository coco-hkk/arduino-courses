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

void arduino_send_sensor_data(const mcu_msg& data)
{
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  doc["src"] = ARDUINO_DEV;
  doc["dst"] = ANY_DEV;
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

void read_serial_data()
{
  mcu_msg data;
  
  const size_t capacity = 1024;
  StaticJsonDocument<capacity> doc;

  DeserializationError error = deserializeJson(doc, arduinoSerial);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  
  memset(&data, 0x00, sizeof(mcu_msg));

  data.src                           = doc["src"];
  data.dst                           = doc["dst"];

  if (ARDUINO_DEV != data.dst && ANY_DEV != data.dst)
      return;

  data.id                            = doc["id"];

  switch(data.id) {
    case ESP8266_RESET_UNO_MSG:
        /*将12脚连接一个1K电阻，然后用电阻另一端连接RESET脚。注意不是12脚直接连接RESET！！*/
        Serial.println("即将重启 Arduino 设备……");
        Serial.println();
        delay(2000);
        pinMode(ARDUINO_RESET, OUTPUT);
        digitalWrite(ARDUINO_RESET, LOW);
      break;
  }
}
