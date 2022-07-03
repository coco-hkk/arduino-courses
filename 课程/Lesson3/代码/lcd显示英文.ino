/*
   运行该代码，先修改文件名为合法的变量名。

   显示英文实验。

   1 tab = 2 space
 */

#include <LiquidCrystal.h>

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
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  //指定显示屏的尺寸（宽度和高度）,16列，2行
  lcd.begin(16, 2);

  //打印字符，将文本显示在LCD上.
  lcd.print("hello, DOFLY!");
}

//循环执行
void loop() {
  //设置光标到第2行第7列(注意：1 表示第2行，从0开始计数):
  lcd.setCursor(6, 1);

  //打印复位后的运行秒值
  lcd.print(millis() / 1000);
  lcd.print(" Second");
}
