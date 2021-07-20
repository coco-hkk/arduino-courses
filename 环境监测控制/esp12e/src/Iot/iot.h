/*
 *
 * nodemcu 模块，连接 adafruit 服务器并且发送传感器采集数据。
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 连接 MQTT服务器。
 */
void MQTT_connect();

/*
 *  @func : 初始化 iot 模块
 */
void iot_init();

void iot_task();
