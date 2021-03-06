# 实训注意事项

1. 分组。三人一组，确认组长，确认小组编号，确认组员分工（代码、硬件、调试）。
2. 领取设备。分组数量取决于设备数量，有的小组可能超过三个成员。
3. 课件及示例代码地址 `https://github.com/coco-hkk/arduino`。

---

1. 注意按照标准操作使用元器件和各种传感器，防止操作不当损坏。
2. 搭建电路前先想一想怎么才能简洁美观。良好的布线有利于调试。如，合理使用不同颜
   色和不同长度的导线，充分利用面包板的特性。
3. 注意器件驱动电压的范围，3.3V 驱动不了 5V 的设备。

---

### `建议回顾 C 语言基础知识`

0. 变量的概念、类型、作用域。
1. 数组及二维数组概念和基本操作。
2. 位 bit 的概念和操作。二进制和十六进制概念和它们之间的转换。
3. 结构体概念和操作。
4. 函数定义和使用。如，函数声明必须要有分号；函数调用必须要加括号和参数；变量一
   定先定义后使用。
5. 宏定义的概念和使用。

# 实训成果物

1. 按分组提交成果物，提交的文件夹以小组编号命名。例如，`第一组`。
2. 成果物提交内容（文件夹）：`学生日报（周报）`、`代码`、`环境配置手册`、`实训总结`、
   `详细设计说明书`、`项目实训小组答辩PPT`。
3. `学生日报` —— 包括每日实验的代码、电路和实验结果（截图或视频）。保存在以日期命名
   文件夹，例如，`20220711`。每组一份即可，但不能和示例一样。关于每日（周）心得总结每
   人一份，保存在以 `学号+姓名` 创建的文件夹中即可。
4. `代码` —— 指最终项目的代码、电路和实验结果（截图或视频）。每组一份。
5. `环境配置手册` —— 指安装编程环境的步骤笔记。每组一份。
6. `详细设计说明书` —— 指将最终项目实现哪些功能，以及功能是怎么实现的形成书面文档（
   提示：可以使用流程图、电路绘图工具）。每组一份。
7. `项目实训小组答辩PPT` —— PPT内容需要干货，体现自己辛苦和感谢其他人的内容一页即可。
   干货比如，你的实验实现哪些功能，采用什么模块，怎么利用模块实现功能，取得数据
   后如何分析、分析结果如何显示或警报、如何显示分析结果更美观；在这个过程中遇到
   了什么问题、如何解决、学到了什么；有什么好的想法曾尝试实现过，做到了哪一步，
   为什么失败。总之凡是和我们最终项目有关且你尝试过都可以体现在PPT中。

# 实验环境

- WIN10 64 位 家庭版
- Arduino IDE arduino-2.0.0 RC8（从[这里](https://www.arduino.cc/en/software) 获取）
- 电路设计工具 [fritzing](https://fritzing.org/download) 或 Github [fritzing](https://github.com/fritzing/fritzing-app/releases) 选择合适自己的版本。
- Arduino UNO 开发板
- ESP8266MOD 开发板
- ESP8266-12E(NodeMCU 1.0) 开发板
- DS1302 [库文件](http://osoyoo.com/2016/07/26/ds1302_clock_module/)
- ArduinoStreamUtils [库文件](https://github.com/bblanchon/ArduinoStreamUtils)。

# Arduino 实训目标

实现局部气象检测系统的部分功能。具体点，利用各种传感器采集气象相关数据，通过程序
将分析结果显示，或通知或预警，然后用户通过终端控制设备状态。实验要求必须有联网应
用。

从项目目标分析，内容主要分为三部分：
- 传感器。学习和使用各类传感器，实现数据采集。
- 显示状态的元器件。学习和使用各类元器件，包括显示类、通知和报警类。显示类，如，
  LED、LCD、数码管、RGB 三基色 LED；通知和报警类，如，LED、LCD、蜂鸣器等。
- 联网。使用带 WIFI 模块的 NODEMCU 实现，NODEMCU 既可以作为服务器又可以作为客户
  端。
- 其它器件。如，3-8 译码器、舵机、步进电机等控制类的器件。

**课程内容**

1. 掌握串口输出数据和日志。
2. 掌握程序控制（读写）硬件接口、管脚。
3. 掌握使用 Arduino IDE 查找、安装库文件。掌握三种安装库文件方法。
4. 了解如何从零构建一个项目过程。
5. 了解如何查阅硬件和库的使用手册，了解如何学习一个硬件和软件库的流程。
6. 了解调试。学会查看错误日志，即查看 Arduino IDE 控制台（下面黑色输出窗口）消息。
7. 了解硬件和硬件、硬件和软件的数据传输、通讯。
8. 了解两个设备间通过串口通信的方法。

# 实验内容

1. 搭建开发环境。
2. 串口实验。实现串口输入、输出。
3. LED 控制实验。实现跑马灯、交通信号灯模拟。
4. 电位器实验。获取电位器输出模拟值、电位器控制 LED。
5. 数码管实验。实现单位数码管显示数字、秒表功能，4 段数码管实现计数器。
6. LCD 屏实验。实现显示英文并左右或循环移动内容。
7. 按键模块实验。实现按键控制 LED 行为，实现抢答器。
8. 蜂鸣器实验。播放音乐。
9. 键盘实验。
10. 光敏电阻实验。
11. RGB 三基色 LED 实验。
12. 舵机实验。点击旋转 180 度，电位器控制舵机转动。
13. DS1302 时钟实验。显示日期和时间。
14. 红外遥控实验。控制 LED 灯。
15. 超声波测距实验。控制 LED 灯。
16. 声控实验。控制 LED 灯。
17. DHT11 温湿度传感器实验。
18. 步进电机实验。通过电位器控制步进电机转动。
19. NodeMCU/ESP8266 本地数据发布。MCU 创建服务器并给客户端发送传感器数据。
20. NodeMCU/ESP8266 本地传感器控制。利用客户端控制 MCU 外围设备、传感器。
21. 通过 MQTT 客户端完成与 IOT 的互联。
22. MQ-9 可燃气体传感器。
23. PM2.5 传感器。
24. YL-69 土壤湿度传感器。
25. 设备间串口通信。

# 实验问题

**实验结果不符合预期**

0. 调试一定要有耐心。
1. 检查搭建的电路是否正确。如，是否短路、正负极是否接反、导线是否插好后掉了等。
2. 检查上传 / 烧录的代码是否和电路匹配。
3. 检查元器件是否有问题。如，导线、面包板插孔、LED、传感器等，总之一切合理的怀疑
   点都值得去考虑。

**问题汇总**

- ArduinoUNO会将大于3V的输入电压视为高电平识别，小于1.5V的电压视为低电平识别。

- 设备管理器中找不到 Arduino 的端口号
  1. 确保 Arduino 和电脑通过 USB 连接。
  2. 确保 Arduino 设备驱动正确安装。
  3. 确保 Arduino 的电路正确。
  4. 重启电脑。

- Arduino Uno 驱动不能正常安装
  1. 安装目录 0 中的 `Nodemcu_ESP-12E驱动.7z` 解压后的文件。

- 串口输出乱码
  1. 确保串口输出工具和代码中波特率设置一致。比如 115200.

- 无法上传 / 烧录
  1. 确保其它串口工具没有占用 COM 端口。
  2. 确保选择了 COM 端口并且是正确的端口。
  3. 重新插拔 Arduino 设备。
  4. 重启 Arduino IDE。
  5. 检查电路是否正确，注意是否短路和正负极接反。

- 缺少库文件，一般会报错：找不到 xxxx.h 头文件。
  1. 在 Arduino IDE 菜单栏中找到 `项目 ->加载库 ->管理库`，在这里面搜索需要的库
     ，然后安装即可。
  2. 可以在网上找库文件，然后通过 `项目 ->加载库 ->添加.zip 库`，将自己找的库文件
     加载到项目中。
  3. 可以自己手动解压，然后把解压后的目录（文件夹）放在 `项目文件夹位置` 目录
     下的 `libraries` 目录中。
  - 在 `项目 ->加载库` 即可找到是否加载已安装的库模块（需要重启 IDE 才可以看到）。

- 代码一定要使用英文（注释除外），确保空格、换行是由英文半角状态输出。

- 电路没问题步进电机没法正常转动（类似还有 LCD）。
  1. 换一下导线，或换一下面包板上的位置。
  2. 使用 5V 电压，而不是 3V。

- LED 灯不亮
  1. 保证 LED 是正常未损毁的。
  2. 保证电路没问题，导线没有接错。
  3. 也可能是和 LED 串联的电阻阻值过大导致。

- 红外遥控实验可能会提示所用函数被抛弃，导致不能正常编译，或串口不能正常显示。
  1. 删除 libraries 目录中的 IRremote 库。
  2. 重新安装 IRremote 模块。

- 上传代码报错：esptool.FatalError: Failed to connect to ESP8266: Timed out waiting for packet header
  1. 换一下数据线，换一下端口。
  2. 拔掉电源，摁住 FLASH 按键，插上电源，开始烧录，直到重启设备松开 FLASH 按键。

- Arduino Uno 上传代码时，报错：not in sync.
  1. 在电路中不要使用端口 0 和 1，它们专门为硬件串口通信设计。

- NodeMCU 和 Arduino 软串口通信，报错：empty input
  1. 检查串口绑定的端口必须是 PWM 类型。
  2. 检查 NodeMCU 的接收端口是否是 Arduino 的发送端口。反之亦然。
  3. 打印从串口取得的数据，对比发送端，是否一致。若一致，那么可能是因为发送端
     没有发送数据，接收端只能接收到空输入了。

- NodeMCU 和 Arduino 软串口通信，报错：InvalidInput
  1. 时钟偏差。只能在两侧使用相同的MCU。
  2. 接线不良/电噪声。
  3. 接收器读取速度太慢并丢失字节。
  4. 电压不匹配。

# 实训项目注意事项

0. 做项目时，首先考虑总体设计，最好输出一份设计大纲，然后再动手搭建电路和写代码。
1. 使用函数封装不同硬件模块代码。
2. 单块板子管脚不够使用，可采用多块板子做实验。板子之间可通过软件串口通信实现数
   据交流。
3. 使用软串口通信时，需要合理设计串口通信的数据结构。确保两边设备封装和解析数据
   一致。
4. 网页参考教程 [html](https://www.runoob.com/html/html-basic.html) 小节 4-9。

# 总结

1. 对于器件，只需要知道它的引脚（管脚、端口）功能是什么？输入还是输出？（自己查
   资料）。
2. 考虑如何合理使用 Arduino 或 ESP8266 的引脚，将它们和器件引脚相连接。（电路假
   设已经搭建好了）。
3. 根据器件引脚功能，初始化连接到 MCU 引脚的模式（INPUT 还是 OUTPUT）。
4. 对于数字管脚使用 digitalRead 和 digitalWrite 读取和写入，对于模拟管脚使用
   analogRead 和 analogWrite 读取和写入。程序读取引脚值写入变量，这个变量就可以
   按照要求处理，处理后可以写入管脚，继而控制器件。重点在于程序。
