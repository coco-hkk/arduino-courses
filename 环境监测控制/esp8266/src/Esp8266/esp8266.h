/*
 *
 *  esp8266 所用到的管脚宏定义
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */
 
#ifndef ESP8266_H
#define ESP8266_H
#endif

#include "../common/gpio.h"
#include "../common/soft_serial.h"

#define LED_PIN     (D0)    //LED
#define LED_R_PIN   (D1)
#define LED_G_PIN   (D2)
#define LED_B_PIN   (D3)

#define BEE_PIN     (D4)    //蜂鸣器

#define ESP8266_RX  (D5)    //Serial
#define ESP8266_TX  (D6)

#define IR_REMOTE   (D7)    //红外遥控

/*
 *  @func : 初始化软串口
 */
void esp8266_serial_init();

/*
 *  @func : esp8266 分发处理来自其他设备的消息
 *  @para1: 存储消息的变量
 */
void read_serial_data(mcu_msg& data);

/*
 *  @func : esp8266 发送重启 arduino 给 arduino 设备。
 */
void esp8266_reset_arduino();
