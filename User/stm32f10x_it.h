#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led30.h"
#include "global.h"
//#include "string.h"

	 
void Led_Breath_Int(uint8_t enable, uint8_t color, uint8_t BreathTime);	//呼吸灯 是否允许 控制颜色和间隔时间（ms）
void Led_Rotate_Int(uint8_t enable, uint8_t changeTime, uint8_t mode);	//changeTime:转动的间隔时间 mode:选择旋转灯的模式


#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

/****************************/	 
//void NMI_Handler(void);
//void HardFault_Handler(void);
//void MemManage_Handler(void);
//void BusFault_Handler(void);
//void UsageFault_Handler(void);
//void SVC_Handler(void);
//void DebugMon_Handler(void);
//void PendSV_Handler(void);
//void SysTick_Handler(void);
/****************************/
