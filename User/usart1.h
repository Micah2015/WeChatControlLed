#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include "global.h"
#include <stdio.h>

extern uint8_t ReceiveBuffer[BufferLength];	//串口缓存
extern uint16_t WriteSP;	//串口写指针
extern uint16_t tim3;

void USART1_Init(void);	//串口初始化 115200
void MyUsartPrintf(uint8_t* buffer,int length);	//发送串口数据
uint8_t Find_Start_OK(void);	//检测AT是否已经启动
uint8_t SingleLink_OK(void);	//检测是否设置成单连接 AT+CIPMUX=0
uint8_t CIPMODE1_OK(void);	//检测是否设置成透传模式
uint8_t CIPSTATUS_OK3(void);	//显示网络状态stat 2:获得IP 3.已连接 4:断开连接 5.未连接到Wifi
void Wifi_Configure(void);	//配置成 单连接透传模式 TCP
uint8_t Test_CIPSEND_Mode(void);	//测试是否已经进入透传模式

#endif /* __USART1_H */
