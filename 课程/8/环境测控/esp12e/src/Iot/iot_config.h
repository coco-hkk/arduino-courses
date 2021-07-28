/*
 *
 *  adafruit config
 *
 *  2021/07/20 added by 郝宽宽
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
#define AIO_KEY         "aio_AZpT81fm84Y0nkF38FjLCOt4wUVW"
