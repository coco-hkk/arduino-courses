#include <Arduino_FreeRTOS.h>
#include <queue.h>

// 创建任务句柄
TaskHandle_t taskReadHandle;
TaskHandle_t taskPrintHandle;
TaskHandle_t taskInfoHandle;

QueueHandle_t msgQueue;

void setup() {
  Serial.begin(115200);
  while(Serial.read()>= 0){}

  /*创建队列，每个元素是一个包含32个元素的char型数组，长度为4*/
  msgQueue = xQueueCreate(4, 32);

  if( msgQueue != NULL )
  {
    /*创建任务*/
    xTaskCreate(readTask,         // 任务函数
        "Read",          // 任务名
        128,              // 任务分配堆栈
        NULL,
        0,                // 任务优先级
        &taskReadHandle); // 任务句柄

    xTaskCreate(printTask,
        "Print",
        128,
        NULL,
        2,
        &taskPrintHandle);

    xTaskCreate(infoTask,
        "Info",
        128,
        NULL,
        2,
        &taskInfoHandle);
  }
}

void loop(){}

void infoTask(void *pvParameters)
{
  (void) pvParameters;

  /*这里可以放置此任务初始化内容*/

  for (;;)
  {
    Serial.println();
    Serial.println("======== 任务状态 ========");
    Serial.print("Tick count: ");
    Serial.print(xTaskGetTickCount());
    Serial.print(", Task count: ");
    Serial.println(uxTaskGetNumberOfTasks());

    Serial.print("- TASK ");
    Serial.print(pcTaskGetName(taskReadHandle)); // Get task name with handler
    Serial.print(", High Watermark: ");
    Serial.print(uxTaskGetStackHighWaterMark(taskReadHandle));
    Serial.println();

    Serial.print("- TASK ");
    Serial.print(pcTaskGetName(taskPrintHandle));
    Serial.print(", High Watermark: ");
    Serial.print(uxTaskGetStackHighWaterMark(taskPrintHandle));
    Serial.println();

    Serial.print("- TASK ");
    Serial.print(pcTaskGetName(taskInfoHandle));
    Serial.print(", High Watermark: ");
    Serial.print(uxTaskGetStackHighWaterMark(taskInfoHandle));
    Serial.println();

    vTaskDelay( 10000 / portTICK_PERIOD_MS );
  }
}

void printTask(void *pvParameters)
{
  (void) pvParameters;

  // 和初始化队列时，队列元素保持一致
  char msg[32] = {};

  for (;;)
  {
    if(xQueueReceive(msgQueue, &msg, portMAX_DELAY) == pdPASS ){
      Serial.println();
      Serial.print("get msg: ");
      Serial.println(String(msg));  //字符数组转 String 类型
      Serial.println();

      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
}

void readTask(void *pvParameters)
{
  (void) pvParameters;

  String content = "";
  char msg[32] = {};

  for (;;)
  {
    Serial.print("请输入任意内容： ");
    while( Serial.available() <= 0 ){}

    content = Serial.readString();
    content.toCharArray(msg, content.length()); // String类型转字符类型

    xQueueSend(msgQueue, &msg, portMAX_DELAY);
    // One tick delay (15ms) in between reads for stability
    vTaskDelay(1);
  }
}
