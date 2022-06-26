/*
 *
 *  软串口通信模块。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#ifndef SOFT_SERIAL_H
#define SOFT_SERIAL_H

#include <ArduinoJson.h>
#include <SoftwareSerial.h>

/*设备*/
#define ARDUINO_DEV         (-1)
#define ESP8266_DEV         (-2)
#define ESP_12E_DEV         (-3)
#define ANY_DEV             (-4)

/*arduino uno 采集传感器数据指令*/
#define ARDUINO_SENSOR_MSG (0)

#define ESP8266_RESET_UNO_MSG (20)

#define NODEMCU_MSG (40)

/*arduino uno 采集传感器数据结构体*/
typedef struct {
    float temperature;
    float humidity;
    float obstacle_distance;    //超声波模块障碍物距离
    float pm25_dust_denisty;    //PM2.5浓度
    float mq9_ratio;            //MQ-9传感器检测CO的 RS/R0 比值
    int   mq9_alarm;            //检测CO是否超标，超标为1
    float yl69_analog_value;    // YL-69 土壤湿度模拟值
    float photoresistor;        // 光敏电阻模拟值
} arduino_sensor_msg;

typedef struct {
    int src;            //发送消息的设备
    int dst;            //接收消息的设备
    int id;             //用于标识消息是由哪个模块传递
    union {
        arduino_sensor_msg uno_sensor_msg;  //ARDUINO_SENSOR_MSG
        boolean uno_reset;                  //ESP8266_RESET_UNO_MSG
    } msg;
} mcu_msg;

#endif
