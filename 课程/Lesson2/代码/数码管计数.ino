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

/*
 假设数码管是共阳极数码管。
 使用二进制表示数码管每段LED，如 0xc0 用二进制表示为 1100 0000，1表示高电平，0表示低电平。
 从左到右每位表示一段LED，分别为 dp,g,...,a。则0xc0表示 dp 和 g 段LED为高电平，所以它们的
 LED熄灭。此时数码管显示0.
 此数组表示数码管显示的值，从索引0开始依次为0~9.
 */
const unsigned char dofly_DuanMa[10] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90 };

int LEDPins[] = { D1, D2, D3, D4, D5, D6, D7,D8 };      // 对应的 LED 引脚

void setup() {
  for (int LED = 0; LED < 8; LED++)
  {
    pinMode(LEDPins[LED], OUTPUT);
    digitalWrite(LEDPins[LED], HIGH);
  }
}

// 数据处理，把需要处理的 byte 数据写到对应的引脚端口。
void deal(unsigned char value)
{
  for (int i = 0; i<8; i++)                         // 遍历十六进制的每一位二进制
  {
    digitalWrite(LEDPins[i], bitRead(value, i));    //使用了 bitRead 函数，读取十六进制的第i位二进制值
  }
}

void loop() {
  for (int i = 0; i<10; i++)        //循环显示 0-9 数字
  {
    deal(dofly_DuanMa[i]);          //显示数字
    delay(1000);                    //表示1秒计数一次
  }
}
