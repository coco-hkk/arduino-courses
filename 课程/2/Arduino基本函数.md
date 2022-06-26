## 关键字

```c
// if 语句
if (conditions) {

}

// if ... else
if (conditions) {

}
else {

}

// if ... else if ... else
if (conditions) {

}
else if (conditions){

}
else {

}

// for
for (;;) {

}

// while
while (conditions) {

}

// do ... while
do {

} while(conditions)

// switch ... case
switch (conditions) {
    case 1:
        break;
    default:
}

// break
// continue
// return
```

## 语法符号

```
;       // 注意是不是英文分号
{}      // 块符号
//      // 行注释
/* */   // 块注释
```

## 运算符

```
=  +  -  *
/  %  == !=
<  >  <= >=
&& || !	 ++
-- += -= *=
/=
```

## 数据类型

| boolean | char          |
| byte    | int           |
| string  | long          |
| void    | float         |
| double  | unsigned int  |
| array   | unsigned long |

## 常量

```
HIGH | LOW          // 表示数字 IO 口的电平，HIGH 表示高电平 1，LOW 表示低电平 0
INPUT | OUTPUT      // 表示数字 IO 口的方向，INPUT 表示输入（高阻态），OUTPUT   表示输出（AVR 能提供 5V 电压 40mA 电流）
true | false true   // 表示真 1，false 表示假 0
```

## 结构

```c++
void setup()    // 初始化变量，管脚模式，调用库函数等
void loop()     // 连续执行函数内的语句
```

## 数字 I/O

```c++
/*
  数字 IO 口输入输出模式定义函数，pin 表示为 0～13， mode 表示为 INPUT 或 OUTPUT。
  pinMode(7,INPUT); 	    // 将脚位 7 设定为输入模式
  */
pinMode(pin, mode)   

/*
  数字 IO 口输出电平定义函数，pin 表示为 0～13，value 表示为 HIGH 或 LOW。比如定义 HIGH 可以驱动 LED。
  digitalWrite(8,HIGH); 	//将脚位 8 设定输出高电位
  */
digitalWrite(pin, value)  

/*
  数字 IO 口读输入电平函数，pin 表示为 0～13，value 表示为 HIGH 或 LOW。比如可以读数字传感器。
  val = digitalRead(7);     // 读出脚位 7 的值并指定给 val
  */
int digitalRead(pin)   
```

## 模拟 I/O

```c++
/*
  模拟 IO 口读函数，pin 表示为 0～5（Arduino Diecimila 为 0～5，Arduino nano 为 0～7）。比如可以读模拟传感器（10 位 AD，0～5V 表示为 0～1023）。
  val = analogRead(0);     //读出模拟引脚位 0 的值并指定给 val 变数
  */
int analogRead(pin)   

/*
  数字 IO 口 PWM 输出函数，Arduino 数字 IO 口标注了 PWM 的 IO 口可使用该函数，pin 表示 3, 5, 6, 9, 10, 11，value 表示为 0～255（0-5V）。
  比如可用于电机 PWM 调速或音乐播放。
  analogWrite(9,128); // 输出电压约 2.5 伏特（V）
  */
analogWrite(pin, value) - PWM    
```

## 时间函数

```c++
/*
  返回时间函数（单位 ms），该函数是指，当程序运行就开始计时并返回记录的参数，该参数溢出大概需要 50 天时间。
  */
unsigned long millis()  

/*
  延时函数（单位 ms）
  */
delay(ms)   

/*
  延时函数（单位 us）
  */
delayMicroseconds(us)   
```

## 数学函数

```c++
min(x, y) 	           // 求最小值
max(x, y) 	           // 求最大值
abs(x)   	           // 计算绝对值
constrain(x, a, b)     // 约束函数，下限 a，上限 b，x 必须在 ab 之间才能返回。
pow(base, exponent)    // 开方函数，base 的 exponent 次方。
sq(x)                  // 平方
sqrt(x)                // 开根号
map(value, fromLow, fromHigh, toLow, toHigh)    // 约束函数，value 必须在 fromLow 与 toLow 之间和 fromHigh 与 toHigh 之间。
```

## 三角函数

```c++
sin(rad)
cos(rad)
tan(rad)
```

## 随机函数

```c++
randomSeed(seed)        // 随机数端口定义函数，seed 表示读模拟口 analogRead(pin)函数 。
long random(max)        // 随机数函数，返回数据大于等于 0，小于 max。
long random(min, max)   // 随机数函数，返回数据大于等于 min，小于 max。
```

## 外部中断函数

```c++
/*
  外部中断只能用到数字 IO 口 2 和 3，interrupt 表示中断口初始 0 或 1，表示一个功能函数，
  mode：LOW 低电平中断，CHANGE 有变化就中断，RISING 上升沿中断，FALLING 下降沿中断。
  */
attachInterrupt(interrupt,  mode)    

detachInterrupt(interrupt)    // 中断开关，interrupt=1 开，interrupt=0 关。
```

## 中断使能函数

```c++
interrupts()       // 使能中断
noInterrupts()     // 禁止中断
```

## 串口收发函数

```c++
Serial.begin(speed)          // 串口定义波特率函数，speed 表示波特率，如 115200 等。
int Serial.available()       // 判断缓冲器状态。
int Serial.read()            // 读串口并返回收到参数。
Serial.flush()               // 清空缓冲器。
Serial.print(data)           // 串口输出数据。
Serial.println(data)         // 串口输出数据并带回车符。
```

## 官方库文件

```
EEPROM         - EEPROM 读写程序库
Ethernet       - 以太网控制器程序库
LiquidCrystal  - LCD 控制程序库
Servo          - 舵机控制程序库
SoftwareSerial - 任何数字 IO 口模拟串口程序库
Stepper        - 步进电机控制程序库
Wire           - TWI/I2C 总线程序库
Matrix         - LED 矩阵控制程序库
Sprite         - LED 矩阵图象处理控制程序库
```
