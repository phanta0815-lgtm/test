#ifndef __PARAMS_H
#define __PARAMS_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：参数初始化头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app.h"

//版本号
#define PROGRAM_VERSION		100				//程序版本号
#define GUI_VERSION			100				//该程序对应的界面版本号

//参数保存页地址
#define FLASH_SYS_ADDRESS_PAGE	0			//最后一页

//系统参数
typedef struct
{
	uint16_t debug1;
	
	uint16_t battery_zero;					//电池调零
	uint16_t battery_full;					//电池调满
	
	int16_t mpu_x;							//MPU6050 X轴横滚角度调节 
	int16_t mpu_y;							//MPU6050 Y轴俯仰角度调节
	
	uint16_t hover_P;						//悬停PID比例P
	uint16_t hover_I;						//悬停PID比例I
	uint16_t hover_D;						//悬停PID比例D
	
	uint16_t crc16_data;					//CRC16校验
} SYS_T;
#define SYS_NUM	sizeof(SYS_T)/2				//系统参数个数

//运行参数			
typedef struct			
{
	uint16_t debug1;
	uint16_t x;								//开关量输入
	uint16_t y;								//开关量输出
	uint16_t accelerator;					//油门大小，0~255
	uint16_t direction_x;					//X轴左右方向移动，0~255
	uint16_t direction_y;					//Y轴前后方向移动，0~255
	uint16_t aircraft_power;				//飞机电量0-100%
	uint16_t wireless_state;				//无线状态
	uint16_t telecontrol_direction;			//遥控控制航向
	uint16_t aircraft_direction;			//实际无人机航向
	uint16_t aircraft_state;				//飞机状态，0：手动，1：自动，2：悬停
	int16_t height;							//高度（滤波后）
	int16_t height_now;						//实时高度
	uint16_t lock;							//遥控锁，0：锁住，1：解锁
	
	//悬停PID参数
	int16_t  hover_accelerator;				//悬停油门控制
	int16_t  hover_height;					//悬停高度
	
	
	uint16_t air_press;						//气压（滤波后）
	uint16_t air_press_now;					//实时气压
	uint16_t adjust_air_press;				//校准气压
	uint16_t save_flag;						//数据保存标志
	
	int16_t motor_speed[4];					//电机速度
	uint16_t wireless_count;				//无线断线计数
	
} RUN_T;			
#define RUN_NUM	sizeof(RUN_T)/2				//运行参数个数
	
//变量使用范围扩展
extern SYS_T sys;
extern RUN_T run;

extern uint16_t *p_sys;
extern uint16_t *p_run;

//函数声明
void Params_Init(void);
void Sys_Params_Load(void);
void Sys_Params_Default(void);
void Sys_Params_Default_Part(void);
void Sys_Params_Save(void);
void Sys_Params_Save_Task(void);
void Run_Params_Init(void);

#endif
