
#include "tim.h"

    uint32_t count=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim==&htim1) {
        count++;
    }
}
// Created by 29528 on 2025/10/2.
//