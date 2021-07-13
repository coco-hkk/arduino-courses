/*
  运行该代码，先修改文件名为合法的变量名。
  
  MQ-9可燃气体实验。
  
  1 tab = 2 space
*/

const int LED = 2;
const int DO = 8;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(DO, INPUT);
}

void loop() {

  int   alarm = 0;
  float sensor_volt;
  float RS_gas;
  float ratio;
  
  //替换R0为之前校准的R0
  float R0 = 1.10;

  int sensorValue = analogRead(A0);
  sensor_volt = ((float)sensorValue / 1024) * 5.0;
  RS_gas = (5.0 - sensor_volt) / sensor_volt; // Depend on RL on yor module


  ratio = RS_gas / R0; // ratio = RS/R0
//------------------------------------------------------------/

  Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);
  Serial.print("RS_ratio = ");
  Serial.println(RS_gas);
  Serial.print("Rs/R0 = ");
  Serial.println(ratio);

  Serial.println();

  alarm = digitalRead(DO);
  if (alarm == 1) digitalWrite(LED, HIGH);
  else if (alarm == 0) digitalWrite(LED, LOW);

  delay(1000);
}