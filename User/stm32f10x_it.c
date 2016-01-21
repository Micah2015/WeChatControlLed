#include "stm32f10x_it.h"

uint16_t tim3=0;	//1ms ��1
uint16_t usart1FreeTime=0;	//����1����ʱ��
uint8_t ReceiveBuffer[BufferLength];	//���ڻ���
uint16_t WriteSP=0;	//����дָ��

uint8_t usart1ReceiveFlag = 0; //���ڽ��յ�����

Led_Breath_Status LBS={0,0,15,0};
Led_Breath_Status *pBreathStatus=&LBS;

void USART1_IRQHandler(void)	//�жϴ��ڽ��ܳ���
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //���ڽ��շǿ�
	{		
		usart1FreeTime = 0;	//���ڿ���ʱ�� ���ڽ��յ�������0
		ReceiveBuffer[WriteSP++] =  USART_ReceiveData(USART1); //����1���ֽ�
		usart1ReceiveFlag = 1;
	}	
} 

void TIM3_IRQHandler(void)	//��ʱ��3 ÿ1ms����һ���ж�
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)	
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //�����־λ
		usart1FreeTime++;	//����1����ʱ��
		tim3++;		//1ms ��1
		
		Led_Breath_Int(pBreathStatus->enable,pBreathStatus->color,pBreathStatus->waitTime);	//������ ������ɫ�ͼ��ʱ�䣨ms��
	}
}

void Led_Breath_Int(uint8_t enable, uint8_t color, uint8_t BreathTime)	//������ �Ƿ����� ������ɫ�ͼ��ʱ�䣨ms��
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
