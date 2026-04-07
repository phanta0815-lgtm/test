#ifndef __APP_WDT_H
#define __APP_WDT_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：看门狗设置头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"

#define D_WDT_FLAG          (1<<7)		//看门狗溢出标志
#define D_EN_WDT            (1<<5)		//看门狗使能
#define D_CLR_WDT           (1<<4)  	//看门狗定时器清零
#define D_IDLE_WDT          (1<<3)  	//看门狗空闲模式继续计数
#define D_WDT_SCALE_2       0			//溢出时间0.039s
#define D_WDT_SCALE_4       1			//溢出时间0.078s
#define D_WDT_SCALE_8       2 			//溢出时间0.157s      
#define D_WDT_SCALE_16      3			//溢出时间0.315s
#define D_WDT_SCALE_32      4			//溢出时间0.629s
#define D_WDT_SCALE_64      5			//溢出时间1.26s
#define D_WDT_SCALE_128     6			//溢出时间2.52s
#define D_WDT_SCALE_256     7			//溢出时间5.03s

//函数声明
void WDT_Init(void);
void Feed_Dog(void);

#endif
