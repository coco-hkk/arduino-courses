/*
 *
 *  土壤湿度模块，获取模拟值。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 初始化YL69模块。
 */
/*
 *  @func : 初始化YL69模块
 *  @para1: D0 管脚接的 Arduino 管脚编号
 *  @para2: A0 管脚接的 Arduino 管脚编号
 */
void YL69_init(int d0_pin, int a0_pin);

/*
 *  @func : 获取 YL69 D0 管脚的值
 *  @ret  : 1和0
 */
int get_YL69_D0_value();

/*
 *  @func : 获取 YL69 A0 管脚的模拟值
 *  @ret  : 模拟值
 */
float get_YL69_A0_value();

/*
 *  @func : 打印 YL69 获取的A0 和 D0 值。使用该函数前先调用
 *  get_YL69_D0_value()和get_YL69_A0_value()
 */
void get_YL69_print();
