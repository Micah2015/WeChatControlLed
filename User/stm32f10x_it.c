#include "stm32f10x_it.h"

uint8_t buf_R1[30]={50,50,50,0,0,0,0,0,0,50,50,50,50,50,50,0,0,0,50,0,0,50,50,0,50,50,15,50};	//mode 1
uint8_t buf_G1[30]={0,0,0,50,50,50,0,0,0,50,50,50,0,0,0,50,50,50,50,0,0,50,50,0,50,50,15,50};
uint8_t buf_B1[30]={0,0,0,0,0,0,50,50,50,0,0,0,50,50,50,50,50,50,50,0,0,50,50,0,50,50,15,50};
	
uint8_t buf_R2[30]={10,20,30,40,50,50,40,30,20,10,0,50,40,30,20,10,0,50,30,20,10,30,40,50,30,40,50,20};	//mode 2	
uint8_t buf_G2[30]={0,10,20,30,40,50,50,40,20,10,10,10,20,30,40,50,40,30,20,50,20,10,50,30,20,10,30,0};
uint8_t buf_B2[30]={0,0,10,20,30,40,50,50,40,30,20,10,30,40,50,20,10,50,40,30,20,10,30,40,20,50,10,30};
uint8_t buf_Null[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint16_t tim3=0;	//1ms ��1
uint16_t usart1FreeTime=0;	//����1����ʱ��
uint16_t Syntime=0;	//ͬ��ʱ�� ��60s����ǰ����״̬����λ�� ����м��з�����������
uint8_t ReceiveBuffer[BufferLength];	//���ڻ���
uint16_t WriteSP=0;	//����дָ��

uint8_t usart1ReceiveFlag = 0; //���ڽ��յ�����

Led_Breath_Status LBS={0,0,20,0,0,0}; //Ĭ�Ϻ����Ƽ��20ms
Led_Breath_Status* pBreathStatus=&LBS;	//�����ƽṹ��ָ��

Led_Rotate_Status LRS={0,50,0,1,0};	//Ĭ����ת�Ƽ��50ms mode:1
Led_Rotate_Status* pLed_Rotate_Status=&LRS;	//��ת�ƽṹ��ָ��

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
		pBreathStatus->breath_1ms++;	//1ms ��1 ������
		pLed_Rotate_Status->rotate_1ms++;	//1ms ��1 ��ת��
		Syntime++;	//ͬ��ʱ�� ��60s����ǰ����״̬����λ��
		
		Led_Breath_Int(pBreathStatus->enable,pBreathStatus->color,pBreathStatus->waitTime);	//������ ������ɫ�ͼ��ʱ�䣨ms��
		Led_Rotate_Int(pLed_Rotate_Status->enable,pLed_Rotate_Status->changeTime,pLed_Rotate_Status->mode);
	}
}

void Led_Breath_Int(uint8_t enable, uint8_t color, uint8_t BreathTime)	//������ �Ƿ����� ������ɫ�ͼ��ʱ�䣨ms��
{
	if(enable)	//���������
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

void Led_Rotate_Int(uint8_t enable, uint8_t changeTime, uint8_t mode)	//changeTime:ת���ļ��ʱ�� mode:ѡ����ת�Ƶ�ģʽ
{
	if(enable)	//������ת��
	{
		if(pLed_Rotate_Status->rotate_1ms % changeTime == 0)	//����ָ��ʱ����תһ��
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

