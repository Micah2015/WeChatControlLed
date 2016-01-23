#include "led30.h"

//uint8_t BreathWave100[200] = {		//100点呼吸灯查询表
//0  , 0  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1 ,  1  , 1 ,  2 ,  2 ,  2 ,  2  , 2,
//2  , 2  , 3  , 3  , 3  , 3  , 3  , 4  , 4  , 4  , 4 ,  5  , 5 ,  5 ,  6 ,  6 ,  6  , 7,
//7  , 7  , 8  , 8  , 9  , 9  ,10  ,11  ,11  ,12  ,13 , 13  ,14 , 15 , 16 , 17 , 18  ,19,
//20 , 21 , 23 , 24 , 25 , 27 , 28 , 30 , 32 , 34 , 36,  38 , 40,  42,  45,  47,  50 , 53,
//56 , 59 , 63 , 66 , 70 , 74 , 78 , 83 , 88 , 93 , 98, 104 ,110, 116, 123, 130, 138 ,146,
//154, 163, 172, 182, 193, 204, 216, 228, 242, 255};

uint8_t BreathWave100[breathLedNumber*2] = {		//95点呼吸灯查询表
0  , 0  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1 ,  1  , 1 ,  2 ,  2 ,  2 ,  2  , 2,
2  , 2  , 3  , 3  , 3  , 3  , 3  , 4  , 4  , 4  , 4 ,  5  , 5 ,  5 ,  6 ,  6 ,  6  , 7,
7  , 7  , 8  , 8  , 9  , 9  ,10  ,11  ,11  ,12  ,13 , 13  ,14 , 15 , 16 , 17 , 18  ,19,
20 , 21 , 23 , 24 , 25 , 27 , 28 , 30 , 32 , 34 , 36,  38 , 40,  42,  45,  47,  50 , 53,
56 , 59 , 63 , 66 , 70 , 74 , 78 , 83 , 88 , 93 , 98, 104 ,110, 116, 123, 130, 138 ,146,
};

void GPIO_Init_led30(void)	//led30的GPIO使能
{		
	uint8_t i;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	shutDownAll();	//确保关闭所有灯
	for(i=breathLedNumber;i<breathLedNumber*2;i++)
	{
		BreathWave100[i]=BreathWave100[breathLedNumber*2-1-i];	//补全后面的点 倒序
	}
}

void Code_0(void)
{
	uint8_t i;
	GPIOB->BSRR = GPIO_Pin_1;
	for(i=0;i<1;i++)
		__nop();
	__nop();
	GPIOB->BRR = GPIO_Pin_1;
	for(i=3;i>0;i--)
	{
		__nop();__nop();
	}
	__nop();
}

void Code_1(void)
{
	uint8_t i;
	GPIOB->BSRR = GPIO_Pin_1;
	for(i=3;i>0;i--)
	{
		__nop();__nop();__nop();__nop();__nop();__nop();
	}
	GPIOB->BRR = GPIO_Pin_1;
	__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();
}

void Led_Code(uint8_t v)
{
	if(v)
		Code_1();
	else
		Code_0();
}

void Led_Write_Single(uint8_t red, uint8_t green, uint8_t blue)	//通过RGB控制一个led三色灯
{
	Led_Code(green&0x80);Led_Code(green&0x40);Led_Code(green&0x20);Led_Code(green&0x10);
	Led_Code(green&0x08);Led_Code(green&0x04);Led_Code(green&0x02);Led_Code(green&0x01);
	
	Led_Code(red&0x80);Led_Code(red&0x40);Led_Code(red&0x20);Led_Code(red&0x10);
	Led_Code(red&0x08);Led_Code(red&0x04);Led_Code(red&0x02);Led_Code(red&0x01);
	
	Led_Code(blue&0x80);Led_Code(blue&0x40);Led_Code(blue&0x20);Led_Code(blue&0x10);
	Led_Code(blue&0x08);Led_Code(blue&0x04);Led_Code(blue&0x02);Led_Code(blue&0x01);
}

void delay_50us(void)	//延时50us
{
	uint16_t i;
	for(i=600;i>0;i--);  
}

void delay_5ms_t(uint8_t t)	//约5ms
{
	uint8_t i,j,k;
	for(k=0;k<t;k++)
		for(i=230;i>0;i--)
			for(j=230;j>0;j--);
}

void delay_1s(uint8_t t)	//不准
{
	uint8_t i,j,k,m;
	for(m=0;m<t;m++)
		for(i=220;i>0;i--)
			for(j=220;j>0;j--)
				for(k=200;k>0;k--);
}	

void Led30_Stop(void) //停止向后传输数据
{
	GPIOB->BRR = GPIO_Pin_1;
	delay_50us();
	delay_50us();
}

void ChangeOut(uint8_t* buf)	//将外面的一圈 每次移动一位
{
	uint8_t i,temp;
	temp = buf[17];
	for(i=17;i>0;i--)
	{
		buf[i] = buf[i-1];
	}
	buf[0] = temp;
}

void ChangeIn(uint8_t* buf)	//将里面的一圈 每次移动一位
{
	uint8_t i,temp;
	temp = buf[0];
	for(i=0;i<12;i++)
	{
		buf[i] = buf[i+1];
	}
	buf[12] = temp;
}

void Buf_Rotate_InOut(uint8_t* buf)	//按照内圈、外圈移动一位
{
	uint8_t i,temp;
	//外圈
	temp = buf[17];
	for(i=17;i>0;i--)
	{
		buf[i] = buf[i-1];
	}
	buf[0] = temp;
	//内圈
	temp = buf[12];
	for(i=18;i<30;i++)
	{
		buf[i] = buf[i+1];
	}
	buf[30] = temp;
}

void Led_Rotate(uint8_t* buf_R,uint8_t* buf_G,uint8_t* buf_B,uint8_t T_5ms)	//外顺时针转，内逆时针转 移动一次延时
{
	uint8_t i;
	for(i=0;i<18;i++)
	{
		Led_Write_Single(buf_R[i],buf_G[i],buf_B[i]);
	}
	for(i=18;i<30;i++)
	{
		Led_Write_Single(buf_R[i],buf_G[i],buf_B[i]);
	}
	Led30_Stop();
	delay_5ms_t(T_5ms);
	Buf_Rotate_InOut(buf_R);
	Buf_Rotate_InOut(buf_G);
	Buf_Rotate_InOut(buf_B);
}

void Led_Write_All(uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t i;
	for(i=0;i<30;i++)
	{
		Led_Write_Single(red,green,blue);
	}
	Led30_Stop();
}

void shutDownAll(void)	//确保关闭所有灯
{
	Led30_Stop();
	delay_5ms_t(1);
	Led_Write_All(0,0,0);
	delay_5ms_t(30);
	Led_Write_All(0,0,0);
	delay_5ms_t(50);
}

//void Led_Breath(uint8_t* buf_R,uint8_t* buf_G,uint8_t* buf_B)	//呼吸灯
//{
//	uint8_t i,j;
//	for(i=0;i<200;i++)
//	{
//		if(i<100)
//			j=i;
//		else
//			j=199-i;
//		Led_Write_All(buf_R[j],buf_G[j],buf_B[j]);
//		delay_5ms_t(3);
//	}
//}

//void Led_Breath(uint8_t num)	//呼吸灯
//{
//	uint8_t i;
//	
//	for(i=0;i<200;i++)
//	{
//		switch(num)
//		{
//			case 0:
//			{
//				Led_Write_All(0,0,0);
//			}break;
//				
//			case 1:
//			{
//				Led_Write_All(BreathWave100[i],0,0);
//			}break;
//			
//			case 2:
//			{
//				Led_Write_All(0,BreathWave100[i],0);
//			}break;
//		}
//		delay_5ms_t(3);
//	}
//}

void Led_Breath(uint8_t color, uint8_t BreathWaveCount)	//呼吸灯
{
	switch(color)
	{
		case 0:
		{
			Led_Write_All(0,0,0);
		}break;
			
		case 1:	//白灯
		{
			Led_Write_All(BreathWave100[BreathWaveCount],BreathWave100[BreathWaveCount],BreathWave100[BreathWaveCount]);
		}break;
		
		case 2:	//红灯
		{
			Led_Write_All(BreathWave100[BreathWaveCount],0,0);
		}break;
		
		case 3:	//绿灯
		{
			Led_Write_All(0,BreathWave100[BreathWaveCount],0);
		}break;
		
		case 4:	//蓝灯
		{
			Led_Write_All(0,0,BreathWave100[BreathWaveCount]);
		}break;
		
		case 5:	//黃灯
		{
			Led_Write_All(BreathWave100[BreathWaveCount],BreathWave100[BreathWaveCount],0);
		}break;
		
		case 6:	//青灯
		{
			Led_Write_All(0,BreathWave100[BreathWaveCount],BreathWave100[BreathWaveCount]);
		}break;
		
		default: Led_Write_All(0,0,0);	//默认为关
	}
}

