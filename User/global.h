#ifndef __GLOBAL_H
#define	__GLOBAL_H

#include "stm32f10x_it.h"
#include "string.h"

#define BufferLength				1024

typedef struct
{
	uint8_t count;	//��ʾ�����Ʋ��ĵڼ���
	uint8_t color;			//��ʾ��������ɫ
	uint8_t waitTime;		//��ʾ��������������֮���ʱ����
	uint8_t enable;			//�Ƿ����������
}Led_Breath_Status;

#endif
