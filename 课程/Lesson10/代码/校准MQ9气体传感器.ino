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
  float adcVoltage = 5.0        // MQ-9使用 5V 电压
  int   adcBits = 1024          // 模拟端口取值范围 0~1023
  float RS_air;                 //  Rs in clean air
  float R0;                     // R0 in 1000 ppm LPG
  float sensorValue = 0;

  //取100次传感器数据，求均值
  for(int x = 0 ; x < 100 ; x++)
  {
    sensorValue = sensorValue + analogRead(A0);
  }
  sensorValue = sensorValue/100.0;

  sensor_volt = (sensorValue/adcBits) * adcVoltage;             // 假设使用 5v 电压，得到 VRL
  RS_air      = (adcVoltage - sensor_volt) / sensor_volt;       // Depend on RL on yor module， 忽略 *RL
  R0          = RS_air/9.9;                                     // 根据 Sensitivity Characteristics Fig.1 图中 RS/R0 在空气中的比值为9.9（猜的）

  Serial.print("sensor_volt = ");
  Serial.print(sensor_volt);
  Serial.println("V");

  Serial.print("R0 = ");
  Serial.println(R0);
  delay(1000);
}
