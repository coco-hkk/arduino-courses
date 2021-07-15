/*
    同学们的代码非常不规范，不方便阅读和调试。这个文件做一些代码规范，以及项目框
    架的模板。

    命名风格
    1. 变量命名：下划线小写风格。如，humidity_value。
    2. 函数命名：下划线小写风格。如，get_humidity()。
    3. 宏命名：下划线大写风格。如，#define LED_PIN (0)

    布局风格：按照文件从上到下顺序依次组织代码
    1. 文件描述。如本注释快内容。
    2. 头文件引用。如，#include <Arduino.h>
    3. 宏定义。如，#define LED_PIN (0)
    4. 结构体定义。
    5. 全局变量定义。如，int humidity_value。
    6. 函数定义。如，void func_module() {}。
    7. setup()
    8. loop()

    注：本文件仅仅是模板。

    1 tab = 2 space
 */

/********************************** include **********************************/
/*引用你的项目中需要的头文件*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <dht11.h>

/*********************************** macro ***********************************/
/*定义你的项目中需要的宏，宏要大写，本例是关于 NODEMCU 引脚映射的宏*/
#define     D1      (5)
#define     D2      (4)
#define     D3      (0)
#define     D4      (2)
#define     D5      (14)
#define     D6      (12)
#define     D7      (13)
#define     D8      (15)
#define     D9      (3)
#define     D10     (1)
#define     D11     (9)
#define     D12     (10)

/******************************* structure definition ************************/
/*该结构体是两块设备间通过串口通信时的数据模板*/
typedef struct {
    int id;             //用于标识消息是由哪个模块传递
    union {             //传递内容，可以是任何 Arduino 支持的类型，这里是 int。
        int id0_data;
        int id1_data;
        char id2_data;
        float id3_data;
    } data;
} message;

/******************************* global variable *****************************/
/*定义你的项目需要的全局变量，并初始化*/
int humidity_value = 0;
int temperature_value =0;

SoftwareSerial sw_serial(D1,D2);

/******************************* function definition *************************/
/*定义你的项目需要的函数*/
/*比如带 init 的函数我把它看做模块初始化函数*/
void temperature_humidity_sensor_init() {
  /*根据之前实验所学，进行初始化*/
  return;
}

void module0_init() {
  /*你的代码*/
  return;
}

void module1_init() {
  /*你的代码*/
  return;
}

void module0_process() {
  /*模块0消息处理程序*/
  return;
}

/*Arduino 和 NODEMCU 之间串口初始化*/
void serial_init() {
  /*你的代码*/
  sw_serial.begin(9600);
  return;
}

/*通过 Arduino 和 NodeMCU 之间串口得到的消息*/
void dispatch() {
  message serial_msg;
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, sw_serial);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  JsonObject root = doc.as<JsonObject>(); // get the root object

  serial_msg.id = (int)root["id"];

  switch(serial_msg.id) {
    case 0:
      Serial.println("消息来自 ID 为 0 的模块，这里处理模块 0 相关内容。");
      serial_msg.id0_data = (int)root["data"];
      module0_process();
      break;
    case 1:
      Serial.println("消息来自 ID 为 1 的模块，这里处理模块 1 相关内容。");
      break;
    defalut:
      break;
  }
  return;
}

/* setup 函数 */
void setup() {
  Serial.begin(115200);
  serial_init();

  temperature_humidity_sensor_init();

  /*其它模块初始化代码……*/
}

/* 主循环 loop 函数 */
void loop() {
  dispatch();
}

