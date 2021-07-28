/* 
 * Arduino Uno 和 NodeMCU ESP8266 之间的串口通信
 */
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

/* map D5,D6 and gpio12,gpio14*/
#define D6  12
#define D5  14

SoftwareSerial nodemcuSerial(D6,D5);
 
void setup()
{
  Serial.begin(115200);
  nodemcuSerial.begin(9600); 
  while (!Serial) continue;
}
 
void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(nodemcuSerial); /* parse message from nodemcuSerial */
  
  if (root == JsonObject::invalid())
  {
    return;
  }
  
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  
  Serial.println("");
  Serial.print("a ");
  int data1=root["a"];
  Serial.println(data1);
  Serial.print("b ");
  int data2=root["b"];
  Serial.println(data2);
  Serial.println("---------------------xxxxx--------------------");
}
