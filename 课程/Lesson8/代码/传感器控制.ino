/*
   运行该代码，先修改文件名为合法的变量名。

   服务器传感器控制实验。

   1 tab = 2 space
 */

//网络服务所需头文件
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define D4 2

//设置AP的SSID和密码
const char *ssid     = "NodeMCU";
const char *password = "12345678";

//全局对象，用提供web服务
ESP8266WebServer server(80);

//全局字符串对象，用以完成网页所需的html脚本
String strHtml1 = R"===(
  <html>
    <head>
     <meta charset="utf-8" />
      <title>外设控制</title>
   </head>
   <body>
      <form id=form1>
        <input type="button" value="开灯" onclick='location.href=("/Digital?value=1")' />
        <input type="button" value="关灯" onclick='location.href=("/Digital?value=0")' />
      </form>
      <h1>D4 is )===";

//全局字符串对象，用以完成网页所需的html脚本
String strHtml2 =R"===(
      </h1>
   </body>
  </html>
  )===";

//全局变量，表示LED的亮灭
int valueLED = 0;

//用户跳转到 http://192.168.4.1/Digital 时页面内容
void handleDigital()
{
  // 页面传递参数到这里，使用sever.arg解析参数
  String str = server.arg("value");
  valueLED = str.toInt();
  digitalWrite(D4, valueLED);

  String htmlContent = strHtml1 + String(valueLED?"HIGH" : "LOW") + strHtml2;
  server.send(200, "text/html", htmlContent);
}

//用户跳转到http://192.168.4.1时页面内容
void handleRoot() {
  String htmlContent = strHtml1 + String(valueLED?"HIGH" : "LOW") + strHtml2;
  server.send(200, "text/html", htmlContent);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  //启动AP热点
  WiFi.softAP(ssid, password);

  //显示热点信息，访问网址 http://192.168.4.1
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  //设置D4端口模式为输出
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);

  //绑定 HTTP 服务器 / 目录下所发布的信息
  server.on("/", handleRoot);

  //绑定 HTTP 服务器 /Digital 目录下所发布的信息
  server.on("/Digital", HTTP_GET, handleDigital);

  //启动服务器
  server.begin();

  Serial.println("HTTP Server started.");
}

void loop() {
  // 监听客户端请求
  server.handleClient();
}
