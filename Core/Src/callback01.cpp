#include "can.h"
#include "main.h"
#include "tim.h"
#include"motorclass.h"
#include"pid.h"
extern uint8_t tx_data[8];
extern uint8_t rx_data[8];
extern CAN_TxHeaderTypeDef tx_header;
extern CAN_RxHeaderTypeDef rx_header;
extern uint32_t can_tx_mail_box_;
extern int16_t intensity;
M3508_Motor Motor(19.2);
PID pid_();
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (hcan->Instance==CAN1) {
        HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&rx_header,rx_data);
    }
    if (rx_header.StdId==0x201) {

        Motor.canRxMsgCallback(rx_data);
        //Motor.setReferencePoint();
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    Motor.handle();

    if (htim->Instance==htim6.Instance) {
        HAL_CAN_AddTxMessage(&hcan1,&tx_header,tx_data,&can_tx_mail_box_);
    }
}

