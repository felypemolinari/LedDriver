# Driver de LED Assíncrono com FreeRTOS (ESP-IDF)

Este projeto implementa uma arquitetura de **Device Driver** baseada em filas (Queues) do FreeRTOS para o controle de LEDs no ESP32. O objetivo é demonstrar o desacoplamento entre a lógica de aplicação (Tasks) e o controle de hardware.

## Descrição do Projeto

Diferente de uma abordagem tradicional ("Super Loop" ou acesso direto aos registros), este projeto utiliza o padrão **Produtor-Consumidor**:

1.  **Driver (Consumidor):** Uma tarefa dedicada que gerencia o hardware (GPIOs). Ela permanece bloqueada até receber comandos via Fila.
2.  **Tasks de Aplicação (Produtores):** Tarefas independentes que enviam comandos de alto nível (`ON`, `OFF`, `TOGGLE`) para o driver, sem bloquear seu próprio fluxo de execução.

### Funcionalidades
* **Segurança de Thread:** Múltiplas tarefas podem tentar controlar LEDs simultaneamente sem conflito de hardware, pois a Fila serializa os pedidos.
* **Não-Bloqueante:** O envio de comandos é imediato; a tarefa que pede para acender o LED não precisa esperar o LED acender de fato.
* **Escalabilidade:** Fácil adição de novos LEDs ou comandos sem alterar a lógica das tarefas existentes.

## Hardware Utilizado

* Microcontrolador: **ESP32**
* 3x LEDs (Cores variadas)
* 3x Resistores (220Ω)

### Pinagem (GPIOs)

| Componente | GPIO (ESP32) | Descrição |
| :--- | :--- | :--- |
| **LED 1** | GPIO 02 | Pisca Rápido (200ms) |
| **LED 2** | GPIO 04 | Pisca Médio (1000ms) |
| **LED 3** | GPIO 05 | Pisca Lento/Irregular |

## Estrutura de Arquivos

```text
├── main/
│   ├── main.c           # Criação das Tasks e setup inicial
│   ├── led_driver.c     # Implementação da Tarefa do Driver e lógica da Fila
│   ├── led_driver.h     # Interface pública (API) do Driver
└── README.md
```

## Link do projeto no Wokwi
https://wokwi.com/projects/448953454245071873