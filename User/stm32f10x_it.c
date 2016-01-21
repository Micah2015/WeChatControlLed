#include "stm32f10x_it.h"

uint16_t tim3=0;	//1ms 加1
uint16_t usart1FreeTime=0;	//串口1空闲时间
uint8_t ReceiveBuffer[BufferLength];	//串口缓存
uint16_t WriteSP=0;	//串口写指针

uint8_t usart1ReceiveFlag = 0; //串口接收到数据

Led_Breath_Status LBS={0,0,15,0};
Led_Breath_Status *pBreathStatus=&LBS;

void USART1_IRQHandler(void)	//中断串口接受程序
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //串口接收非空
	{		
		usart1FreeTime = 0;	//串口空闲时间 串口接收到数据置0
		ReceiveBuffer[WriteSP++] =  USART_ReceiveData(USART1); //接收1个字节
		usart1ReceiveFlag = 1;
	}	
} 

void TIM3_IRQHandler(void)	//定时器3 每1ms进入一次中断
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)	
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清除标志位
		usart1FreeTime++;	//串口1空闲时间
		tim3++;		//1ms 加1
		
		Led_Breath_Int(pBreathStatus->enable,pBreathStatus->color,pBreathStatus->waitTime);	//呼吸灯 控制颜色和间隔时间（ms）
	}
}

void Led_Breath_Int(uint8_t enable, uint8_t color, uint8_t BreathTime)	//呼吸灯 是否允许 控制颜色和间隔时间（ms）
{
	if(enable)
	{
		if(tim3 % BreathTime == 0)
		{
			Led_Breath(color,pBreathStatus->count);
			pBreathStatus->count++;
			if(pBreathStatus->count==200)
				pBreathStatus->count=0;
		}
	}
}

//void ledBreathStatus_Init()
//{
//	memcpy(pBreathStatus,0,sizeof(LBS)); 
//}
