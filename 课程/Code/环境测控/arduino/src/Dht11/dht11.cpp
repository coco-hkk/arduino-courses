/*
 *
 *  温湿度传感器模块。
 *
 *  2021/07/18 added by 郝宽宽
 *
 *  1 tab = 2 space
 */

#include <Arduino.h>
#include <dht11.h>

dht11 DHT11;
float temperature, humidity;

/*
 *  @func : 获取温度
 *  @ret  : 返回温度值
 */
float get_temperature() {
  temperature = DHT11.temperature;
  return temperature;
}

/*
 *  @func: 获取湿度
 *  @ret : 返回值为湿度
 */
float get_humidity() {
  humidity = DHT11.humidity;
  return humidity;
}

/*
 *  @func: 打印温度和湿度
 */
void get_dht11_print() {
  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.println("C");
  Serial.print("湿度: ");
  Serial.print(humidity);
  Serial.println("%");

  return;
}

/*
 *  @func : dhtll任务模块
 *  @para1: 入参为管脚编号
 */
void dht11_task(int pin) {
  DHT11.read(pin);

  return;
}
