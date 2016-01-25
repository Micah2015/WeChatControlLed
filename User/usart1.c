#include "usart1.h"
#include "led30.h"

const uint8_t testAT_Start[]="AT\x0d\x0a";
const	uint8_t RST[]="AT+RST\x0d\x0a";	//restart
const uint8_t singleLink[]="AT+CIPMUX=0\x0d\x0a";
const uint8_t sLinkTest[]="AT+CIPMUX?\x0d\x0a";
const uint8_t CIPMODE1[]="AT+CIPMODE=1\x0d\x0a";
const uint8_t CIPMODE1_Test[]="AT+CIPMODE?\x0d\x0a";
const uint8_t CIPSTATUS[]="AT+CIPSTATUS\x0d\x0a";
const uint8_t CWMODE1[]="AT+CWMODE_DEF=1\x0d\x0a";	//���ó��ն�
const uint8_t CWMODE1_Test[]="AT+CWMODE_DEF?\x0d\x0a";
const	uint8_t HUSTDTV[]="AT+CWJAP=\"HUSTDTV\",\"13807182202\"\x0d\x0a";
//const uint8_t linkServer[]="AT+CIPSTART=\"UDP\",\"192.168.2.242\",8080\x0d\x0a";
//const uint8_t linkServer[]="AT+CIPSTART=\"TCP\",\"192.168.2.5\",8080\x0d\x0a";
//const uint8_t linkServer[]="AT+CIPSTART=\"TCP\",\"192.168.1.117\",8080\x0d\x0a";
const uint8_t linkServer[]="AT+CIPSTART=\"TCP\",\"121.42.182.224\",6969\x0d\x0a";
const uint8_t CIPSEND[]="AT+CIPSEND\x0d\x0a";

uint16_t testTime[15];

void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//Tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PB0 ���ڸ�λWifiģ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	 //ʹ�ܽ����ж�
	
	USART_Cmd(USART1, ENABLE);
	
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x08000);		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //4��ռ���ȼ� 4����Ӧ���ȼ�		
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 //usart1 �ж�ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //��Ӧ���ȼ����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

//�Զ��崮�ڷ��ͳ���
void MyUsartPrintf(uint8_t* buffer,int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		USART_SendData(USART1, buffer[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);  //δ������һֱ�ȴ�
	}	
}

uint8_t Find_Start_OK(void)	//���AT�Ƿ��Ѿ�����
{
	if(ReceiveBuffer[WriteSP-4]=='O' && ReceiveBuffer[WriteSP-3]=='K')
		return 1;
	else
		return 0;
}

uint8_t LinkServerOK(void)	//���AT�Ƿ��Ѿ�����
{
	if(ReceiveBuffer[50]=='O' && ReceiveBuffer[51]=='K')
		return 1;
	else
		return 0;
}

uint8_t SingleLink_OK(void)	//����Ƿ����óɵ����� AT+CIPMUX=0
{
	if(ReceiveBuffer[WriteSP-4]=='O' && ReceiveBuffer[WriteSP-3]=='K' && ReceiveBuffer[WriteSP-9]=='0')	//OK 0
		return 1;
	else
		return 0;
}

uint8_t CIPMODE1_OK(void)	//����Ƿ����ó�͸��ģʽ
{
	if(ReceiveBuffer[WriteSP-4]=='O' && ReceiveBuffer[WriteSP-3]=='K' && ReceiveBuffer[WriteSP-9]=='1')	//OK 1
		return 1;
	else
		return 0;
}

uint8_t CIPSTATUS_OK3(void)	//��ʾ����״̬stat 2:���IP 3.������ 4:�Ͽ����� 5.δ���ӵ�Wifi
{
	if(ReceiveBuffer[WriteSP-4]=='O' && ReceiveBuffer[WriteSP-3]=='K')
		return ReceiveBuffer[WriteSP-9];
	else	//ָ��ʧ��
		return 0;
}

uint8_t CIPSTATUS_OK3_Find(void)	//����TCP Sever�� stat��λ�û��
{
	if(ReceiveBuffer[WriteSP-4]=='O' && ReceiveBuffer[WriteSP-3]=='K')
		return ReceiveBuffer[22];	//����stat��ֵ
	else	//ָ��ʧ��
		return 0;
}

uint8_t CIPSEND_OK(void)
{
	if(ReceiveBuffer[WriteSP-7]=='O' && ReceiveBuffer[WriteSP-6]=='K' && ReceiveBuffer[WriteSP-1]==0x3e)
		return 1;
	else
		return 0;
}

uint8_t Test_CIPSEND_Mode(void)	//�����Ƿ��Ѿ�����͸��ģʽ
{
	uint8_t test[]="+++\x0d\x0a";	//
	uint8_t i;
	uint8_t SendBuffer[50];
	
	testTime[0]=tim3;
	
	delay_5ms_t(2);	//�ȴ������жϿ���
	GPIOB->BRR = GPIO_Pin_0;	//��λWifiģ��
	delay_5ms_t(1);
	GPIOB->BSRR = GPIO_Pin_0;
	delay_1s(3);
	
	testTime[1]=tim3;
	
	WriteSP = 0;
	i=0;
	memcpy(SendBuffer,testAT_Start,sizeof(testAT_Start));
	do
	{
		if(i++==5)	//��������5�� ֹͣ2s
		{
			i=0;
			delay_1s(1);
		}
		MyUsartPrintf(SendBuffer,sizeof(testAT_Start));
		delay_5ms_t(4);
	}while(!Find_Start_OK());	//ATδ����һֱѭ��
	
	testTime[2]=tim3;
	
	//delay_1s(3);
	//��ü���Ӳ����λ
	WriteSP = 0;
	ReceiveBuffer[2]=0;
	MyUsartPrintf(test,sizeof(test));
	delay_5ms_t(4);
	//if(ReceiveBuffer[0]==test[0] && ReceiveBuffer[1]== test[0] && ReceiveBuffer[2] == test[0])	//δ����͸��ģʽ
	if(ReceiveBuffer[2])	//�лظ� ��˵��δ����͸��ģʽ
		return 1;
	else
		return 0;
}

void Wifi_Configure(uint8_t enRST)	//���ó� ������͸��ģʽ TCP
{
	uint8_t SendBuffer[100];
	uint8_t cipstatus=0;
	uint8_t i=0;	//��������5�� ֹͣ2s
	uint8_t WifiFirst=0; //��һ�ν�wifi case �ȴ����˳� ��Ϊģ����ܻ�û�Զ�����
	
	testTime[0]=tim3;
	delay_5ms_t(2);	//�ȴ������жϿ���
	GPIOB->BSRR = GPIO_Pin_0;	//RST�ߵ�ƽ 
	if(enRST)	//�Ƿ���и�λ
	{
		GPIOB->BRR = GPIO_Pin_0;	//��λWifiģ��
		delay_5ms_t(1);
		GPIOB->BSRR = GPIO_Pin_0;
		delay_1s(5);
	}
	testTime[1]=tim3;
	WriteSP = 0;
	i=0;
	memcpy(SendBuffer,testAT_Start,sizeof(testAT_Start));
	do
	{
		if(i++==5)	//��������5�� ֹͣ2s
		{
			i=0;
			delay_1s(1);
		}
		MyUsartPrintf(SendBuffer,sizeof(testAT_Start));
		delay_5ms_t(4);
	}while(!Find_Start_OK());	//ATδ����һֱѭ��
	
	testTime[3]=tim3;
	
	WriteSP = 0;
	i=0;
	do
	{
		if(i++==5)	//��������5�� ֹͣ2s
		{
			i=0;
			delay_5ms_t(100);
		}
		memcpy(SendBuffer,singleLink,sizeof(singleLink));
		MyUsartPrintf(SendBuffer,sizeof(singleLink));
		delay_5ms_t(4);
		memcpy(SendBuffer,sLinkTest,sizeof(sLinkTest));
		MyUsartPrintf(SendBuffer,sizeof(sLinkTest));
		delay_5ms_t(4);
	}while(CIPSTATUS_OK3()!='0');	//����Ƿ����óɵ����� AT+CIPMUX=0
	
	testTime[4]=tim3;
	
	WriteSP = 0;
	i=0;
	do
	{
		if(i++==5)	//��������5�� ֹͣ2s
		{
			i=0;
			delay_1s(1);
		}
		memcpy(SendBuffer,CWMODE1,sizeof(CWMODE1));
		MyUsartPrintf(SendBuffer,sizeof(CWMODE1));
		delay_5ms_t(4);
		memcpy(SendBuffer,CWMODE1_Test,sizeof(CWMODE1_Test));
		MyUsartPrintf(SendBuffer,sizeof(CWMODE1_Test));
		delay_5ms_t(4);
	}while(CIPSTATUS_OK3()!='1');	//���ó��ն�
	
	testTime[5]=tim3;
	
	WriteSP = 0;
	i=0;
	do
	{
		if(i++==5)	//��������5�� ֹͣ2s
		{
			i=0;
			delay_1s(1);
		}
		memcpy(SendBuffer,CIPMODE1,sizeof(CIPMODE1));
		MyUsartPrintf(SendBuffer,sizeof(CIPMODE1));
		delay_5ms_t(4);
		memcpy(SendBuffer,CIPMODE1_Test,sizeof(CIPMODE1_Test));
		MyUsartPrintf(SendBuffer,sizeof(CIPMODE1_Test));
		delay_5ms_t(4);
	}while(!CIPMODE1_OK());	//����Ƿ����ó�͸��ģʽ
	
	testTime[6]=tim3;
	
	WriteSP = 0; 
	i=0;	
	do
	{
		if(i++==8)	//��������8�� ֹͣ1s
		{
			i=0;
			delay_1s(1);
		}
		WriteSP = 0;
		memcpy(SendBuffer,CIPSTATUS,sizeof(CIPSTATUS));
		MyUsartPrintf(SendBuffer,sizeof(CIPSTATUS));
		delay_5ms_t(10);
		cipstatus=CIPSTATUS_OK3_Find();
		switch(cipstatus)		//HUSTDTV
		{
			case '5':		//δ���ӵ�Wifi
			{	
				testTime[10]++;
				if(WifiFirst == 0)
				{
					WifiFirst = 1;
					delay_1s(1);
				}
				else
				{
					memcpy(SendBuffer,HUSTDTV,sizeof(HUSTDTV));
					MyUsartPrintf(SendBuffer,sizeof(HUSTDTV));
					delay_1s(3);
				}
			}break;
			
			case '2':	//�ѻ��IP	׼������TCP Sever 
			case '4':	//�Ͽ�����
			{
				testTime[11]++;
				
				WriteSP = 0;
				memcpy(SendBuffer,linkServer,sizeof(linkServer));
				MyUsartPrintf(SendBuffer,sizeof(linkServer));
				delay_5ms_t(50);
				
				if(LinkServerOK()==1)	//���ӳɹ��˳�
					cipstatus = '3';
			}break;
			
			case '3':	//������ 
			{
				
			}break;
			
			default: testTime[12]++;
		}
		testTime[9]++;
	}while(cipstatus!='3');	
	
	testTime[7]=tim3;
	
	do
	{
		memcpy(SendBuffer,CIPSEND,sizeof(CIPSEND));
		MyUsartPrintf(SendBuffer,sizeof(CIPSEND));
		delay_5ms_t(4);
	}while(!CIPSEND_OK());
	WriteSP = 0;
	
	testTime[8]=tim3;
}
