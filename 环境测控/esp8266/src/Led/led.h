/*
 *
 *  led 模块。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

// rgb不同颜色
enum{ Color_R, Color_G, Color_B, Color_RG, Color_RB, Color_GB, Color_RGB };

/*
 *  @func : led 初始化
 *  @para1: 管脚编号
 */
void led_init(int led_pin);

/*
 *  @func : rgb 初始化
 *  @para1: 三个管脚编号
 */
void rgb_init(int led_r, int led_g, int led_b);

/*
 *  @func : RGB 三基色 LED。
 *  @para1: 0~6 共七中不同颜色
 */
void rgb_color(unsigned char data_color);

void led_write_high();
void led_write_low();
