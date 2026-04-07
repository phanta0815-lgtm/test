#include "control.h"

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：控制任务
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

/**************************************************************************************************
* 功能：控制任务
* 参数：无
* 描述：无
**************************************************************************************************/
void Control_Task(void)
{
	ADC_Task();				//ADC电量采集任务
	NRF24L01_Task();		//NRF24L01任务
	PID_Task();				//电机PID调节任务
	Motor_Task();			//电机控制任务
	DO_Output();			//开关量输出
}

/**************************************************************************************************
* 功能：无人机锁任务
* 参数：无
* 描述：无
**************************************************************************************************/
void Lock_Task(void)
{
	//失控保护
	if(run.wireless_state==0)
	{
		run.lock = 0;
	}
	
	//XY轴方向倾斜过大保护
	if((AngleX<-50)||(AngleX>50)||(AngleY<-50)||(AngleY>50))
	{
		run.lock = 0;
	}
	
	if(run.lock == 0)	//上锁，停机
	{
		run.motor_speed[0] = 0;
		run.motor_speed[1] = 0;
		run.motor_speed[2] = 0;
		run.motor_speed[3] = 0;
		
		run.height = 0;
		run.aircraft_state = 0;
	}
	else				//正常工作
	{
		run.height = ((float)run.adjust_air_press - run.air_press)*9.0/10;			//高度计算,1Pa约等于0.09米
		run.height_now = ((float)run.adjust_air_press - run.air_press_now)*9.0/10;	//高度计算,1Pa约等于0.09米(用于悬停控制)
	}
}

/**************************************************************************************************
* 功能：NRF24L01任务
* 参数：无
* 描述：无
**************************************************************************************************/
void NRF24L01_Task(void)
{
	u8 xdata buf[32] = {0};
	
	if(!NRF24L01_RxPacket(buf))
	{
		run.accelerator = buf[0];			//油门
		run.direction_x = buf[1];           //X轴横滚
		run.direction_y = buf[2];           //Y轴俯仰
		run.telecontrol_direction = buf[3]; //航向
		if(buf[4] == 1)
		{
			sys.mpu_x++;
			run.save_flag = 1;
		}
		else if(buf[4] == -1)
		{
			sys.mpu_x--;
			run.save_flag = 1;
		}
		if(buf[5] == 1)
		{
			sys.mpu_y++;
			run.save_flag = 1;
		}
		else if(buf[5] == -1)
		{
			sys.mpu_y--;
			run.save_flag = 1;
		}
		if(buf[6] == 2)						//飞机状态，0：手动，1：自动，2：悬停
		{
			if(run.aircraft_state!=2)
			{
				run.hover_height = run.height_now;	//记录悬停高度
			}
		}  
		run.aircraft_state = buf[6];
		if(buf[7]==1)						//遥控锁解锁
		{
			if(run.lock == 0)
			{
				run.adjust_air_press = run.air_press;
				run.height = 0;
				run.lock=1;
			}
		}
		if(buf[7]==2)						//遥控锁上锁			
		{
			run.lock=0;
		}
		
		if(buf[8] == 0x55)
		{
			run.y^=0x01;
		}

		//发送
		NRF24L01_TX_Mode();					//发送模式
		buf[0] = run.aircraft_power;
		buf[1] = run.aircraft_direction>>8;
		buf[2] = run.aircraft_direction;
		buf[3] = run.aircraft_state;
		buf[4] = run.height>>8;
		buf[5] = run.height;
		buf[6] = run.lock;
		buf[7] = 0x55;
		NRF24L01_TxPacket(buf);				//发送数据
		NRF24L01_RX_Mode();					//接收模式
		
		
		//正常通讯
		run.wireless_state = 1;
		run.wireless_count=0;
	}	
	else
	{
		//断线计数
		run.wireless_count++;
		if(run.wireless_count>=50)
		{
			run.wireless_count=50;
			run.wireless_state=0;
		}
	}
}
