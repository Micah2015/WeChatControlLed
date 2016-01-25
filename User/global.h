#ifndef __GLOBAL_H
#define	__GLOBAL_H

#include "stm32f10x_it.h"
#include "string.h"

#define BufferLength				1024
#define breathLedNumber			90			//呼吸灯点数

typedef struct
{
	uint8_t count;	//表示呼吸灯查表的第几个
	uint8_t color;			//表示呼吸灯颜色
	uint8_t waitTime;		//表示呼吸灯两个亮度之间的时间间隔
	uint8_t enable;			//是否允许呼吸灯
	uint8_t breath_1ms;	//1ms 加1
	uint8_t stopFlag;		//暂停为1
}Led_Breath_Status;	//呼吸灯结构体

typedef struct	
{
	uint8_t enable;			//是否允许旋转灯
	uint8_t changeTime;	//转动的间隔时间
	uint8_t rotate_1ms;
	uint8_t mode;				//选择旋转灯的模式
	uint8_t stopFlag;		//暂停为1
}Led_Rotate_Status;		//旋转灯结构体

#endif
