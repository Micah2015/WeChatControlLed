#include "tim3.h"

void TIM3_Config(void)	
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Time base configuration */		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	TIM_DeInit(TIM3); 
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1;  //    ��ʱ 1����
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;	    //
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);							    		/* �������жϱ�־ */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
	TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR
	TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3
  /*�ж�����*/  													
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //���ȼ����ڴ����ж�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

