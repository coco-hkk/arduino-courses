/*
  运行该代码，先修改文件名为合法的变量名。
  
  YL-69土壤湿度实验。
  
  1 tab = 2 space
*/

#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13

#define PIN_AO A0
#define PIN_DO D1
 
void setup() {  
  pinMode(PIN_AO, INPUT);
  pinMode(PIN_DO, INPUT);  
  Serial.begin(115200);  
}  
 
void loop() 
{
  Serial.print("AO =");  
  Serial.print(analogRead(PIN_AO));
  Serial.print(", DO =");  
  Serial.println(digitalRead(PIN_DO));
  delay(500);  
}
