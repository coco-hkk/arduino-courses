/*
  运行该代码，先修改文件名为合法的变量名。
  
  RTC日期显示实验。
  
  1 tab = 2 space
*/

#include <DS1302.h>

DS1302 rtc(5, 6, 7); // RST, DAT, CLK

void setup()
{
  Serial.begin(115200);
  // 设置时间后, 需要注释掉设置时间的代码,并重新烧录一次. 以免掉电重新执行setup中的时间设置函数.
  
  //rtc.halt(false);
  //rtc.writeProtect(false);
  rtc.setDOW(WEDNESDAY);
  rtc.setTime(20, 22, 30);
  rtc.setDate(06, 7, 2021);
  rtc.writeProtect(true);
}
void loop()
{
  //Serial.print(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/'));
  Serial.print(rtc.getDateStr());
  Serial.print("    ");
  Serial.print(rtc.getDOWStr());
  Serial.print("    ");
  Serial.println(rtc.getTimeStr());
  delay(1000);
}