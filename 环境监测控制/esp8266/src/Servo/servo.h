/*
 *
 *  舵机模块
 *
 *  2021/07/20 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 初始化舵机模块
 */
void servo_init();

/*
 *  @func : 转动舵机
 *  @para1: 转动角度，范围 0~180
 */
void servo_control(int angle);
