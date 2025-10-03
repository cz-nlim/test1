#include "can.h"
#include "main.h"
#include "tim.h"
extern uint8_t tx_data[8];
extern uint8_t rx_data[8];
extern CAN_TxHeaderTypeDef tx_header;
extern CAN_RxHeaderTypeDef rx_header;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (hcan->Instance==CAN1) {
        HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&rx_header,rx_data);
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance==htim6.Instance) {
        HAL_CAN_AddTxMessage(&hcan1,&tx_header,tx_data,CAN_FilterFIFO0);
    }
}

