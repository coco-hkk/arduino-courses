/*
 *
 *  LCD 模块
 *
 *  2021/07/21 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "../esp12e/esp12e.h"

/*
*初始化引脚
*设置接线的对应引脚编号
*rs:12
*enable:11
*d4:5
*d5:4
*d6:3
*d7:2
*/

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

String value;

void lcd_init() {
  lcd.begin(16, 2);
}

void lcd_set_value(String str) {
//  strncpy(value, str, str.length());
    value = str;
}

void lcd_task() {
  lcd.setCursor(0, 0);

  lcd.print(value);

  lcd.setCursor(16, 0);

  lcd.autoscroll();

  for (unsigned int i = 0; i < value.length(); i++)
  {
    lcd.print(value[i]);
    delay(300);
  }

  lcd.noAutoscroll();
}
