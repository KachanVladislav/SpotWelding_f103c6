#ifndef MAINAPP_H_
#define MAINAPP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f1xx_hal.h"

void MainApp();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#ifdef __cplusplus
}
#endif

#endif /* MAINAPP_H_ */
