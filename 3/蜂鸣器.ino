/*
  运行该代码，先修改文件名为合法的变量名。
  
  蜂鸣器实验。
  
  1 tab = 2 space
*/

/*
 *  第一个频率的声音为1毫秒发声1毫秒不发声。1秒等于1000毫秒，2毫秒为一个周期。得出频率为500赫兹。
    第二个频率的声音为2毫秒发声2毫秒不发声，4毫秒为一个周期。得出频率为250赫兹。
    一个事件的循环就是500赫兹的声音响80毫秒，然后250赫兹的声音响200毫秒。如此循环下去。
 */
 
int  tonepin = 7;               //设置控制蜂鸣器的数字D3脚

void setup()
{
  pinMode(tonepin,OUTPUT);      //设置数字IO脚模式，OUTPUT为输出
}

void loop()
{
  unsigned char i,j;
  
  while(1)
  {
    for(i=0; i<80; i++)           //输出一个频率的声音
    {
      digitalWrite(tonepin,HIGH); //发声音
      delay(1);//延时1ms
      digitalWrite(tonepin,LOW);  //不发声音
      delay(1);//延时1ms
    }

    delay(100);
    
    for(i=0;i<200;i++)            //输出另一个频率的声音,这里的200与前面的80一样，用来控制频率，可以自己调节
    {
      digitalWrite(tonepin,HIGH);
      delay(2);
      digitalWrite(tonepin,LOW);
      delay(2);
    }
  }
}
