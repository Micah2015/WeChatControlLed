#include "stm32f10x.h"
#include "usart1.h"
#include "led30.h"
#include "tim3.h"
#include "global.h"

extern Led_Breath_Status *pBreathStatus;
extern uint16_t tim3;
extern uint16_t WriteSP;	//串口写指针
extern uint8_t usart1ReceiveFlag; //串口接收到数据

void test2(void);

uint8_t buf_R[30]={50,50,50,0,0,0,0,0,0,50,50,50,50,50,50,0,0,0,50,0,0,50,50,0,50,50,15,50};
uint8_t buf_G[30]={0,0,0,50,50,50,0,0,0,50,50,50,0,0,0,50,50,50,50,0,0,50,50,0,50,50,15,50};
uint8_t buf_B[30]={0,0,0,0,0,0,50,50,50,0,0,0,50,50,50,50,50,50,50,0,0,50,50,0,50,50,15,50};
	
void Periph_Init(void)	//外设函数初始化
{
	GPIO_Init_led30();
	//TIM3_Config();
	//USART1_Init();
	//Wifi_Configure();
}

	
int main(void)
{
	Periph_Init();

//	Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(1);Led_Code(1);Led_Code(1);Led_Code(1);
//	Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);
//	Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);Led_Code(0);
		
//	GPIOB->BRR = GPIO_Pin_1;
//	delay_50us();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	GPIOB->BRR = GPIO_Pin_1;
//	delay_50us();
//	
//	Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();	
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();	
//	Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();Code_0();
//	Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();Code_1();

//	GPIOB->BRR = GPIO_Pin_1;
//	delay_5ms_t(1);
	
	Led30_Stop();
	Led_Write_All(0,0,0);
	delay_5ms_t(1);
	Led_Write_All(255,255,255);
	
  while (1)
  {
		//Led_Rotate(buf_R,buf_G,buf_B,7);
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
//			Led_Breath(indexWave2,indexWave,indexWave2);//呼吸灯
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
