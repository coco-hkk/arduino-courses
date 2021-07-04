/*
  运行该代码，先修改文件名为合法的变量名。
  
  通过串口输入指令控制发光二极管 实验
  
  1 tab = 4 space
*/

int val;              //定义变量val
int ledpin = 13;      //定义数字接口13

void setup()
{
  Serial.begin(115200);              //设置波特率为9600，这里要跟软件设置相一致。
  pinMode(ledpin,OUTPUT);           //设置数字13 口为输出接口，Arduino 上我们用到的I/O 口都要进行类似这样的定义。
}
void loop()
{
  val=Serial.read();                   //读取PC 机发送给Arduino 的指令或字符，并将该指令或字符赋给val
  if(val=='R')                          //判断接收到的指令或字符是否是“R”。
  {                                     //如果接收到的是“R”字符
    digitalWrite(ledpin,HIGH);          //点亮数字13 口LED。
    delay(500);
    digitalWrite(ledpin,LOW);          //熄灭数字13 口LED
    delay(500);
    Serial.println("Hello World!");   //显示“Hello World！”字符串
  }
}
