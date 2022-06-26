/*
   运行该代码，先修改文件名为合法的变量名。

   Arduino Uno 和 NodeMCU ESP8266 之间的串口通信实验。
   serialize.

   1 tab = 2 space
 */

/* ArduinoJson 5.13.5, from arduino IDE libraries manager
 * https://arduinojson.org/v6/example/
 */
#include <ArduinoJson.h>

/* arduino built-in library*/
#include <SoftwareSerial.h>

/*digital pins 10 and 11 on your Arduino boards are used as virtual RX and TX serial lines*/
SoftwareSerial arduinoSerial(10,11);      // 第一个参数10是接收端口，第二个参数11是发送端口

/*发送和接收消息结构体保持一致*/
typedef struct {
  char name[32];
  int time;
  float value;
} sensor_data_send_json;

/*发送串口数据*/
void writeSensorData(const sensor_data_send_json& data, Stream& output)
{
  const size_t capacity = JSON_OBJECT_SIZE(3);
  StaticJsonDocument<capacity> doc;

  doc["name"] = data.name;
  doc["time"] = data.time;
  doc["value"] = data.value;

  serializeJson(doc, output);
}

void setup()
{
  /*set baudrate，最好设置为9600*/
  arduinoSerial.begin(9600);
}

void loop()
{
  /*
   *  JSON 格式。元素为键值对。格式-> 键:值 => key: value
   *  {"name": "hkk", "time": 2, "value": 1.5}
   */

  sensor_data_send_json sensordata;

  strlcpy(sensordata.name, "hkk", sizeof(sensordata.name));
  sensordata.time = 2;
  sensordata.value = 1.5;

  writeSensorData(sensordata, arduinoSerial);
}
