/*
 *
 *  Arduino Uno 实验中所使用的所有管脚
 *
 *  2021/07/19 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#ifndef ARDUINO_H
#define ARDUINO_H
#endif

#include "../common/gpio.h"
#include "../common/soft_serial.h"

#define DHT11_PIN (D3)  //温湿度传感器管脚

#define PHOTORESISTOR_PIN (A0) //光敏传感器管脚

#define YL69_A0_PIN   (A1)  //土壤湿度传感器
#define YL69_D0_PIN   (D2)

#define ULTRASONIC_WAVE_TRIGGER (D5)  //超声波测距传感器
#define ULTRASONIC_WAVE_ECHO    (D4)

#define MQ9_D0_PIN  (D7)    //MQ9可燃气体传感器
#define MQ9_A0_PIN  (A2)

#define PM25_LEDPOWER_PIN (D8)    //PM2.5传感器
#define PM25_MEASURE_PIN  (A3)

#define SERIAL_RX (D10)   //软串口通信管脚
#define SERIAL_TX (D11)

#define ARDUINO_RESET   (D12)   //重启 Arduino Uno

/*
 *  @func : 初始化 arduino 串口
 */
void arduino_serial_init();

/*
 *  @func : arduino 发送传感器数据
 *  @para1: 传感器数据
 */
void arduino_send_sensor_data(const mcu_msg& data);

/*
 *  @func : arduino 处理接收到的数据
 *  @para1: 接收到的数据
 */
void read_serial_data();
