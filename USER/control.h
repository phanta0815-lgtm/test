#ifndef __CONTROL_H
#define __CONTROL_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：控制任务头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app.h"

extern float AngleX,AngleY;					//四元数解算出的欧拉角

//函数声明
void Control_Task(void);
void Lock_Task(void);
void Key_Task(void);
void Disp_Task(void);
void NRF24L01_Task(void);

#endif
