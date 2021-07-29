/*
   运行该代码，先修改文件名为合法的变量名。

   红外遥控控制LED 实验

   1 tab = 2 space
 */

#include <IRremote.h>

int RECV_PIN = 11;
int LED_PIN  = 13;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn();                    // Start the receiver

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);

    if (results.value == 0xFF30CF)        //1关灯
    {
      digitalWrite(LED_PIN, LOW);
    }
    else if (results.value == 0xFF18E7)   //2开灯
    {
      digitalWrite(LED_PIN, HIGH);
    }

    irrecv.resume();                      // Receive the next value
  }
  delay(100);
}
