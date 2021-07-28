/*
  运行该代码，先修改文件名为合法的变量名。
  
  通过MQTT客户端完成和IOT的互联实验。
  
  1 tab = 2 space
*/

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "5G"                 //你的WI-FI的SSID，注意把你的 WIFI 的 AP 设置成 2.4GHz 频段。
#define WLAN_PASS       "12345678"          //你的WI-FI的密码

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                                //use 8883 for SSL
#define AIO_USERNAME    "vimacs"                            //你在io.adafruit.com上注册的用户名
#define AIO_KEY         "aio_fXfI68eRxaggxe9Swl1ltwGFEysJ"  //你在io.adafruit.com所获得的AIO


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

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Switch");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(1000);

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
  
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);

  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
  Adafruit_MQTT_Subscribe *subscription;
  
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
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

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
  int8_t retries = 10;

  // Stop if already connected.
  if ( mqtt.connected() ) 
  {
    return;
  }

  Serial.println("Connecting to MQTT... ");

  while ( (ret = mqtt.connect()) != 0 )                       // connect will return 0 for connected
  { 
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
