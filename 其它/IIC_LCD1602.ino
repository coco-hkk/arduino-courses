#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//设置LCD1602设备地址，这里的地址是0x3F，一般是0x20，或者0x27，具体看模块手册
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("LCD1602 iic Test");
  lcd.setCursor(0,1);
  lcd.print("  of arduino ");
  delay(1000);
}
