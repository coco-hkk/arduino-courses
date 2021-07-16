/*
   运行该代码，先修改文件名为合法的变量名。

   Arduino Uno 和 NodeMCU ESP8266 之间的串口通信实验。
   Deserialize.

   1 tab = 2 space
 */

#include <ArduinoJson.h>
#include <SoftwareSerial.h>

/* map D5,D6 and gpio12,gpio14*/
#define D6  12
#define D5  14

/*接收和发送消息结构体保持一致*/
typedef struct {
  char name[32];
  int time;
  float value;
} sensor_data_receive_json;

/*定义串口*/
SoftwareSerial nodemcuSerial(D5,D6);    //第一个参数D5是接收端口，第二个参数D6是发送端口

/*获取串口数据*/
void readSensorData(sensor_data_receive_json* data, Stream& input)
{
  const size_t capacity = JSON_OBJECT_SIZE(3) + 32;
  StaticJsonDocument<capacity> doc;

  DeserializationError error = deserializeJson(doc, input);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  strlcpy(data->name, doc["name"] | "N/A", sizeof(data->name));
  data->time = doc["time"];
  data->value = doc["value"];
}

void setup()
{
  Serial.begin(115200);

  nodemcuSerial.begin(9600);
}

void loop() {
  sensor_data_receive_json sensordata_json;

  readSensorData(&sensordata_json, nodemcuSerial);

  Serial.println("JSON received and parsed。");

  /*
   *  从串口获取的数据，内容为JSON格式。解析时要保证和发送端数据类型一致。
   *  JSON 格式。元素为键值对。格式-> 键:值 => key: value
   *  {"name": "hkk", "time": 2, "value": 1.5}
   */
   
  Serial.println();
  Serial.print("name: ");
  Serial.println(sensordata_json.name);
  Serial.print("time: ");
  Serial.println(sensordata_json.time);
  Serial.print("value: ");
  Serial.println(sensordata_json.value);
}
