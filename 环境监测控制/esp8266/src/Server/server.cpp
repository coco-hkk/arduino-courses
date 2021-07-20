/*
 *
 *  esp8266 wifi 模块作为服务器。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */
#include "server.h"
#include "../irremote/irremote.h"

//网络服务所需头文件
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//设置AP的SSID和密码
const char *ssid = "NodeMCU";
const char *password = "12345678";

float temperature,
      humidity,
      obstacle_distance,
      pm25_dust_denisty,
      mq9_ratio,
      mq9_alarm,
      yl69_analog_value,
      photoresistor;

int led_status,
    music_status,
    server_status;

//全局对象，用提供web服务
ESP8266WebServer server(80);

//html
String meta_html, control_html;

String publish_html = "<h2>传感器采集数据发布</h2>\
                  <p>温度          ： " + String(temperature) + "</p>\
                  <p>湿度          ： " + String(humidity) + "</p>\
                  <p>障碍物距离    ： " + String(obstacle_distance) + "</p>\
                  <p>PM2.5浓度     ： " + String(pm25_dust_denisty) + "</p>\
                  <p>MQ9 RS/R0     ： " + String(mq9_ratio) + "</p>\
                  <p>MQ9超标状态   ： " + String(mq9_alarm?"超标":"正常") + "</p>\
                  <p>土壤湿度模拟值： " + String(yl69_analog_value) + "</p>\
                  <p>光照强度模拟值： " + String(photoresistor) + "</p>";

String before_html = "\
    <!DOCTYPE html>\
    <html>\
    <head>";

String title_html = "\
    <title>ESP8266 信息发布和设备控制</title>";

String head_html = "\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
    <style>\
    * { box-sizing: border-box; }\
    body { margin: 0; }\
    .header { background-color: #f1f1f1; padding: 20px; text-align: center; }\
    .topnav { overflow: hidden; background-color: #333; }\
    .topnav a { float: left; display: block; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none; width: 50%;}\
    .topnav a:hover { background-color: #ddd; color: black; }\
    .column { float: left; width: 100%; }\
    .row:after { content: \"\"; display: table; clear: both; }\
    @media screen and (max-width: 600px) { .column { width: 100%; } }\
    .item {color:red; font-weight:bold;}\
    .item1 {color:blue; font-weight:bold;}\
    </style>\
    </head>\
    <body>\
    <div class=\"header\">\
      <h1>ESP8266 信息发布和设备控制</h1>\
    </div>\
    <div class=\"topnav\">\
      <a href=\"/\">信息发布</a>\
      <a href=\"/control\">设备控制</a>\
    </div>\
    <div class=\"row\">\
      <div class=\"column\" id=\"content\">";

String foot_html = "\
      </div>\
    </div>\
    </body>\
    </html>";

void get_sensor_data_from_arduino_uno(mcu_msg& uno_msg) {
  temperature       = uno_msg.msg.uno_sensor_msg.temperature      ;
  humidity          = uno_msg.msg.uno_sensor_msg.humidity         ;
  obstacle_distance = uno_msg.msg.uno_sensor_msg.obstacle_distance;
  pm25_dust_denisty = uno_msg.msg.uno_sensor_msg.pm25_dust_denisty;
  mq9_ratio         = uno_msg.msg.uno_sensor_msg.mq9_ratio        ;
  mq9_alarm         = uno_msg.msg.uno_sensor_msg.mq9_alarm        ;
  yl69_analog_value = uno_msg.msg.uno_sensor_msg.yl69_analog_value;
  photoresistor     = uno_msg.msg.uno_sensor_msg.photoresistor    ;

  publish_html = "<h2>传感器采集数据发布</h2>\
                  <p>温度          ： " + String(temperature) + "</p>\
                  <p>湿度          ： " + String(humidity) + "</p>\
                  <p>障碍物距离    ： " + String(obstacle_distance) + "</p>\
                  <p>PM2.5浓度     ： " + String(pm25_dust_denisty) + "</p>\
                  <p>MQ9 RS/R0     ： " + String(mq9_ratio) + "</p>\
                  <p>MQ9超标状态   ： " + String(mq9_alarm?"超标":"正常") + "</p>\
                  <p>土壤湿度模拟值： " + String(yl69_analog_value) + "</p>\
                  <p>光照强度模拟值： " + String(photoresistor) + "</p>";
}

 //用户跳转到http://192.168.4.1时页面内容
static void handle_info_publish() {
  meta_html = "<meta charset=\"utf-8\" http-equiv=\"Refresh\" content=\"5\"/>";
  String strHtml = before_html + meta_html + title_html + head_html + publish_html + foot_html;
  server.send(200, "text/html", strHtml);
}

 //用户跳转到http://192.168.4.1/Digital时页面内容
static void handle_device_control()
{
  meta_html = "<meta charset=\"utf-8\"/>";

  if (server.hasArg("led_value")) {
    String led_str = server.arg("led_value");
    led_status = led_str.toInt();
    led_status?led_write_high():led_write_low();
  }

  /*音乐播放过程中网页会卡住，所有操作得等到音乐播放完后才可以进行。可使用OS解决
   * 这个问题，也可以用定时器。
   */
  if (server.hasArg("music")) {
    String music_str = server.arg("music");
    music_status = music_str.toInt();
  }
  if (server.hasArg("server_restart")) {
    String server_str = server.arg("server_restart");
    server_status = server_str.toInt();
  }

  control_html = "<h2>MCU外设控制</h2>\
                  <div>\
                  <form>\
                    <p><span class=\"item\">LED 控制</span>：&nbsp;\
                    <input type=\"button\" value=\"开灯\" onclick=\'location.href=(\"/control?led_value=1\")\' />\
                    <input type=\"button\" value=\"关灯\" onclick=\'location.href=(\"/control?led_value=0\")\' />\
                    &nbsp;&nbsp;&nbsp;&nbsp;<span class=\"item1\">" + String(led_status?"LED灯亮":"LED熄灭") + "</span></p>\
                  </form>\
                  <form>\
                    <p><span class=\"item\">音乐控制</span>：&nbsp;\
                    <input type=\"button\" value=\"播放\" onclick=\'location.href=(\"/control?music=1\")\' />\
                    &nbsp;&nbsp;&nbsp;&nbsp;<span class=\"item1\">" + String(music_status?"正在播放":"音乐停止") + "</span></p>\
                  </form>\
                  <form>\
                    <p><span class=\"item\">服务器状态</span>：&nbsp;\
                    <input type=\"button\" value=\"重启\" onclick=\'location.href=(\"/control?server_restart=1\")\' />\
                    &nbsp;&nbsp;&nbsp;&nbsp;<span class=\"item1\">" + String(server_status?"服务器正在重启中……":"服务器正在运行中") + "</span></p>\
                  </form></div>";

  String strHtml = before_html + meta_html + title_html + head_html + control_html + foot_html;
  server.send(200, "text/html", strHtml);

  if (server.hasArg("music") && music_status) {
    music_status = 0;
    music_play();
    handle_device_control();
  }
  if (server.hasArg("server_restart") && server_status) {
    server_status = 0;
    delay(2000);        //延迟2s，等待网页刷新
    ESP8266_reboot();
  }
}

void server_config() {
  Serial.println("配置热点……");

  Serial.println("启动热点……");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("热点 IP： ");
  Serial.println(myIP);

  server.on("/", handle_info_publish);
  server.on("/control",  handle_device_control);

  server.begin();

  Serial.println("HTTP Server started.");
}

void server_listen() {
  server.handleClient();
}
