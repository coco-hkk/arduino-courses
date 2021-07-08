/*
  运行该代码，先修改文件名为合法的变量名。
  
  dht温湿度传感器 实验
  
  1 tab = 2 space
*/

#include <dht11.h>

#define DHT11PIN 9

dht11 DHT11;

void setup()
{
  Serial.begin(115200);
  pinMode(DHT11PIN, OUTPUT);
}

void loop()
{
  //读取温湿度的数据
  int chk = DHT11.read(DHT11PIN);

  //温度
  float temp = (float)DHT11.temperature;

  Serial.print("Tep: ");
  Serial.print(temp);
  Serial.println("C");


  //湿度
  float humi = (float)DHT11.humidity;

  Serial.print("Hum: ");
  Serial.print(humi);
  Serial.println("%");

  delay(500);

}
