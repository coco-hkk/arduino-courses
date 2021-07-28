/*
  运行该代码，先修改文件名为合法的变量名。
  
  光敏电阻实验。光照越强，电阻越小。
  
  1 tab = 2 space
*/

#define LIGHT_SENSOR_PIN A2
#define LED_PIN 12
 
int Intensity = 0;  //光照度数值
 
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}
 
void loop()
{
  Intensity = analogRead(LIGHT_SENSOR_PIN);
  
  Serial.println(Intensity);

  analogWrite(LED_PIN, Intensity/4);
  
  delay(500);
}
