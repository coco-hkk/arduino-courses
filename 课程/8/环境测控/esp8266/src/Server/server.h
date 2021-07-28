/*
 *
 *  esp8266 wifi 模块作为服务器。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include "../common/soft_serial.h"
#include "../led/led.h"
#include "../music/music.h"

/*
 *  @func : 服务器配置
 */
void server_config();

/*
 *  @func : 服务器监听来自客户端的请求
 */
void server_listen();

/*
 *  @func : 获取从 arduino uno 板子得到的数据
 *  @para1: uno_msg
 */
void get_sensor_data_from_arduino_uno(mcu_msg& uno_msg);
