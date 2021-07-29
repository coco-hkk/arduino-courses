/*
   运行该代码，先修改文件名为合法的变量名。

   服务器发布数据实验。

   1 tab = 2 space
 */

//温湿度库对应的头文件
#include <dht11.h>

//网络服务所需头文件
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define D4       2
#define DHT11PIN D4

//设置AP的SSID和密码
const char *ssid     = "DHT11";
const char *password = "12345678";

//全局对象，用提供web服务
ESP8266WebServer server(80);

//全局对象，用于获取温湿度
dht11 DHT11;

//获取湿度
float getHumidity(){
  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.humidity;
}

//获取温度
float getTemperature(){
  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.temperature;
}

//访问http://192.168.4.1会看到的内容
void handleRoot() {
  float h    = getHumidity();
  float t    = getTemperature();
  String str = R"===(
        <html>
          <head>
            <meta charset="utf-8" http-equiv="Refresh" content="1"/>
            <title>ESP-12E试验</title>
          </head>
          <body>
            <h1>当前湿度(%):
            )===";

  str += String(h);
  str += "<br>当前温度(℃):";
  str += String(t);
  str += "</h1></body></html>";

  server.send(200, "text/html", str);
}

void setup() {
  Serial.begin(115200);

  delay(1000);
  Serial.println();
  Serial.println("Configuring access point...");

  //启动AP热点
  WiFi.softAP(ssid, password);

  //显示热点信息
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  //绑定HTTP服务器/目录下所发布的信息，并启动服务
  server.on("/", handleRoot);
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
