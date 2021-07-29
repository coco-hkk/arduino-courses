/*
   运行该代码，先修改文件名为合法的变量名。

   按键实验，按一下亮，按一下灭。

   1 tab = 2 space
 */

int LED       = 13;
int INPUT_KEY = 2;
int val       = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(INPUT_KEY, INPUT);    /*设置INPUT_PULLUP ，INPUT_KEY就不会处于悬空状态*/
}

void ScanKey()
{
  val = 0;
  if (digitalRead(INPUT_KEY) == LOW)
  {
    delay(20);

    if (digitalRead(INPUT_KEY) == LOW)
    {
      val = 1;
      while (digitalRead(INPUT_KEY) == LOW);
    }
  }
}

void loop() {
  ScanKey();
  if (val == 1)
  {
    digitalWrite(LED, !digitalRead(LED));
  }
}
