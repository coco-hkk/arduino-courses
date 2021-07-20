/*
 *
 *  蜂鸣器演奏音乐。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>
#include "../led/led.h"

//列出全部D调的频率
#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556

#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278

#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112

//列出所有节拍
#define WHOLE     1
#define HALF      0.5
#define QUARTER   0.25
#define EIGHTH    0.125
#define SIXTEENTH 0.625

//根据简谱列出各频率
int tune[]=
{
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD3,NTD2,NTD2,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1,
  NTD2,NTD2,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD2,
  NTD1,NTD2,NTDL5,NTD0,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD4,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1
};

//根据简谱列出各节拍
float durt[]=
{
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,0.5,0.5,1,1,
  1,0.5,0.5,1,1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,0.5,0.5,
  1,1,1,1,
  1+0.5,0.5,1+1,
};

int length;
int _tone_pin = 0;

void music_init(int tone_pin)
{
  _tone_pin = tone_pin;
  pinMode(tone_pin, OUTPUT);
  length = sizeof(tune)/sizeof(tune[0]);   //计算长度
}
void music_play()
{
  for(int x = 0; x<length; x++)           //循环音符的次数
  {
    tone(_tone_pin,tune[x]);                //此函数依次播放tune序列里的数组，即每个音符

    //digitalWrite(ledpin, HIGH);
    rgb_color(x % 7);
    delay(300*durt[x]);                   //这里用来根据节拍调节延时，是每个音符持续的时间，即节拍duration，500是调整时间的越大，曲子速度越慢，越小曲子速度越快，自己掌握吧,500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
    //digitalWrite(ledpin, LOW);
    delay(200*durt[x]);
    noTone(_tone_pin);                      //停止当前音符，进入下一音符
  }
  delay(2000);
}

