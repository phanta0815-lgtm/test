#ifndef __APP_H
#define __APP_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：外设初始化头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_di.h"
#include "app_do.h"
#include "app_delay.h"
#include "app_timer.h"
#include "app_eeprom.h"
#include "app_utils.h"
#include "app_wdt.h"
#include "app_ai.h"
#include "app_nrf24l01.h"
#include "app_motor.h"
#include "app_mpu6050.h"
#include "app_iic.h"
#include "app_bmp280.h"
#include "app_pid.h"

//函数声明
void App_Init(void);

#endif
