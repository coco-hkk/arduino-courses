/*
  运行该代码，先修改文件名为合法的变量名。
  
  抢答器实验。
  
  1 tab = 2 space
*/

int redled = 6;
int yellowled = 5;
int greenled = 4;

int redpin = 3;
int yellowpin = 2;
int greenpin = 1;


int red;
int yellow;
int green;


void setup()
{
  pinMode(redled,OUTPUT);
  pinMode(yellowled,OUTPUT);
  pinMode(greenled,OUTPUT);
  
  pinMode(redpin,INPUT);
  pinMode(yellowpin,INPUT);
  pinMode(greenpin,INPUT);
}

void loop()
{
  red = digitalRead(redpin);
  
  if(red == LOW)
  { 
    digitalWrite(redled,LOW);
  }
  else
  { 
    digitalWrite(redled,HIGH);
  }
  
  yellow = digitalRead(yellowpin);
  if(yellow == LOW)
  {
    digitalWrite(yellowled,LOW);
  }
  else
  { 
    digitalWrite(yellowled,HIGH);
  }
  
  green=digitalRead(greenpin);
  if(green == LOW)
  { 
    digitalWrite(greenled,LOW);
  }
  else
  { 
    digitalWrite(greenled,HIGH);
  }
}
