/*
   运行该代码，先修改文件名为合法的变量名。

   lcd左右移动英文实验。

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

//显示的内容
char strtitle[] = "hello, DOFLY!";

//内容的长度
int nSize = strlen(strtitle);

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, DOFLY!");
}

void loop() {
  lcd.scrollDisplayRight();
  delay(300);
}
