/*
  运行该代码，先修改文件名为合法的变量名。
  
  按键实验，按一下亮一下，不按不亮。
  
  1 tab = 2 space
*/

int LED = 13;
int INPUT_KEY = 2;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(INPUT_KEY, INPUT);
  //pinMode(INPUT_KEY, INPUT_PULLUP);/*设置INPUT_PULLUP ，INPUT_KEY就不会处于悬空状态*/
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(INPUT_KEY) == LOW) 
  {
    digitalWrite(LED, LOW);
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
}
