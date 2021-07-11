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
 
/* arduino serial settings, port 2 for RX, port 3 for TX*/
SoftwareSerial arduinoSerial(2,3);

void setup() 
{
  /*set baudrate，最好设置为9600*/
  arduinoSerial.begin(9600);
}

void loop() 
{
  /*allocate a static buffer, 200byte size*/
  StaticJsonDocument<200> doc;
  
  // convert it to a JsonObject
  JsonObject root = doc.to<JsonObject>();

  /* 
   *  dict, key => value 
   *  {"a": 1, "b": 2}
   */
  root["a"] = 1;
  root["b"] = 2;

  /*send data through arduinoSerial*/
  serializeJson(doc, arduinoSerial);
}
