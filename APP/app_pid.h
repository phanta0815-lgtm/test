#ifndef __APP_PID_H
#define __APP_PID_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：电机PID调节头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"
#include "params.h"

extern float edata AngleX,AngleY,AngleZ;			//四元数解算出的欧拉角
extern u8 YM,FRX,FRY,FRZ;								//4通道遥控信号

//函数声明
void PID_Init(void);
void PID_Task(void);

#endif
