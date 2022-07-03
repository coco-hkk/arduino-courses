/*
   运行该代码，先修改文件名为合法的变量名。

   电位器控制LED实验

   1 tab = 2 space
 */

int potpin = 0;                 //模拟端口A0
int ledpin = 11;                //数字端口11（PWM 输出）
int val    = 0;

void setup()
{
  pinMode(ledpin,OUTPUT);
  Serial.begin(115200);
  //注意：模拟接口自动设置为输入
}

void loop()
{
  val = analogRead(potpin);     // 读取电位计模拟值
  Serial.println(val);

  /*
   LED正极接到ledpin端口，通过 analogWrite 控制PWM端口输出电压达到控制LED亮度目的。
   由于 PWM 端口可输出范围为 0~255，而模拟端口为 0~1023 所以需要 val/4
   */
  analogWrite(ledpin,val/4);
  delay(10);
}

/*
 这个实验中，电位计和LED灯是两套独立的电路。由于它们都使用了 Arduino 端口，
 所以我们可以通过代码操纵它们所使用的端口，然后将两套独立的电路通过程序联系
 在一起。 
 */