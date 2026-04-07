#ifndef __APP_IIC_H
#define __APP_IIC_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：IIC协议头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"
#include "app_delay.h"

#define	SDA	P23		//SDA
#define	SCL	P24		//SCL

//函数声明
void IIC_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
bit I2C_RecvACK(void);
void I2C_SendByte(u8 dat);
u8 I2C_RecvByte(void);

#endif
