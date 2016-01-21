#include "tim3.h"

void TIM3_Config(void)	
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Time base configuration */		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	TIM_DeInit(TIM3); 
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1;  //    定时 1毫秒
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;	    //
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
	TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR
	TIM_Cmd(TIM3, ENABLE);                   //使能定时器3
  /*中断配置*/  													
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //优先级低于串口中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

