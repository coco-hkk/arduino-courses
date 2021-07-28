/*
 *
 *  esp12e 所用到的管脚宏定义
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */
#ifndef ESP12E_H
#define ESP12E_H
#endif

#include <StreamUtils.h>
#include "../common/gpio.h"
#include "../common/soft_serial.h"

#define ESP12E_RX D7    //软串口通信
#define ESP12E_TX D8

#define LCD_RS     D0   //LCD
#define LCD_ENABLE D1
#define LCD_D4     D2
#define LCD_D5     D3
#define LCD_D6     D4
#define LCD_D7     D5

#define LED_PIN    D6   //LED


/*
 *  @func : 初始化软串口
 */
void esp12e_serial_init();

/*
 *  @func : esp8266 分发处理来自其他设备的消息
 *  @para1: 存储消息的变量
 */
void read_serial_data();

/*
 *  @func : esp12e 获取来自串口的传感器数据
 *  @para1: 数据
 */
void get_sensor_data(mcu_msg& data);
