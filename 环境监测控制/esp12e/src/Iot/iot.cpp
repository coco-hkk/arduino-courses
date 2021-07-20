/*
 *
 * nodemcu 模块，连接 adafruit 服务器并且发送传感器采集数据。
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "test"
#define WLAN_PASS       "12345678"

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "vimacs"
#define AIO_KEY         "aio_HfzY34SeWQTtSbokOS90LOcOQvbJ"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/switch");

/*
   Function to connect and reconnect as necessary to the MQTT server.  Should be
   called in the loop function and it will take care if connecting.
   */
void MQTT_connect() {
  int8_t ret;
  int8_t retries = 10;

  if ( mqtt.connected() ) {
    return;
  }

  Serial.println("Connecting to MQTT... ");

  while ( (ret = mqtt.connect()) != 0 ) {
    Serial.println( mqtt.connectErrorString(ret) );
    Serial.println("Retrying MQTT connection in 5 seconds...");

    mqtt.disconnect();
    delay(5000);

    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }

  Serial.println("MQTT Connected!");
}

void iot_init() {
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
}

void iot_task() {
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
        Serial.println("开灯");
      }
      if(!value.compareTo("关"))
      {
        Serial.println("关灯");
      }
    }
  }

  int value = analogRead(A0);
  int x = map(value,100,1000,1,100);

  Serial.println();
  Serial.print(F("Sending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! photocell.publish(x))
  {
    Serial.println(F("Failed"));
  }
  else
  {
    Serial.println(F("OK!"));
  }

}
