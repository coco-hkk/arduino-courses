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

#include "../common/gpio.h"
#include "../common/soft_serial.h"

#define ESP12E_RX D0
#define ESP12E_TX D1

/*
 *  @func : 初始化软串口
 */
void esp12e_serial_init();

/*
 *  @func : esp8266 分发处理来自其他设备的消息
 *  @para1: 存储消息的变量
 */
void read_serial_data();
