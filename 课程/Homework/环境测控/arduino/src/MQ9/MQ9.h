/*
 *
 *  MQ-9 可燃气传感器。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 初始化 MQ-9 相关引脚
 */
void mq9_init(int d0_pin);

/*
 *  @func : mq-9 检测可燃气
 *  @para1: arduino 引脚，和 MQ-9 A0连接
 *  @para2: R0测量的校准值。
 */
void mq9_task(int analog_pin, float R0);

/*
 *  @func : 判断检测的气体是否超标
 *  @ret  : 超标返回1，未超标返回0
 */
int is_mq9_alarm();

/*
 *  @func : 返回 RS/R0 比值，可用于对照表格查找浓度
 *  @ret  : RS/R0的值
 */
float get_mq9_rs_r0_ratio();

/*
 *  @func : 校准mq9 R0
 *  @para1: Arduino 管脚和mq9 A0管脚连接的编号
 */
void mq9_calibration(int analog_pin);

/*
 *  @func : 返回校准后的R0
 *  @ret  : 校准后的R0
 */
float get_mq9_R0();
