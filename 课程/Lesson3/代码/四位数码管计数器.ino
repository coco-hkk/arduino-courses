/*
   运行该代码，先修改文件名为合法的变量名。

   四位数码管计数器实验。

   1 tab = 2 space
 */

#define  d_a   1
#define  d_b   2
#define  d_c   3
#define  d_d   4
#define  d_e   5
#define  d_f   6
#define  d_g   7
#define  d_h   8

#define   COM1   9
#define   COM2   10
#define   COM3   11
#define   COM4   12

//共阳极，数码管0-F码值。这里使用二维数组显示数码管值，也可以使用二进制显示。
unsigned char num[17][8] =
{
  //a  b  c  d  e  f  g  h
  { 0, 0, 0, 0, 0, 0, 1, 1 },     //0
  { 1, 0, 0, 1, 1, 1, 1, 1 },     //1
  { 0, 0, 1, 0, 0, 1, 0, 1 },     //2
  { 0, 0, 0, 0, 1, 1, 0, 1 },     //3
  { 1, 0, 0, 1, 1, 0, 0, 1 },     //4
  { 0, 1, 0, 0, 1, 0, 0, 1 },     //5
  { 0, 1, 0, 0, 0, 0, 0, 1 },     //6
  { 0, 0, 0, 1, 1, 1, 1, 1 },     //7
  { 0, 0, 0, 0, 0, 0, 0, 1 },     //8
  { 0, 0, 0, 0, 1, 0, 0, 1 },     //9
  { 0, 0, 0, 1, 0, 0, 0, 0 },     //A
  { 0, 0, 0, 0, 0, 0, 0, 0 },     //B
  { 0, 1, 1, 0, 0, 0, 1, 0 },     //C
  { 0, 0, 0, 0, 0, 0, 1, 0 },     //D
  { 0, 1, 1, 0, 0, 0, 0, 0 },     //E
  { 0, 1, 1, 1, 0, 0, 0, 0 },     //F
  { 1, 1, 1, 1, 1, 1, 1, 0 },     //.
};

// 共阴极
unsigned char num1[17][8] =
{
  //a  b  c  d  e  f  g  h
  { 1, 1, 1, 1, 1, 1, 0, 0 },     //0
  { 0, 1, 1, 0, 0, 0, 0, 0 },     //1
  { 1, 1, 0, 1, 1, 0, 1, 0 },     //2
  { 1, 1, 1, 1, 0, 0, 1, 0 },     //3
  { 0, 1, 1, 0, 0, 1, 1, 0 },     //4
  { 1, 0, 1, 1, 0, 1, 1, 0 },     //5
  { 1, 0, 1, 1, 1, 1, 1, 0 },     //6
  { 1, 1, 1, 0, 0, 0, 0, 0 },     //7
  { 1, 1, 1, 1, 1, 1, 1, 0 },     //8
  { 1, 1, 1, 1, 0, 1, 1, 0 },     //9
  { 1, 1, 1, 0, 1, 1, 1, 1 },     //A
  { 1, 1, 1, 1, 1, 1, 1, 1 },     //B
  { 1, 0, 0, 1, 1, 1, 0, 1 },     //C
  { 1, 1, 1, 1, 1, 1, 0, 1 },     //D
  { 1, 0, 0, 1, 1, 1, 1, 1 },     //E
  { 1, 0, 0, 0, 1, 1, 1, 1 },     //F
  { 0, 0, 0, 0, 0, 0, 0, 1 },     //.
};

void setup()
{
  pinMode(d_a, OUTPUT);
  pinMode(d_b, OUTPUT);
  pinMode(d_c, OUTPUT);
  pinMode(d_d, OUTPUT);
  pinMode(d_e, OUTPUT);
  pinMode(d_f, OUTPUT);
  pinMode(d_g, OUTPUT);
  pinMode(d_h, OUTPUT);

  pinMode(COM1, OUTPUT);
  pinMode(COM2, OUTPUT);
  pinMode(COM3, OUTPUT);
  pinMode(COM4, OUTPUT);
}

void loop()
{
  //9999之后自动从0开始计数
  for (int l = 0; l < 10; l++)                  // 第一个数码管，最左边的
  {
    for (int k = 0; k < 10; k++)                // 第二个数码管
    {
      for (int j = 0; j < 10; j++)              // 第三个数码管
      {
        for (int i = 0; i < 10; i++)            // 第四个数码管
        {
          for (int q = 0; q < 125; q++)
          {
          /*
           循环体中总共延时8ms，假设我要求1s计数一次，则需要循环 125 次。
           由于四位数码管每次只能显示一个数码管，所以只能轮流选择并显示数码管，
           为达到我们眼中四个数码管同时亮的效果，我们需要快速的显示各个数码管即可。
           */
            Display(1, l);
            delay(2);
            Display(2, k);
            delay(2);
            Display(3, j);
            delay(2);
            Display(4, i);
            delay(2);
          }
        }
      }
    }
  }
}

//显示函数，com可选数值范围1-4，num可选数值范围0-9
void Display(unsigned char com, unsigned char n)
{
  digitalWrite(d_a, HIGH);          //去除余晖
  digitalWrite(d_b, HIGH);
  digitalWrite(d_c, HIGH);
  digitalWrite(d_d, HIGH);
  digitalWrite(d_e, HIGH);
  digitalWrite(d_f, HIGH);
  digitalWrite(d_g, HIGH);
  digitalWrite(d_h, HIGH);

  //选择数码管
  switch (com)
  {
    case 1:
      digitalWrite(COM1, HIGH);     //选择位1
      digitalWrite(COM2, LOW);
      digitalWrite(COM3, LOW);
      digitalWrite(COM4, LOW);
      break;
    case 2:
      digitalWrite(COM1, LOW);
      digitalWrite(COM2, HIGH);     //选择位2
      digitalWrite(COM3, LOW);
      digitalWrite(COM4, LOW);
      break;
    case 3:
      digitalWrite(COM1, LOW);
      digitalWrite(COM2, LOW);
      digitalWrite(COM3, HIGH);     //选择位3
      digitalWrite(COM4, LOW);
      break;
    case 4:
      digitalWrite(COM1, LOW);
      digitalWrite(COM2, LOW);
      digitalWrite(COM3, LOW);
      digitalWrite(COM4, HIGH);     //选择位4
      break;
    default:break;
  }

  digitalWrite(d_a, (num[n][0]));   //a查询码值表
  digitalWrite(d_b, (num[n][1]));
  digitalWrite(d_c, (num[n][2]));
  digitalWrite(d_d, (num[n][3]));
  digitalWrite(d_e, (num[n][4]));
  digitalWrite(d_f, (num[n][5]));
  digitalWrite(d_g, (num[n][6]));
  digitalWrite(d_h, (num[n][7]));
}
