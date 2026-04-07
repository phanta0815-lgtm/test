#ifndef __APP_PUBLIC_H
#define __APP_PUBLIC_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：公共头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "STC8051U.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define	MAIN_Fosc	22118400L   	//定义主时钟

#define	TRUE	1
#define	FALSE	0

#define ENABLE		1
#define DISABLE		0

#define SUCCESS		0
#define FAIL		-1

typedef unsigned char BYTE;
typedef unsigned char uchar;
typedef unsigned int  uint;
typedef unsigned long uword;

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

typedef signed char int8_t;
typedef signed int  int16_t;
typedef signed long int32_t;

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;

#endif
