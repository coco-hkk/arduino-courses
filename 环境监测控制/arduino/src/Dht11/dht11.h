/*
 *
 *  dht11头文件
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 获取温度
 *  @ret  : 返回温度值
 */
float get_temperature();

/*
 *  @func: 获取湿度
 *  @ret : 返回值为湿度
 */
float get_humidity();

/*
 *  @func: 打印温度和湿度
 */
void get_dht11_print();

/*
 *  @func : dhtll任务模块
 *  @para1: 入参为管脚编号
 */
void dht11_task(int pin);
