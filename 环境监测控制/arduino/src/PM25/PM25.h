/*
 *
 *  PM2.5传感器。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : PM2.5 模块初始化
 *  @para1: arduino 管脚和PM2.5传感器电源灯管脚连接编号
 */
void pm25_init(int ledpower_pin);

/*
 *  @func : 检测PM2.5浓度
 *  @para1: 检测结果输入到Arduino的管脚编号
 */
void pm25_task(int measure_pin);

/*
 *  @func : 返回PM2.5浓度
 *  @ret  : PM2.5浓度
 */
float get_pm25_dust_density();

