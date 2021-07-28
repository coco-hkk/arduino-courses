/*
  运行该代码，先修改文件名为合法的变量名。
  
  点亮LED灯实验。
  
  arduino Uno使用编号为10的pin脚点灯方式
  
  1 tab = 4 space
*/

int ledPin = 10;              //定义数字10 接口

void setup()
{
  pinMode(ledPin, OUTPUT);    //定义小灯接口为输出接口
}

void loop()
{
    digitalWrite(ledPin, HIGH); //点亮小灯
}
