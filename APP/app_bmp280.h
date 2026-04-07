#ifndef __APP_BMP280_H
#define __APP_BMP280_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：BMP280气压计头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"
#include "app_iic.h"
#include "params.h"

#define BMP280_ADDR         0xEC
#define BMP280_TEMP_ADDR    0xFA
#define BMP280_PRESS_ADDR   0xF7

//函数声明
void BMP280_Init(void);
void bmp280_WriteByte(u8 addr, u8 dat);
u8 bmp280_ReadByte(u8 addr);
short bmp280_MultipleReadTwo(u8 addr);
long bmp280_MultipleReadThree(u8 addr);
float bmp280_GetPress(void);
void BMP280_Task(void);

#endif
