#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

// comandos suportados pelo driver
typedef enum 
{
    LED_CMD_ON,
    LED_CMD_OFF,
    LED_CMD_TOGGLE
} led_cmd_t;

// estrutura da mensagem enviada para a fila
typedef struct 
{
    int pin;        // qual GPIO controlar
    led_cmd_t cmd;  // qual comando executar
} led_msg_t;

int led_driver_init(void);

void led_driver_send_cmd(int pin, led_cmd_t cmd);

#endif // LED_DRIVER_H