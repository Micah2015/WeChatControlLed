#include "stm32f10x.h"
#include "usart1.h"
#include "led30.h"
#include "tim3.h"
#include "global.h"

extern Led_Breath_Status *pBreathStatus;	//�����ƽṹ��ָ��
extern Led_Rotate_Status* pLed_Rotate_Status;	//��ת�ƽṹ��ָ��

extern uint16_t tim3;
extern uint16_t WriteSP;	//����дָ��
extern uint8_t usart1ReceiveFlag; //���ڽ��յ�����
extern uint16_t Syntime;	//ͬ��ʱ�� ��60s����ǰ����״̬����λ��

void test2(void);
	
void Periph_Init(void)	//���躯����ʼ��
{
	GPIO_Init_led30();
	TIM3_Config();
	USART1_Init();
	Wifi_Configure(1);
}
	
int main(void)
{
	uint8_t SendBack='3';	//����������
	uint8_t testConnect='S';
//	uint8_t TrueWifiSerialFlag=0;
//	uint8_t i;
	uint8_t WifiRestart = 0;
	
	Periph_Init();
	
//	for(i=0;i<1024;i++)
//		ReceiveBuffer[i] = 0;
//	WriteSP = 0;
//	MyUsartPrintf(&SendBack,1);
//	delay_5ms_t(100);
//	while(1);
	
	/******һ��ʼ����Ϊ��ɫ������******/
	SendBack = '3';
	MyUsartPrintf(&SendBack,1);
	delay_5ms_t(2);
	ReceiveBuffer[0]=SendBack;
	usart1ReceiveFlag = 1;
	ReceiveBuffer[10]=0;
	ReceiveBuffer[11]=0;
	/******һ��ʼ����Ϊ��ɫ������******/
	
  while (1)
  {
		if(WifiRestart == 1)	//Wifiģʽ��������
		{
			WifiRestart = 0;
			Wifi_Configure(1);	
			usart1ReceiveFlag = 0; //��������˵��Wifi���ӶϿ��� ���յ���Flag�϶��������Է����� ����
			delay_5ms_t(1);	//�����յ�10 11����ֹ�����ڳ��������ݸ���
			ReceiveBuffer[10]=0;	//���� ��ֹ������ΪWifi�ϵ���
			ReceiveBuffer[11]=0;
		}
		
		if(Syntime >= 29999) //30s ͬ��һ��
		{
			Syntime = 0;
			WriteSP = 1;
			MyUsartPrintf(&testConnect,1); //���͵������ܳ���9�� ����Ӱ������10���ж�
			delay_5ms_t(20);
			WriteSP = 0;	//�´ν��ջָ���0��������յ����ǵڶ�����������жϻ��
		}
		
		delay_5ms_t(4);
		if(ReceiveBuffer[10] == 0 && ReceiveBuffer[11] == 0)	//����������Wifi�ϵ���
		{
			if(usart1ReceiveFlag == 1)	//���ڽ��յ�����  
			{
				WriteSP=0;
				usart1ReceiveFlag = 0; //����
				
				switch(ReceiveBuffer[0])
				{
					case '0':	//��ͣ ������
					{
						if(pBreathStatus->enable == 1)	//������
						{
							pBreathStatus->enable = 0;	//�رպ�����
							SendBack = '0';
							pBreathStatus->stopFlag = 1;
						}
						if(pLed_Rotate_Status->enable == 1)
						{
							pLed_Rotate_Status->enable = 0;
							SendBack = '0';
							pLed_Rotate_Status->stopFlag = 1;
						}
					}break;
					case '9':	//���� 
					{
						if(pBreathStatus->stopFlag == 1)	//��ǰΪ��������ͣ
						{
							pBreathStatus->stopFlag = 0;
							pBreathStatus->enable = 1;
							SendBack = '9';
						}
						if(pLed_Rotate_Status->stopFlag == 1)	//��ǰΪ��ת����ͣ
						{
							pLed_Rotate_Status->stopFlag = 0;
							pLed_Rotate_Status->enable = 1;
							SendBack = '9';
						}
					}break;
					case '1':	//�� ������
					{
						pLed_Rotate_Status->enable = 0;	//�ر���ת��
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 1;
						SendBack = '1';
					}break;
					case '2':	//�� ������
					{
						pLed_Rotate_Status->enable = 0;	//�ر���ת��
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 2;
						SendBack = '2';
					}break;
					case '3':	//�� ������
					{
						pLed_Rotate_Status->enable = 0;	//�ر���ת��
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 3;
						SendBack = '3';
					}break;
					case '4':	//�� ������
					{
						pLed_Rotate_Status->enable = 0;	//�ر���ת��
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 4;
						SendBack = '4';
					}break;
					case '5':	//�S ������
					{
						pLed_Rotate_Status->enable = 0;	//�ر���ת��
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 5;
						SendBack = '5';
					}break;
					case '6':	//�� ������
					{
						pLed_Rotate_Status->enable = 0;	//�ر���ת��
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 6;
						SendBack = '6';
					}break;
					case '7':	//�ص�
					{
						pLed_Rotate_Status->enable = 0;	//�ر���ת��
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						
						delay_5ms_t(30);
						pBreathStatus->color = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						
						SendBack = '7';
					}break;
					case 'a':	//��ת��
					{
						pBreathStatus->enable = 0;	//�رպ�����
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pLed_Rotate_Status->enable = 1;
						pLed_Rotate_Status->changeTime = 50;
						pLed_Rotate_Status->mode = 1;
						SendBack = 'a';
					}break;
					case 'b':	//��ת��
					{
						pBreathStatus->enable = 0;	//�رպ�����
						pBreathStatus->stopFlag = 0;	//�������� ȡ����ͣ״̬
						pLed_Rotate_Status->stopFlag = 0;
						pLed_Rotate_Status->enable = 1;
						pLed_Rotate_Status->changeTime = 50;
						pLed_Rotate_Status->mode = 2;
						SendBack = 'b';
					}break;
					
					default: SendBack = 0xff;	//error
				}
				MyUsartPrintf(&SendBack,1);	//����
			}
		}
		else	//Wifi �ϵ�������
		{
			WifiRestart = 1;
			ReceiveBuffer[10] = 0; //����
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

//void test2()
//{
//	tim3 = 0;
//	pBreathStatus->waitTime = 15;
//	while (1)
//  {
//		switch(tim3/3000+1)
//		{
//			case 1:
//			{
//				pBreathStatus->enable = 1;
//				pBreathStatus->color = 1;
//			}break;
//			case 2:
//			{
//				pBreathStatus->color = 2;
//			}break;
//			case 3:
//			{
//				pBreathStatus->color = 3;
//			}break;
//			case 4:
//			{
//				pBreathStatus->color = 4;
//			}break;
//			case 5:
//			{
//				pBreathStatus->color = 5;
//			}break;
//			case 6:
//			{
//				pBreathStatus->color = 6;
//			}break;
//			case 7:
//			case 8:
//			case 9:
//			case 10:
//			case 11:
//			case 12:
//			{
//				pBreathStatus->enable = 0;
//				Led_Rotate(buf_R,buf_G,buf_B,10);
//			}break;
//			default: tim3=0;
//		}
//  }
//}
