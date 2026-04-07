#ifndef __APP_UTILS_H
#define __APP_UTILS_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：功能函数头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"

//8位共用体
typedef union 
{
    uint8_t RegByte;
    struct
    {
        uint8_t b0 :1;
        uint8_t b1 :1;
        uint8_t b2 :1;
        uint8_t b3 :1;
        uint8_t b4 :1;
        uint8_t b5 :1;
        uint8_t b6 :1;
        uint8_t b7 :1;
    } RegBits;
} REG8_T;

//16位共用体
typedef union 
{
    uint16_t RegWord;
    struct
    {
        uint8_t LoByte;
        uint8_t HiByte;
    } RegBytes;
    struct
    {
        uint16_t b0 :1;
        uint16_t b1 :1;
        uint16_t b2 :1;
        uint16_t b3 :1;
        uint16_t b4 :1;
        uint16_t b5 :1;
        uint16_t b6 :1;
        uint16_t b7 :1;
        uint16_t b8 :1;
        uint16_t b9 :1;
        uint16_t b10 :1;
        uint16_t b11 :1;
        uint16_t b12 :1;
        uint16_t b13 :1;
        uint16_t b14 :1;
        uint16_t b15 :1;
    } RegBits;
} REG16_T;

//32位共用体
typedef union 
{
	uint32_t RegWords;
	struct
    {
        REG16_T LoByte;
        REG16_T HiByte;
    } RegWord;
	struct
    {
        uint8_t Byte0;
        uint8_t Byte1;
		uint8_t Byte2;
		uint8_t Byte3;
    } RegBytes;
	struct
    {
        uint16_t b0 :1;
        uint16_t b1 :1;
        uint16_t b2 :1;
        uint16_t b3 :1;
        uint16_t b4 :1;
        uint16_t b5 :1;
        uint16_t b6 :1;
        uint16_t b7 :1;
        uint16_t b8 :1;
        uint16_t b9 :1;
        uint16_t b10 :1;
        uint16_t b11 :1;
        uint16_t b12 :1;
        uint16_t b13 :1;
        uint16_t b14 :1;
        uint16_t b15 :1;
		uint16_t b16 :1;
        uint16_t b17 :1;
        uint16_t b18 :1;
        uint16_t b19 :1;
        uint16_t b20 :1;
        uint16_t b21 :1;
        uint16_t b22 :1;
        uint16_t b23 :1;
        uint16_t b24 :1;
        uint16_t b25 :1;
        uint16_t b26 :1;
        uint16_t b27 :1;
        uint16_t b28 :1;
        uint16_t b29 :1;
        uint16_t b30 :1;
        uint16_t b31 :1;
    } RegBits;
} REG32_T;

//函数声明
uint16_t CRC16(uint8_t *pData, uint16_t Length, uint8_t mode);
void my_memcpy(uint8_t *dest, uint8_t *src, uint16_t n);
void Set_bit(u16 *p, u8 bitnum);
void Reset_bit(u16 *p, u8 bitnum);

#endif
