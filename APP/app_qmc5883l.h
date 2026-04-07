#ifndef __APP_QMC5883L_H
#define __APP_QMC5883L_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：QMC5883L地磁仪头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"
#include "params.h"

#define QMC5883_Address 0x1A

extern float Angle_XY;	

//函数声明
void QMC5883L_Init(void);
void Single_Write_QMC5883(uchar REG_Address,uchar REG_data);
void Multiple_Read_QMC5883(void);
void QMC5883L_Task(void);

#endif
