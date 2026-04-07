#ifndef __TASKS_H
#define __TASKS_H

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：任务头文件
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

#include "app.h"
#include "control.h"
#include "debug1.h"

#define PRIORITY_NOR	1				//低优先级
#define PRIORITY_HIG	2				//高优先级

#define TASK_RUN		1				//运行
#define TASK_STOP		0				//停止

//任务结构体
typedef struct
{
	uint8_t Priority;					//优先级
	uint8_t Run;               			//运行或停止
	uint16_t Timer;             		//计数值
	uint16_t ItvTime;           		//重载值
	void (*TaskHook)(void);    			//函数句柄
} TASK_COMPONENTS;

//任务列表
typedef enum
{
	TASK0, 
	TASK1,
	TASK2,
	TASK3,
	TASK4,
	TASK_MAX                			//最大任务数
} TASK_LIST;

//函数声明
void Task_0(void);
void Task_1(void);
void Task_2(void);
void Task_3(void);
void Task_4(void);
void Task_Count(void);
void Task_Process(void);

#endif
