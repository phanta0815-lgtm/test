#ifndef __APP_FONT_H
#define __APP_FONT_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-09-03
* 功能：字体编码头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"

#define  HZWIDTH   		16
#define  hz_Num  		5
#define  hzIndex_Num  	hz_Num*2
#define  hzdot_Num  	hz_Num*32

//变量使用范围扩展
extern const uint8_t ASCII_8x16[][16];
extern const uint8_t hzIndex[hzIndex_Num];
extern const uint8_t hzdot[hzdot_Num];
extern const uint8_t BMP_16x16[][32];
extern const uint8_t BMP_32x32[][128];

//函数声明


#endif
