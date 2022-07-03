/*
   运行该代码，先修改文件名为合法的变量名。

   MQ-9可燃气体实验。

   1 tab = 2 space
 */

const int LED = 2;
const int DO  = 8;

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(DO, INPUT);
}

void loop() {
  int   alarm = 0;
  float adcVoltage = 5.0        // MQ-9使用 5V 电压
  int   adcBits = 1024          // 模拟端口取值范围 0~1023
  float sensor_volt;
  float RS_gas;
  float ratio;
  int sensorValue;

  //替换R0为之前校准的R0
  float R0 = 1.10;

  sensorValue = analogRead(A0);
  sensor_volt = ((float)sensorValue / adcBits) * adcVoltage;
  RS_gas      = (adcVoltage - sensor_volt) / sensor_volt;       // Depend on RL on yor module，忽略 *RL
  ratio       = RS_gas / R0;                                    // ratio = RS/R0

  Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);

  Serial.print("RS_gas = ");
  Serial.println(RS_gas);

  Serial.print("Rs/R0 = ");
  Serial.println(ratio);
  Serial.println();

  alarm = digitalRead(DO);
  if (alarm == 1)
    digitalWrite(LED, HIGH);
  else if
    (alarm == 0) digitalWrite(LED, LOW);

  delay(1000);
}
