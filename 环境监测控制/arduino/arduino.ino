#include "src/arduino/arduino.h"
#include "src/common/soft_serial.h"

#include "src/dht11/dht11.h"
#include "src/photoresistor/photoresistor.h"
#include "src/yl69/yl69.h"
#include "src/ultrasonicwave/ultrasonicwave.h"
#include "src/mq9/mq9.h"
#include "src/pm25/pm25.h"

float MQ9_R0;

void sensor_data_collection(mcu_msg& uno_msg) {
  float temperature,
        humidity,
        obstacle_distance,
        pm25_dust_denisty,
        mq9_ratio,
        mq9_alarm,
        yl69_analog_value,
        photoresistor;

  temperature = get_temperature();
  humidity = get_humidity();
  obstacle_distance = get_ultrasonicwave_distance();
  pm25_dust_denisty = get_pm25_dust_density();
  mq9_ratio = get_mq9_rs_r0_ratio();
  mq9_alarm = is_mq9_alarm();
  yl69_analog_value = get_YL69_A0_value();
  photoresistor = get_photoresistor_value(PHOTORESISTOR_PIN);

  get_YL69_D0_value();

  get_dht11_print();
  get_photoresistor_print();
  get_YL69_print();
  get_ultrasonicwave_distance_print();

  uno_msg.id                            = ARDUINO_SENSOR_MSG;
  uno_msg.msg.uno_sensor_msg.temperature       = temperature;
  uno_msg.msg.uno_sensor_msg.humidity          = humidity;
  uno_msg.msg.uno_sensor_msg.obstacle_distance = obstacle_distance;
  uno_msg.msg.uno_sensor_msg.pm25_dust_denisty = pm25_dust_denisty;
  uno_msg.msg.uno_sensor_msg.mq9_ratio         = mq9_ratio;
  uno_msg.msg.uno_sensor_msg.mq9_alarm         = mq9_alarm;
  uno_msg.msg.uno_sensor_msg.yl69_analog_value = yl69_analog_value;
  uno_msg.msg.uno_sensor_msg.photoresistor     = photoresistor;
}

void setup() {
  Serial.begin(115200);             //串口初始化
  arduino_serial_init();
  
  YL69_init(YL69_D0_PIN, YL69_A0_PIN);
  ultrasonicwave_init(ULTRASONIC_WAVE_TRIGGER, ULTRASONIC_WAVE_ECHO);

  mq9_init(MQ9_D0_PIN);
  mq9_calibration(MQ9_A0_PIN);      //正常需要预热15分钟，这里不预热。
  MQ9_R0 = get_mq9_R0();

  pm25_init(PM25_LEDPOWER_PIN);
}

void loop() {
  mcu_msg uno_msg;

  dht11_task(DHT11_PIN);
  ultrasonicwave_task();
  mq9_task(MQ9_A0_PIN,MQ9_R0);
  pm25_task(PM25_MEASURE_PIN);

  sensor_data_collection(uno_msg);
  arduino_send_sensor_data(uno_msg);

  Serial.println();
  delay(5000);
}
