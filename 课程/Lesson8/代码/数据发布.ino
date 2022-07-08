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
  
  // html 页面, += 操作符属于字符串拼接操作符
  String html_content = R"===(
        <html>
         <head>
            <meta charset="utf-8" http-equiv="Refresh" content="5" />
            <title>Arduino 温湿度显示</title>
            <style>h1 {display: inline;} span {font-size: 2em; color: red;}</style>
         </head>
          <body>
            <div>
                <h1>当前湿度:&nbsp;&nbsp;</h1>
                <span>
            )===";

  // 从温湿传感器获取的湿度，将浮点类型转换为字符串类型，然后使用字符串拼接操作符 +=
  html_content += String(h);
  
  html_content += R"===(
          &nbsp;%</span>
            </div>
            <div>
            <h1>当前温度:&nbsp;&nbsp;</h1>
            <span>
            )===";
            
  html_content += String(t);
  
  html_content += R"===(
          &nbsp;℃</span>
            </div>
          </body>
        </html>
        )===";

  server.send(200, "text/html", html_content);
}

void setup() {
  //初始化串口
  Serial.begin(115200);

  delay(1000);
  Serial.println();
  Serial.println("Configuring access point...");

  //启动 AP 热点，ssid 热点名称，password 热点密码
  WiFi.softAP(ssid, password);

  //显示热点信息，主要是访问的网址：http://192.168.4.1
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  //绑定HTTP服务器/目录下所发布的信息
  server.on("/", handleRoot);
  
  // 启动服务器
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  // 监听来自客户端的消息请求
  server.handleClient();
}
