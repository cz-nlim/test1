#include <cstring>
#include "main.h"
#include "usart.h"
extern uint8_t rx_msg[4];
uint8_t buffer[4];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart7) {
        HAL_UART_Receive_IT(&huart7, rx_msg, 3);
        memcpy(buffer, rx_msg, 3);
        HAL_UART_Transmit_IT(&huart7, buffer, 10);
    }
}
