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

SoftwareSerial nodemcuSerial(D5,D6);    //第一个参数D5是接收端口，第二个参数D6是发送端口
 
void setup()
{
  Serial.begin(115200);
  while (!Serial) continue;
    
  nodemcuSerial.begin(9600); 
}
 
void loop() {
  StaticJsonDocument<200> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, nodemcuSerial);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  
  JsonObject root = doc.as<JsonObject>(); // get the root object
  
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed。");
  
  Serial.println();
  Serial.print("a ");
  Serial.println((int)root["a"]);   //类型要和在 arduino 文件中定义的一致。所以这里强制转换类型。
  Serial.print("b ");
  Serial.println((int)root["b"]);
  Serial.println("end.");
}
