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
#include "../esp8266/esp8266.h"
#include "../servo/servo.h"

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

volatile int led_status,
    music_status,
    server_status,
    servo_status,
    arduino_status;

static int html_refresh_flag;

//全局对象，用提供web服务
ESP8266WebServer server(80);

//html
String meta_html, control_html;

String publish_html = "<h2>传感器采集数据发布</h2>\
                  <p>温度          ： " + String(temperature) + " ℃ </p>\
                  <p>湿度          ： " + String(humidity) + " % </p>\
                  <p>障碍物距离    ： " + String(obstacle_distance) + " cm </p>\
                  <p>PM2.5浓度     ： " + String(pm25_dust_denisty) + " ug/m3 </p>\
                  <p>MQ9 RS/R0     ： " + String(mq9_ratio) + "</p>\
                  <p>MQ9超标状态   ： " + String(mq9_alarm?"超标":"正常") + "</p>\
                  <p>土壤湿度模拟值： " + String(yl69_analog_value) + "</p>\
                  <p>光照强度模拟值： " + String(photoresistor) + "</p>";

String head_html = "\
    <!DOCTYPE html>\
    <html>\
    <head>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";

String title_html = "\
    <title>ESP8266 信息发布和设备控制</title>";

String style_html = "\
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
    table {width: 50%;}\
    #servo_value {font-size: 1.5rem; color: red; font-weight: bold;}\
    </style>";

String script_html = "<script>\
                   function servo_change(flag = 0) {\
                        var x = document.getElementById(\"servo\").value;\
                        document.getElementById(\"servo_value\").innerHTML = x;\
                        if (1 == flag) {\
                            window.location.href = \"/control?servo_angle=\" + String(x);}\
                    }\
                  </script>";

String body_html = "\
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

void get_sensor_data_from_arduino_uno(mcu_msg& data) {
  temperature       = data.msg.uno_sensor_msg.temperature;
  humidity          = data.msg.uno_sensor_msg.humidity;
  obstacle_distance = data.msg.uno_sensor_msg.obstacle_distance;
  pm25_dust_denisty = data.msg.uno_sensor_msg.pm25_dust_denisty;
  mq9_ratio         = data.msg.uno_sensor_msg.mq9_ratio;
  mq9_alarm         = data.msg.uno_sensor_msg.mq9_alarm;
  yl69_analog_value = data.msg.uno_sensor_msg.yl69_analog_value;
  photoresistor     = data.msg.uno_sensor_msg.photoresistor;


  publish_html = "<h2>传感器采集数据发布</h2>\
                  <p>温度          ： " + String(temperature) + " ℃ </p>\
                  <p>湿度          ： " + String(humidity) + " % </p>\
                  <p>障碍物距离    ： " + String(obstacle_distance) + " cm </p>\
                  <p>PM2.5浓度     ： " + String(pm25_dust_denisty) + " ug/m3 </p>\
                  <p>MQ9 RS/R0     ： " + String(mq9_ratio) + "</p>\
                  <p>MQ9超标状态   ： " + String(mq9_alarm?"超标":"正常") + "</p>\
                  <p>土壤湿度模拟值： " + String(yl69_analog_value) + "</p>\
                  <p>光照强度模拟值： " + String(photoresistor) + "</p>";

  //若果 esp8266 可以正常得到来自arduino的采集数据，可以认为arduino正常运行。
  arduino_status = 0;
}

 //用户跳转到http://192.168.4.1时页面内容
static void handle_info_publish() {
  meta_html = "<meta charset=\"utf-8\" http-equiv=\"Refresh\" content=\"5\"/>";
  String strHtml = head_html + meta_html + title_html + style_html + body_html + publish_html + foot_html;
  server.send(200, "text/html", strHtml);
}

 //用户跳转到http://192.168.4.1/Digital时页面内容
static void handle_device_control()
{
  meta_html = "<meta charset=\"utf-8\"/>";

  if (0 == html_refresh_flag) {
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

    if (server.hasArg("arduino_restart")) {
      String arduino_str = server.arg("arduino_restart");
      arduino_status = arduino_str.toInt();
    }

    if (server.hasArg("servo_angle")) {
      String servo_str = server.arg("servo_angle");
      servo_status = servo_str.toInt();
    }
  }

  control_html = "<h2>MCU外设控制</h2>\
                <div>\
                <table>\
                <tbody>\
                 <tr>\
                     <td>\
                         <span class=\"item\">服务器状态</span>\
                     </td>\
                     <td>\
                         <span class=\"item1\">" + String(server_status?"服务器正在重启中……":"服务器正在运行中") + "</span>\
                     </td><td>\
                         <input type=\"button\" value=\"重启 ESP8266 服务器\" onclick=\"location.href=(&quot;/control?server_restart=1&quot;)\">\
                     </td>\
                </tr>\
                 <tr>\
                     <td>\
                         <span class=\"item\">Arduino 状态</span>\
                     </td>\
                     <td>\
                         <span class=\"item1\">" + String(arduino_status?"正在重启……":"正常工作") + "</span>\
                     </td><td>\
                         <input type=\"button\" value=\"重启 Arduino\" onclick=\"location.href=(&quot;/control?arduino_restart=1&quot;)\">\
                     </td>\
                </tr>\
                <tr>\
                <td><span class=\"item\">LED 控制</span></td>\
                <td><span class=\"item1\">"+ String(led_status?"LED灯亮":"LED熄灭") + "</span></td>\
                <td>\
                    <input type=\"button\" value=\"开灯\" onclick=\"location.href=(&quot;/control?led_value=1&quot;)\">\
                    <input type=\"button\" value=\"关灯\" onclick=\"location.href=(&quot;/control?led_value=0&quot;)\">\
                </td>\
                </tr>\
                    <tr><td><span class=\"item\">音乐控制</span></td>\
                        <td><span class=\"item1\">" + String(music_status?"正在播放":"音乐停止") + "</span></td>\
                        <td>\
                            <input type=\"button\" value=\"播放\" onclick=\"location.href=(&quot;/control?music=1&quot;)\">\
                        </td>\
                    </tr>\
                </tbody>\
                </table>\
                </div>\
                <hr><div>\
                <h3>舵机</h3>\
                <input type=\"range\" id=\"servo\" value=\"" + servo_status + "\" min=\"0\" max=\"180\" step=\"1\" oninput=\"servo_change()\" oninput=\"servo_change()\">\
                <button onclick=\"servo_change(1)\">确定</button>\
                <span id=\"servo_value\">" + servo_status + "</span>\
                </div>";

  String strHtml = head_html + meta_html + title_html + style_html + script_html + body_html + control_html + foot_html;
  server.send(200, "text/html", strHtml);

  if (0 == html_refresh_flag) {
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

    if (server.hasArg("arduino_restart") && arduino_status) {
      esp8266_reset_arduino();
    }

    if (server.hasArg("servo_angle")) {
      servo_control(servo_status);
    }
  }
  html_refresh_flag = 0;
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
