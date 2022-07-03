如果实在不知道哪里出错，就重新插拔开发板或重启 Arduino IDE，Windows 环境太复杂了。

# Arduino IDE

1. 官网下载地址 `https://www.arduino.cc/en/software`.
2. 可以下载 1.x 版本或 2.x 版本。建议下载 1.8.19 版本，2.0.0 RC8 不稳定总是出现意料外的问题。
3. 一般安装好 IDE 后，Arduino 的开发板管理已经将 Arduino 开发环境配置好了，只需选择 Arduino UNO 即可。
4. 若没安装 `Arduino AVR Boards`

   打开 `开发板管理器` 搜索 `Arduino AVR Boards` 安装.

5. 使用串口时，确保 `串口波特率` 和代码设置一致，统一为 115200.
3. 确保代码真的上传到了开发板，注意成功提醒。若没提醒重新插拔设备。

# Arduino UNO

1. 一般来说，只要 UNO 开发接到电脑上会自动安装驱动，若没有可先安装 Arduino IDE。
2. 插跳线时，注意开发板端口，不要插错。
3. 电路布线时保持飒爽，跳线之间不要紧挨在一起，看好端口再插线，不仔细容易错位。
4. LED 注意正负极。
5. LED 搭配电阻时，要注意电阻阻值不要过大，否则 LED 可能不亮。

# 代码

1. 串口初始化函数 `Serial.begin(115200)`
2. 串口输出函数 `Serial.println("string.")`
3. Arduino 端口初始化函数 `pinMode(pin, mode)`
4. 数字端口输出函数 `digitalWrite(pin, value)`
5. 数字端口值读取函数 `digitalRead(pin)`
6. 延时函数 `delay()` 单位为 ms
7. 常量 `LOW` 表示低电平，即为 0v
8. 常量 `HIGH` 表示高电平，即为 5v
9. 模拟端口输入值读取函数 `analogRead(pin)`，返回值取值范围为 0~1023