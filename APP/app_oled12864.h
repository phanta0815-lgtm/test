#ifndef __APP_OLED12864_H
#define __APP_OLED12864_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-09-03
* 功能：OLED12864显示头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"
#include "app_delay.h"
#include "app_font.h"

#define X_WIDTH 	128
#define Y_WIDTH 	64

#define OLED_ADDR	0x78	//OLED器件地址

sbit SDA = P2^3;			//数据线
sbit SCL = P2^4;			//时钟线

//函数声明
void OLED12864_Init(void);
void I2C_WriteNbyte(u8 addr, u8 *p, u8 number);
void OLED_WrDat(u8 dat);
void OLED_WrCmd(u8 cmd);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Fill(uchar dat);
void Screen_Refresh(void);
void Oled_Disp_8x16(uint8_t x,uint8_t y,uint8_t text,uint8_t mode);
void OLED_Disp(uint8_t x,uint8_t y,uint8_t *text,uint8_t mode);
void Clear_Buff(void);
void Full_Buff(void);
void OLED_Disp_BMP_16x16(uint8_t x,uint8_t y,uint8_t num);
void Direction_Icon(uint8_t x,uint8_t y,uint8_t num);

#endif
