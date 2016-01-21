#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include "global.h"
#include <stdio.h>

extern uint8_t ReceiveBuffer[BufferLength];	//���ڻ���
extern uint16_t WriteSP;	//����дָ��
extern uint16_t tim3;

void USART1_Init(void);	//���ڳ�ʼ�� 115200
void MyUsartPrintf(uint8_t* buffer,int length);	//���ʹ�������
uint8_t Find_Start_OK(void);	//���AT�Ƿ��Ѿ�����
uint8_t SingleLink_OK(void);	//����Ƿ����óɵ����� AT+CIPMUX=0
uint8_t CIPMODE1_OK(void);	//����Ƿ����ó�͸��ģʽ
uint8_t CIPSTATUS_OK3(void);	//��ʾ����״̬stat 2:���IP 3.������ 4:�Ͽ����� 5.δ���ӵ�Wifi
void Wifi_Configure(void);	//���ó� ������͸��ģʽ TCP
uint8_t Test_CIPSEND_Mode(void);	//�����Ƿ��Ѿ�����͸��ģʽ

#endif /* __USART1_H */
