/*
   运行该代码，先修改文件名为合法的变量名。

   通过MQTT客户端完成和IOT的互联实验。

   1 tab = 2 space
 */

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "5G"                                //你的WI-FI的SSID，注意把你的 WIFI 的 AP 设置成 2.4GHz 频段。
#define WLAN_PASS       "12345678"                          //你的WI-FI的密码

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"                    //adafruit 官网
#define AIO_SERVERPORT  1883                                 //use 8883 for SSL
#define AIO_USERNAME    "vimacs"                             //你在 io.adafruit.com 上注册的用户名
#define AIO_KEY         "aio_fXfI68eRxaggxe9Swl1ltwGFEysJ"   //你在 io.adafruit.com 所获得的 AIO

/************ Global State (you don't need to change this!) ******************/
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13

#define LED_PIN D6

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
// Setup a feed called 'publish_data' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish publish_data = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/display");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/switch");

/*************************** Code ************************************/
void MQTT_connect();

void setup() {
  Serial.begin(115200);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);

  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  Adafruit_MQTT_Subscribe *subscription;
  
  MQTT_connect();

  while ( (subscription = mqtt.readSubscription(5000)) )
  {
    if (subscription == &onoffbutton)
    {
      Serial.print(F("Got: "));
      String value = (char *)onoffbutton.lastread;

      Serial.println(value);
      if(!value.compareTo("开"))
      {
        digitalWrite(LED_PIN,HIGH);
      }
      if(!value.compareTo("关"))
      {
        digitalWrite(LED_PIN,LOW);
      }
    }
  }

  // Now we can publish stuff!
  int value = analogRead(A0);
  int data = map(value,100,1000,1,100);

  Serial.println();
  Serial.print(F("Sending publish_data value "));
  Serial.print(data);
  Serial.print("...");

  if (! publish_data.publish(data))
  {
    Serial.println(F(" Failed!"));
  }
  else
  {
    Serial.println(F(" OK!"));
  }
}

/*
  连接 MQTT server，失败后重试。若仍然失败则等待设备重启
  */
void MQTT_connect() {
  int8_t ret;
  int8_t retries = 10;

  if ( mqtt.connected() )    // 若已连接则返回
  {
    return;
  }

  Serial.println("Connecting to MQTT... ");

  while ( (ret = mqtt.connect()) != 0 )
  {
    Serial.println( mqtt.connectErrorString(ret) );
    Serial.println("Retrying MQTT connection in 5 seconds...");

    mqtt.disconnect();
    delay(5000);

    retries--;
    Serial.print("Remaining attempts ");
    Serial.print(retries);
    Serial.println(" times");
    
    if (retries == 0)
    {
      while (1);        // 阻塞在这里，等待看门狗超时，重启设备
    }
  }

  Serial.println("MQTT Connected!");
}
