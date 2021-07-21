/*
 *
 * nodemcu 模块，连接 adafruit 服务器并且发送传感器采集数据。
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include "../esp12e/esp12e.h"
#include "../lcd/lcd.h"
#include "../led/led.h"
#include "iot_config.h"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/*发布数据*/
Adafruit_MQTT_Publish _temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish _humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish _obstacle_distance = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/obstacle_distance");
Adafruit_MQTT_Publish _pm25_dust_denisty = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pm25_dust_denisty");
Adafruit_MQTT_Publish _mq9_ratio = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/mq9_ratio");
Adafruit_MQTT_Publish _mq9_alarm = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/mq9_alarm");
Adafruit_MQTT_Publish _yl69_analog_value = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/yl69_analog_value");
Adafruit_MQTT_Publish _photoresistor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photoresistor");

/*订阅*/
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/switch");
Adafruit_MQTT_Subscribe lcd_text = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/lcd");

float temperature,
      humidity,
      obstacle_distance,
      pm25_dust_denisty,
      mq9_ratio,
      mq9_alarm,
      yl69_analog_value,
      photoresistor;

unsigned char publish_flag;

void MQTT_connect() {
  int8_t ret;
  int8_t retries = 50;

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
      while (1);                //等待 WDT 超时重启
    }
  }

  Serial.println("MQTT Connected!");
}

void get_sensor_data(mcu_msg& data) {
  publish_flag = 1;

  temperature       = data.msg.uno_sensor_msg.temperature;
  humidity          = data.msg.uno_sensor_msg.humidity;
  obstacle_distance = data.msg.uno_sensor_msg.obstacle_distance;
  pm25_dust_denisty = data.msg.uno_sensor_msg.pm25_dust_denisty;
  mq9_ratio         = data.msg.uno_sensor_msg.mq9_ratio;
  mq9_alarm         = data.msg.uno_sensor_msg.mq9_alarm;
  yl69_analog_value = data.msg.uno_sensor_msg.yl69_analog_value;
  photoresistor     = data.msg.uno_sensor_msg.photoresistor;
}

/*
 *  @func : 传感器数据发布
 */
static void publish_sensor_data() {
  publish_flag = 0;

  Serial.print(F("Sending sensor data ……"));

  _temperature.publish(temperature);
  _humidity.publish(humidity);
  _obstacle_distance.publish(obstacle_distance);
  _pm25_dust_denisty.publish(pm25_dust_denisty);
  _mq9_ratio.publish(mq9_ratio);
  _mq9_alarm.publish(mq9_alarm);
  _yl69_analog_value.publish(yl69_analog_value);

  if (!_photoresistor.publish(photoresistor)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}

/*
 *  @func : 订阅处理
 */
static void subscribe_info() {
  Adafruit_MQTT_Subscribe *subscription;

  MQTT_connect();

  while ( (subscription = mqtt.readSubscription(5000)) ) {
    if (subscription == &onoffbutton) {

      Serial.print("Got: ");
      String value = (char *)onoffbutton.lastread;

      Serial.println(value);
      if(!value.compareTo("开"))
      {
        Serial.println("开灯");
        led_write_high();
      }
      if(!value.compareTo("关"))
      {
        Serial.println("关灯");
        led_write_low();
      }
    } else if (subscription == &lcd_text) {

      Serial.print("LCD: ");
      String lcd_str = (char *)lcd_text.lastread;

      Serial.println(lcd_str);
      lcd_set_value(lcd_str);
    }
  }
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

  mqtt.subscribe(&onoffbutton);
  mqtt.subscribe(&lcd_text);
}

void iot_task() {
  if ( 1 == publish_flag )
    publish_sensor_data();

  subscribe_info();
}
