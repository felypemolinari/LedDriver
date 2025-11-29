#include "led_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

// Handle da Fila
static QueueHandle_t led_queue = NULL;

static void led_driver_task(void *arg)
{
  led_msg_t msg;

  printf("Driver de LED Iniciado\r\n");

  for (;;)
  {
    // Bloqueia a tarefa até chegar uma mensagem (portMAX_DELAY = espera infinita)
    if (xQueueReceive(led_queue, &msg, portMAX_DELAY))
    {
      // Configura o pino como saída automaticamente
      // (Fazemos isso aqui para o usuário não precisar configurar manualmente)
      gpio_reset_pin(msg.pin);
      gpio_set_direction(msg.pin, GPIO_MODE_OUTPUT);

      int current_level = gpio_get_level(msg.pin);

      switch (msg.cmd)
      {
        case LED_CMD_ON:
          gpio_set_level(msg.pin, 1);
          printf("GPIO %d: LIGADO\r\n", msg.pin);
          break;

        case LED_CMD_OFF:
          gpio_set_level(msg.pin, 0);
          printf("GPIO %d: DESLIGADO\r\n", msg.pin);
          break;

        case LED_CMD_TOGGLE:
          int newState = !current_level;
          gpio_set_level(msg.pin, !current_level);

          printf("GPIO %d: TOGGLE para %d\n", msg.pin, newState);
          break;
      }
    }
  }
}

int led_driver_init(void)
{
  led_queue = xQueueCreate(10, sizeof(led_msg_t));
  if (led_queue == NULL)
  {
    printf("Falha ao criar a fila");
    return -1;
  }

  BaseType_t res = xTaskCreate(
    led_driver_task,
    "led_driver_task",
    2048,
    NULL,
    5,
    NULL
    );

  if (res != pdPASS) 
  {
      printf("Falha ao criar tarefa");
      return -1;
  }

  return 0;
}

void led_driver_send_cmd(int pin, led_cmd_t cmd)
{
  led_msg_t msg;
  msg.pin = pin;
  msg.cmd = cmd;

  if (led_queue == NULL) return;

  xQueueSend(led_queue, &msg, 0);
}
