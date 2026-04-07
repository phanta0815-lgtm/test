#ifndef __APP_EEPROM_H
#define __APP_EEPROM_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：EEPROM读写控制头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"

#define IAP_STANDBY()   IAP_CMD = 0     //IAP空闲命令（禁止）
#define IAP_READ()      IAP_CMD = 1     //IAP读出命令
#define IAP_WRITE()     IAP_CMD = 2     //IAP写入命令
#define IAP_ERASE()     IAP_CMD = 3     //IAP擦除命令

#define IAP_EN          (1<<7)
#define IAP_SWBS        (1<<6)
#define IAP_SWRST       (1<<5)
#define IAP_CMD_FAIL    (1<<4)

#define IAP_ENABLE()    IAP_CONTR = IAP_EN; IAP_TPS = MAIN_Fosc / 1000000
#define IAP_DISABLE()   IAP_CONTR = 0; IAP_CMD = 0; IAP_TRIG = 0; IAP_ADDRE = 0xff; IAP_ADDRH = 0xff; IAP_ADDRL = 0xff

//函数声明
void DisableEEPROM(void);
void EEPROM_Trig(void);
void EEPROM_SectorErase(u32 EE_address);
void EEPROM_read_n(u32 EE_address,u8 *DataAddress,u8 length);
u8 EEPROM_write_n(u32 EE_address,u8 *DataAddress,u8 length);

#endif
