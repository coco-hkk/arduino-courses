/*
   运行该代码，先修改文件名为合法的变量名。

   MQ-9气体传感器实验。

   1 tab = 2 space
 */

void setup() {
  Serial.begin(115200);
}

void loop() {
  float sensor_volt;
  float RS_air;         //  Rs in clean air
  float R0;             // R0 in 1000 ppm LPG
  float sensorValue = 0;

  //取100次传感器数据，求均值
  for(int x = 0 ; x < 100 ; x++)
  {
    sensorValue = sensorValue + analogRead(A0);
  }
  sensorValue = sensorValue/100.0;

  sensor_volt = (sensorValue/1024) * 5.0;               // +5V 电压
  RS_air      = (5.0-sensor_volt) / sensor_volt;       // Depend on RL on yor module
  R0          = RS_air/9.9;                            // According to MQ9 datasheet table

  Serial.print("sensor_volt = ");
  Serial.print(sensor_volt);
  Serial.println("V");

  Serial.print("R0 = ");
  Serial.println(R0);
  delay(1000);
}
