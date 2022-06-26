/*
 *
 *  超声波测距。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 超声波测距初始化
 *  @para1: trig 管脚编号
 *  @para2: echo 管脚编号
 */
void ultrasonicwave_init(int trig_pin, int echo_pin);

/*
 *  @func : 负责不断的去检测障碍物距离，必须放在主文件 loop 循环中
 */
void ultrasonicwave_task();

/*
 *  @func : 返回障碍物距离
 *  @ret  : 障碍物距离
 */
float get_ultrasonicwave_distance();

/*
 *  @func : 打印障碍物距离
 */
void get_ultrasonicwave_distance_print();
