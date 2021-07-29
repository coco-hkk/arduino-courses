/*
 * Arduino Uno 和 NodeMCU ESP8266 之间的串口通信
 */

/* ArduinoJson 5.13.5, from arduino IDE libraries manager
 * https://arduinojson.org/v5/example/
 */
#include <ArduinoJson.h>

/* arduino built-in library*/
#include <SoftwareSerial.h>

/* arduino serial settings, port 2 for RX, port 3 for TX*/
SoftwareSerial arduinoSerial(2,3);

void setup()
{
  /*set baudrate*/
  arduinoSerial.begin(9600);
}

void loop()
{
  /*malloc a static buffer, 200byte size*/
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  /*
   *  dict, key => value
   *  {"a": 1, "b": 2}
   */
  root["a"] = 1;
  root["b"] = 2;

  /*send data through arduinoSerial*/
  root.printTo(arduinoSerial);
}
