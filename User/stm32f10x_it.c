#include "stm32f10x_it.h"

uint8_t buf_R1[30]={50,50,50,0,0,0,0,0,0,50,50,50,50,50,50,0,0,0,50,0,0,50,50,0,50,50,15,50};	//mode 1
uint8_t buf_G1[30]={0,0,0,50,50,50,0,0,0,50,50,50,0,0,0,50,50,50,50,0,0,50,50,0,50,50,15,50};
uint8_t buf_B1[30]={0,0,0,0,0,0,50,50,50,0,0,0,50,50,50,50,50,50,50,0,0,50,50,0,50,50,15,50};
	
uint8_t buf_R2[30]={10,20,30,40,50,50,40,30,20,10,0,50,40,30,20,10,0,50,30,20,10,30,40,50,30,40,50,20};	//mode 2	
uint8_t buf_G2[30]={0,10,20,30,40,50,50,40,20,10,10,10,20,30,40,50,40,30,20,50,20,10,50,30,20,10,30,0};
uint8_t buf_B2[30]={0,0,10,20,30,40,50,50,40,30,20,10,30,40,50,20,10,50,40,30,20,10,30,40,20,50,10,30};
uint8_t buf_Null[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint16_t tim3=0;	//1ms 加1
uint16_t usart1FreeTime=0;	//串口1空闲时间
uint16_t Syntime=0;	//同步时间 到60s发当前亮灯状态给上位机 如果中间有发数据则清零
uint8_t ReceiveBuffer[BufferLength];	//串口缓存
uint16_t WriteSP=0;	//串口写指针

uint8_t usart1ReceiveFlag = 0; //串口接收到数据

Led_Breath_Status LBS={0,0,20,0,0,0}; //默认呼吸灯间隔20ms
Led_Breath_Status* pBreathStatus=&LBS;	//呼吸灯结构体指针

Led_Rotate_Status LRS={0,50,0,1,0};	//默认旋转灯间隔50ms mode:1
Led_Rotate_Status* pLed_Rotate_Status=&LRS;	//旋转灯结构体指针

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
		pBreathStatus->breath_1ms++;	//1ms 加1 呼吸灯
		pLed_Rotate_Status->rotate_1ms++;	//1ms 加1 旋转灯
		Syntime++;	//同步时间 到60s发当前亮灯状态给上位机
		
		Led_Breath_Int(pBreathStatus->enable,pBreathStatus->color,pBreathStatus->waitTime);	//呼吸灯 控制颜色和间隔时间（ms）
		Led_Rotate_Int(pLed_Rotate_Status->enable,pLed_Rotate_Status->changeTime,pLed_Rotate_Status->mode);
	}
}

void Led_Breath_Int(uint8_t enable, uint8_t color, uint8_t BreathTime)	//呼吸灯 是否允许 控制颜色和间隔时间（ms）
{
	if(enable)	//允许呼吸灯
	{
		if(pBreathStatus->breath_1ms % BreathTime == 0)
		{
			Led_Breath(color,pBreathStatus->count);
			pBreathStatus->count++;
			if(pBreathStatus->count==breathLedNumber*2)
				pBreathStatus->count=0;
		}
	}
}

void Led_Rotate_Int(uint8_t enable, uint8_t changeTime, uint8_t mode)	//changeTime:转动的间隔时间 mode:选择旋转灯的模式
{
	if(enable)	//允许旋转灯
	{
		if(pLed_Rotate_Status->rotate_1ms % changeTime == 0)	//到了指定时间旋转一次
		{
			switch(mode)
			{
				case 1:
				{
					Led_Rotate(buf_R1,buf_G1,buf_B1);
				}break;
				case 2:
				{
					Led_Rotate(buf_R2,buf_G2,buf_B2);
				}break;
				
				default: ;
			}
		}
	}
}

