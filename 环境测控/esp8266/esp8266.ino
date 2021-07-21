/*
   运行该代码，先修改文件名为合法的变量名。

   Arduino Uno 和 NodeMCU ESP8266 之间的串口通信实验。
   Deserialize.

   1 tab = 2 space
 */
 
#include "src/esp8266/esp8266.h"
#include "src/server/server.h"
#include "src/irremote/irremote.h"
#include "src/servo/servo.h"

void setup()
{
  Serial.begin(115200);

  esp8266_serial_init();

  led_init(LED_PIN);
  rgb_init(LED_R_PIN, LED_G_PIN, LED_B_PIN);

  music_init(BEE_PIN);

  IRremote_init();

  servo_init();

  server_config();
}

void loop() {
  read_serial_data();

  IRremote_task();

  server_listen();
}
