/*
   运行该代码，先修改文件名为合法的变量名。

   通过串口输入指令控制发光二极管 实验

   1 tab = 2 space
 */

int val;                             // 定义变量 val 用于存储来自串口的指令
int ledpin = 13;                     // 定义数字接口13

void setup()
{
  Serial.begin(115200);              //初始化波特率为115200，必须和 Arduino IDE 串口监视器设置一致。
  pinMode(ledpin,OUTPUT);            //初始化数字端口13为输出模式，Arduino 中用到I/O端口都要进行这样的初始化。
}

void loop()
{
  val = Serial.read();                //读取从PC发送给 Arduino 的指令
  if(val == 'R')                      //判断接收到的指令
  {
    digitalWrite(ledpin,HIGH);        //点亮LED
    delay(500);

    digitalWrite(ledpin,LOW);         //熄灭LED
    delay(500);

    Serial.println("Hello World!");   //显示“Hello World！”字符串
  }
}
