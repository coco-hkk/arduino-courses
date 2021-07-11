# 设备间串口通信

1. 设备间串口通信实训不做要求，可能有的同学发现 NodeMCU 管脚不够用，使用这种方式解决。
2. 实例实现 Arduino Uno 和 NodeMcu ESP8266 通过软串口通信。当然 NodeMCU 之间也可以使用。
3. 软串口使用 Arduino 官方内置库 SoftwareSerial 实现，无需额外安装。
4. 串口数据内容使用Json格式，使用第三方库 ArduinoJson，可通过 Arduino IDE 库管理安装。

# 注意事项

1. 本实例使用的是 ArduinoJson V6 版本，V5 版本在目录 V5 中。
2. 实例使用的是静态方式（StaticJsonDocument）申请的通信缓存，官方建议传输小于 1KB 的数据。
3. 两个设备串口通信，一端的输出是另一端的输入，注意不要接错导线。