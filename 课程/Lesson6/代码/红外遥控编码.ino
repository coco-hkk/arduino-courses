/*
   运行该代码，先修改文件名为合法的变量名。

   红外遥控编码打印 实验

   1 tab = 2 space
 */

#include <IRremote.h>

uint16_t IR_RECEIVE_PIN = 11;

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode())                      //检查是否收到红外遥控信号
  {
    //IrReceiver.printIRResultShort(&Serial);   // rawdata 简明输出
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();                        //Receive the next value
  }
  delay(100);
}
