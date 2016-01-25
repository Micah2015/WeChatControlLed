#include "stm32f10x.h"
#include "usart1.h"
#include "led30.h"
#include "tim3.h"
#include "global.h"

extern Led_Breath_Status *pBreathStatus;	//呼吸灯结构体指针
extern Led_Rotate_Status* pLed_Rotate_Status;	//旋转灯结构体指针

extern uint16_t tim3;
extern uint16_t WriteSP;	//串口写指针
extern uint8_t usart1ReceiveFlag; //串口接收到数据
extern uint16_t Syntime;	//同步时间 到60s发当前亮灯状态给上位机

void test2(void);
	
void Periph_Init(void)	//外设函数初始化
{
	GPIO_Init_led30();
	TIM3_Config();
	USART1_Init();
	Wifi_Configure(1);
}
	
int main(void)
{
	uint8_t SendBack='3';	//发给服务器
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
	
	/******一开始连上为绿色呼吸灯******/
	SendBack = '3';
	MyUsartPrintf(&SendBack,1);
	delay_5ms_t(2);
	ReceiveBuffer[0]=SendBack;
	usart1ReceiveFlag = 1;
	ReceiveBuffer[10]=0;
	ReceiveBuffer[11]=0;
	/******一开始连上为绿色呼吸灯******/
	
  while (1)
  {
		if(WifiRestart == 1)	//Wifi模式掉电重启
		{
			WifiRestart = 0;
			Wifi_Configure(1);	
			usart1ReceiveFlag = 0; //进入这里说明Wifi连接断开了 接收到的Flag肯定不是来自服务器 清零
			delay_5ms_t(1);	//至少收到10 11，防止被串口出来的数据覆盖
			ReceiveBuffer[10]=0;	//清零 防止后面认为Wifi断电了
			ReceiveBuffer[11]=0;
		}
		
		if(Syntime >= 29999) //30s 同步一次
		{
			Syntime = 0;
			WriteSP = 1;
			MyUsartPrintf(&testConnect,1); //发送的数不能超出9个 否则影响后面第10个判断
			delay_5ms_t(20);
			WriteSP = 0;	//下次接收恢复到0，否则接收到的是第二个，下面的判断会错
		}
		
		delay_5ms_t(4);
		if(ReceiveBuffer[10] == 0 && ReceiveBuffer[11] == 0)	//后面有数是Wifi断电了
		{
			if(usart1ReceiveFlag == 1)	//串口接收到数据  
			{
				WriteSP=0;
				usart1ReceiveFlag = 0; //清零
				
				switch(ReceiveBuffer[0])
				{
					case '0':	//暂停 呼吸灯
					{
						if(pBreathStatus->enable == 1)	//呼吸灯
						{
							pBreathStatus->enable = 0;	//关闭呼吸灯
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
					case '9':	//继续 
					{
						if(pBreathStatus->stopFlag == 1)	//当前为呼吸灯暂停
						{
							pBreathStatus->stopFlag = 0;
							pBreathStatus->enable = 1;
							SendBack = '9';
						}
						if(pLed_Rotate_Status->stopFlag == 1)	//当前为旋转灯暂停
						{
							pLed_Rotate_Status->stopFlag = 0;
							pLed_Rotate_Status->enable = 1;
							SendBack = '9';
						}
					}break;
					case '1':	//白 呼吸灯
					{
						pLed_Rotate_Status->enable = 0;	//关闭旋转灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 1;
						SendBack = '1';
					}break;
					case '2':	//红 呼吸灯
					{
						pLed_Rotate_Status->enable = 0;	//关闭旋转灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 2;
						SendBack = '2';
					}break;
					case '3':	//绿 呼吸灯
					{
						pLed_Rotate_Status->enable = 0;	//关闭旋转灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 3;
						SendBack = '3';
					}break;
					case '4':	//蓝 呼吸灯
					{
						pLed_Rotate_Status->enable = 0;	//关闭旋转灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 4;
						SendBack = '4';
					}break;
					case '5':	//黃 呼吸灯
					{
						pLed_Rotate_Status->enable = 0;	//关闭旋转灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 5;
						SendBack = '5';
					}break;
					case '6':	//青 呼吸灯
					{
						pLed_Rotate_Status->enable = 0;	//关闭旋转灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						pBreathStatus->color = 6;
						SendBack = '6';
					}break;
					case '7':	//关灯
					{
						pLed_Rotate_Status->enable = 0;	//关闭旋转灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						
						delay_5ms_t(30);
						pBreathStatus->color = 0;
						pBreathStatus->count = 0;
						pBreathStatus->enable = 1;
						
						SendBack = '7';
					}break;
					case 'a':	//旋转灯
					{
						pBreathStatus->enable = 0;	//关闭呼吸灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pLed_Rotate_Status->enable = 1;
						pLed_Rotate_Status->changeTime = 50;
						pLed_Rotate_Status->mode = 1;
						SendBack = 'a';
					}break;
					case 'b':	//旋转灯
					{
						pBreathStatus->enable = 0;	//关闭呼吸灯
						pBreathStatus->stopFlag = 0;	//进入这里 取消暂停状态
						pLed_Rotate_Status->stopFlag = 0;
						pLed_Rotate_Status->enable = 1;
						pLed_Rotate_Status->changeTime = 50;
						pLed_Rotate_Status->mode = 2;
						SendBack = 'b';
					}break;
					
					default: SendBack = 0xff;	//error
				}
				MyUsartPrintf(&SendBack,1);	//发送
			}
		}
		else	//Wifi 断电重启了
		{
			WifiRestart = 1;
			ReceiveBuffer[10] = 0; //清零
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
