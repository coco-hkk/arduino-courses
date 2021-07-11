/*
  运行该代码，先修改文件名为合法的变量名。
  
  红外遥控编码打印 实验
  
  1 tab = 2 space
*/

#include <IRremote.h>

// 本代码适用于 IRremote 3.1.1 之前的

//An IR detector/demodulator is connected to GPIO pin 11
uint16_t RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();    //Start the receiver
}

void loop() {
  if (irrecv.decode(&results))      //检查是否收到红外遥控信号
  {
    Serial.println(results.value, HEX);   //打印信号编码
    irrecv.resume();                      //Receive the next value
  }
  delay(100);
}
