#ifndef __GLOBAL_H
#define	__GLOBAL_H

#include "stm32f10x_it.h"
#include "string.h"

#define BufferLength				1024
#define breathLedNumber			90			//�����Ƶ���

typedef struct
{
	uint8_t count;	//��ʾ�����Ʋ��ĵڼ���
	uint8_t color;			//��ʾ��������ɫ
	uint8_t waitTime;		//��ʾ��������������֮���ʱ����
	uint8_t enable;			//�Ƿ����������
	uint8_t breath_1ms;	//1ms ��1
	uint8_t stopFlag;		//��ͣΪ1
}Led_Breath_Status;	//�����ƽṹ��

typedef struct	
{
	uint8_t enable;			//�Ƿ�������ת��
	uint8_t changeTime;	//ת���ļ��ʱ��
	uint8_t rotate_1ms;
	uint8_t mode;				//ѡ����ת�Ƶ�ģʽ
	uint8_t stopFlag;		//��ͣΪ1
}Led_Rotate_Status;		//��ת�ƽṹ��

#endif
