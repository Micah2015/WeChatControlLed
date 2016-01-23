#include "stm32f10x.h"
#include "usart1.h"
#include "led30.h"
#include "tim3.h"
#include "global.h"

extern Led_Breath_Status *pBreathStatus;
extern uint16_t tim3;
extern uint16_t WriteSP;	//����дָ��
extern uint8_t usart1ReceiveFlag; //���ڽ��յ�����
extern uint16_t Syntime;	//ͬ��ʱ�� ��60s����ǰ����״̬����λ��

void test2(void);

uint8_t buf_R[30]={50,50,50,0,0,0,0,0,0,50,50,50,50,50,50,0,0,0,50,0,0,50,50,0,50,50,15,50};
uint8_t buf_G[30]={0,0,0,50,50,50,0,0,0,50,50,50,0,0,0,50,50,50,50,0,0,50,50,0,50,50,15,50};
uint8_t buf_B[30]={0,0,0,0,0,0,50,50,50,0,0,0,50,50,50,50,50,50,50,0,0,50,50,0,50,50,15,50};
	
void Periph_Init(void)	//���躯����ʼ��
{
	GPIO_Init_led30();
	TIM3_Config();
	USART1_Init();
	Wifi_Configure();
}

	
int main(void)
{
	uint8_t SendBack;	//����������
	
	Periph_Init();
	
	/******һ��ʼ����Ϊ��ɫ������******/
	SendBack = 3;
	MyUsartPrintf(&SendBack,1);
	delay_5ms_t(2);
	ReceiveBuffer[0]='3';
	usart1ReceiveFlag = 1;
	/******һ��ʼ����Ϊ��ɫ������******/
	
  while (1)
  {
		if(Syntime == 60000)	//����ͬ��ʱ��
		{
			Syntime = 0;
			MyUsartPrintf(&SendBack,1);	//����			
		}
		if(usart1ReceiveFlag == 1)	//���ڽ��յ����� ��16ms
		{
			WriteSP=0;
			usart1ReceiveFlag = 0; //����
			Syntime = 0;
			
			switch(ReceiveBuffer[0])
			{
				case '0':	//��ͣ
				{
					pBreathStatus->enable = 0;
					SendBack = '0';
				}break;
				case '9':	//����
				{
					pBreathStatus->enable = 1;
					SendBack = '9';
				}break;
				case '1':
				{
					pBreathStatus->count = 0;
					pBreathStatus->enable = 1;
					pBreathStatus->color = 1;
					SendBack = '1';
				}break;
				case '2':
				{
					pBreathStatus->count = 0;
					pBreathStatus->enable = 1;
					pBreathStatus->color = 2;
					SendBack = '2';
				}break;
				case '3':
				{
					pBreathStatus->count = 0;
					pBreathStatus->enable = 1;
					pBreathStatus->color = 3;
					SendBack = '3';
				}break;
				case '4':
				{
					pBreathStatus->count = 0;
					pBreathStatus->enable = 1;
					pBreathStatus->color = 4;
					SendBack = '4';
				}break;
				case '5':
				{
					pBreathStatus->count = 0;
					pBreathStatus->enable = 1;
					pBreathStatus->color = 5;
					SendBack = '5';
				}break;
				case '6':
				{
					pBreathStatus->count = 0;
					pBreathStatus->enable = 1;
					pBreathStatus->color = 6;
					SendBack = '6';
				}break;
				case '7':	//�ص�
				{
					delay_5ms_t(30);
					pBreathStatus->color = 0;
					pBreathStatus->count = 0;
					pBreathStatus->enable = 1;
					//delay_5ms_t(30);
					//shutDownAll();	//ȷ���ر����е�
					SendBack = '7';
				}break;
				
				default: SendBack = 0xff;	//error
			}
			
			MyUsartPrintf(&SendBack,1);	//����
		}
  }
}

void test(void)
{
//		GPIOB->BSRR = GPIO_Pin_1;
//		delay_1s(1);
//		GPIOB->BRR = GPIO_Pin_1;
//		delay_1s(1);
	
//		for(i=0;i<50;i++)
//			Led_Rotate(buf_R,buf_G,buf_B,5);
//		for(i=0;i<5;i++)
//			Led_Breath(indexWave2,indexWave,indexWave2);//������
//			Led_Breath(2);
	
//	pBreathStatus->waitTime = 15;
//	pBreathStatus->enable = 1;
//	for(i=1;i<=6;i++)
//	{
//		pBreathStatus->color = i;
//		delay_1s();delay_1s();delay_1s();
//	}
}

void test2()
{
	tim3 = 0;
	pBreathStatus->waitTime = 15;
	while (1)
  {
		switch(tim3/3000+1)
		{
			case 1:
			{
				pBreathStatus->enable = 1;
				pBreathStatus->color = 1;
			}break;
			case 2:
			{
				pBreathStatus->color = 2;
			}break;
			case 3:
			{
				pBreathStatus->color = 3;
			}break;
			case 4:
			{
				pBreathStatus->color = 4;
			}break;
			case 5:
			{
				pBreathStatus->color = 5;
			}break;
			case 6:
			{
				pBreathStatus->color = 6;
			}break;
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			{
				pBreathStatus->enable = 0;
				Led_Rotate(buf_R,buf_G,buf_B,10);
			}break;
			default: tim3=0;
		}
  }
}
