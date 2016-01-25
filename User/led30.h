#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"
#include "global.h"
//#include "string.h"

void Code_0(void);
void Code_1(void);
void Led_Code(uint8_t v);
void delay_50us(void);	//延时50us

void GPIO_Init_led30(void);	//led30的GPIO使能
void Led_Write_Single(uint8_t red, uint8_t green, uint8_t blue);	//通过RGB控制一个led三色灯
void Led30_Stop(void); //停止向后传输数据
void Led_Rotate(uint8_t* buf_R,uint8_t* buf_G,uint8_t* buf_B);	//外顺时针转，内逆时针转 移动一次延时
//void Led_Breath(uint8_t* buf_R,uint8_t* buf_G,uint8_t* buf_B);	//呼吸灯
//void Led_Breath(uint8_t num);	//呼吸灯
void Led_Breath(uint8_t color, uint8_t BreathWaveCount);	//呼吸灯
void Led_Write_All(uint8_t red, uint8_t green, uint8_t blue);
void delay_1s(uint8_t t);	//不准
void delay_5ms_t(uint8_t t);	//约5ms
void shutDownAll(void);	//确保关闭所有灯
#endif
