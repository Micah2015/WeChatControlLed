#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"
#include "global.h"
//#include "string.h"

void Code_0(void);
void Code_1(void);
void Led_Code(uint8_t v);
void delay_50us(void);	//��ʱ50us

void GPIO_Init_led30(void);	//led30��GPIOʹ��
void Led_Write_Single(uint8_t red, uint8_t green, uint8_t blue);	//ͨ��RGB����һ��led��ɫ��
void Led30_Stop(void); //ֹͣ���������
void Led_Rotate(uint8_t* buf_R,uint8_t* buf_G,uint8_t* buf_B);	//��˳ʱ��ת������ʱ��ת �ƶ�һ����ʱ
//void Led_Breath(uint8_t* buf_R,uint8_t* buf_G,uint8_t* buf_B);	//������
//void Led_Breath(uint8_t num);	//������
void Led_Breath(uint8_t color, uint8_t BreathWaveCount);	//������
void Led_Write_All(uint8_t red, uint8_t green, uint8_t blue);
void delay_1s(uint8_t t);	//��׼
void delay_5ms_t(uint8_t t);	//Լ5ms
void shutDownAll(void);	//ȷ���ر����е�
#endif
