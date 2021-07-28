/*
  运行该代码，先修改文件名为合法的变量名。
  
  数码管秒表实验。
  
  1 tab = 2 space
*/

#define D1 2
#define D2 3
#define D3 4
#define D4 5
#define D5 6
#define D6 7
#define D7 8
#define D8 9

//共阳极码段
const unsigned char dofly_DuanMa[10] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90 };

int LEDPins[] = { D1, D2, D3, D4, D5, D6, D7,D8 };      // 对应的 LED 引脚

void setup() {
  //循环设置，把对应的 LED 都设置成输出
  for (int LED = 0; LED < 8; LED++)
  {
    pinMode(LEDPins[LED], OUTPUT);
    digitalWrite(LEDPins[LED], HIGH);
  }
}

// 数据处理，把需要处理的 byte 数据写到对应的引脚端口。
void deal(unsigned char value)
{
  for (int i = 0; i<8; i++)
  {
    digitalWrite(LEDPins[i], bitRead(value, i));//使用了 bitRead 函数，非常简单
  }
}


//主循环
void loop() {

  //循环显示 0-9 数字
  for (int i = 0; i<10; i++)
  {
    deal(dofly_DuanMa[i]);        //读取对应的段码值
    delay(1000);                  //调节延时，2个数字之间的停留间隔
  }
}
