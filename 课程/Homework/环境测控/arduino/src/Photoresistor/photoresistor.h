/*
 *
 * 光敏电阻模块，检测光照强度。光照越强，电阻越小。电路可串联 1K-10K 电阻。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 获取光照强度值
 *  @ret  : 返回从管脚读取的模拟值
 */
float get_photoresistor_value(int pin);

/*
 *  @func : 打印光照强度的模拟值，在调用此函数前先调用 get_photoresistor_value()。
 */
void get_photoresistor_print();
