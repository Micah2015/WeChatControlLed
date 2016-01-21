#ifndef __GLOBAL_H
#define	__GLOBAL_H

#include "stm32f10x_it.h"
#include "string.h"

#define BufferLength				1024

typedef struct
{
	uint8_t count;	//表示呼吸灯查表的第几个
	uint8_t color;			//表示呼吸灯颜色
	uint8_t waitTime;		//表示呼吸灯两个亮度之间的时间间隔
	uint8_t enable;			//是否允许呼吸灯
}Led_Breath_Status;

#endif
