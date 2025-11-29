#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_driver.h"

#define LED1_PIN 2
#define LED2_PIN 4
#define LED3_PIN 5

void task_blink_fast(void *pvParam)
{
  for(;;)
  {
    led_driver_send_cmd(LED1_PIN, LED_CMD_TOGGLE);
    vTaskDelay(pdMS_TO_TICKS(200)); // 200ms
  }
}

void task_blink_medium(void *pvParam)
{
  for (;;)
  {
    led_driver_send_cmd(LED2_PIN, LED_CMD_TOGGLE);
    vTaskDelay(pdMS_TO_TICKS(1000)); // 1 segundo
  }
}

void task_blink_slow(void *pvParam)
{
  for (;;)
  {
    led_driver_send_cmd(LED3_PIN, LED_CMD_ON);
    vTaskDelay(pdMS_TO_TICKS(2000)); // Fica ligado 2s
    
    led_driver_send_cmd(LED3_PIN, LED_CMD_OFF);
    vTaskDelay(pdMS_TO_TICKS(500));  // Fica desligado 0.5s
  }
}

void app_main() {
    led_driver_init();

    xTaskCreate(task_blink_fast, "blink_fast", 2048, NULL, 5, NULL);
    xTaskCreate(task_blink_medium,  "blink_med",  2048, NULL, 5, NULL);
    xTaskCreate(task_blink_slow,  "blink_slow", 2048, NULL, 5, NULL);
}
