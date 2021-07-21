/*
 *
 *  LCD 模块
 *
 *  2021/07/21 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

/*
 *  @func : 初始化 lcd
 */
void lcd_init();

/*
 *  @func : 设置 Lcd 显示内容
 *  @para1: 显示内容
 */
void lcd_set_value(String str);

/*
 *  @func : lcd 任务
 */
void lcd_task();
