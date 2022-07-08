/*
   运行该代码，先修改文件名为合法的变量名。

   红外遥控控制LED 实验

   1 tab = 2 space
 */

#include <IRremote.h>

uint16_t IR_RECEIVE_PIN = 11;
int LED_PIN  = 13;

void setup()
{
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  if (IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    if (IrReceiver.decodedIRData.decodedRawData == 0xF30CFF00)        //1关灯
    {
      digitalWrite(LED_PIN, LOW);
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 0xE718FF00)   //2开灯
    {
      digitalWrite(LED_PIN, HIGH);
    }

    IrReceiver.resume();    
  }
  delay(100);
}
