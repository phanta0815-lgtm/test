#ifndef __APP_MOTOR_H
#define __APP_MOTOR_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：电机控制头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app_public.h"
#include "params.h"

#define PWM1	P20		//M1
#define PWM2	P22		//M2
#define PWM3	P04		//M3
#define PWM4	P06		//M4

#define PWM_PERIOD  2000   //设置周期值,对应11kHz

#define PWM1_0      0x00	//P:P1.0  N:P1.1
#define PWM1_1      0x01	//P:P0.0  N:P0.1
#define PWM1_2      0x02	//P:P2.0  N:P2.1

#define PWM2_0      0x00	//P:P1.2  N:P1.3
#define PWM2_1      0x04	//P:P0.2  N:P0.3
#define PWM2_2      0x08	//P:P2.2  N:P2.3

#define PWM3_0      0x00	//P:P1.4  N:P1.5
#define PWM3_1      0x10	//P:P0.4  N:P0.5
#define PWM3_2      0x20	//P:P2.4  N:P2.5

#define PWM4_0      0x00	//P:P1.6  N:P1.7
#define PWM4_1      0x40	//P:P0.6  N:P0.7
#define PWM4_2      0x80	//P:P2.6  N:P2.7

#define ENO1P       0x01	//PWM输出控制位
#define ENO1N       0x02
#define ENO2P       0x04
#define ENO2N       0x08
#define ENO3P       0x10
#define ENO3N       0x20
#define ENO4P       0x40
#define ENO4N       0x80

//函数声明
void Motor_Init(void);
void Motor_Task(void);
void PWM_Output(void);

#endif
