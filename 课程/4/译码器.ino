/*
  运行该代码，先修改文件名为合法的变量名。
  
  3-8译码器实验。
  
  1 tab = 2 space
*/

int  latch_Pin = 4;   //STCP
int  clock_Pin = 5;   //SHCP
int  data_Pin = 2;    //DS

void setup ()
{
  pinMode(latch_Pin,OUTPUT);
  pinMode(clock_Pin,OUTPUT);
  pinMode(data_Pin,OUTPUT); 
}
void loop()
{
  for(int a = 0; a < 256; a++)
  {
    digitalWrite(latch_Pin, LOW);             //将ST_CP口上面加低电平让芯片准备好接收数据

    /*
     * shiftOut(dataPin, clockPin, bitOrder, value)
     * 功能： 能够将数据通过串行的方式在引脚上输出，相当于一般意义上的同步串行通信，这是控制器与控制器、控制器与传感器之间常用的一种通信方式。
     * 返回值： 无      
     * dataPin： 数据输出引脚，数据的每一位将逐次输出。引脚模式需要设置成输出。
     * clockPin：时钟输出引脚，为数据输出提供时钟，引脚模式需要设置成输出。
     * bitOrder：数据位移顺序选择位，该参数为byte类型，有两种类型可选择，分别是高位先入MSBFIRST和低位先入LSBFIRST。
     * val：所要输出的数据值。
     */
    shiftOut(data_Pin, clock_Pin, MSBFIRST, a);
    
    digitalWrite(latch_Pin,HIGH);             //将ST_CP这个针脚恢复到高电平
    
    delay(1000);
  }
}
