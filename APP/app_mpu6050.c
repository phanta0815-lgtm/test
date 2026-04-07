#include "app_mpu6050.h"

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：MPU6050陀螺仪
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

/**************************************************************************************************
* 功能：MPU6050陀螺仪初始化
* 参数：无
* 描述：无
**************************************************************************************************/
void MPU6050_Init(void)
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);  //陀螺仪125hz
	Single_WriteI2C(CONFIG1, 0x04);      //21HZ滤波 延时A8.5ms G8.3ms  此处取值应相当注意，延时与系统周期相近为宜
	Single_WriteI2C(GYRO_CONFIG, 0x08); //陀螺仪500度/S 65.5LSB/g
	Single_WriteI2C(ACCEL_CONFIG, 0x08);//加速度+-4g  8192LSB/g
	delay_ms(100);
}

//**************************************
//向I2C设备写入一个字节数据
//**************************************
void Single_WriteI2C(u8 REG_Address,u8 REG_data)
{
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
}

void Read_MPU6050(u8 *buf)
{
	u8	i;
	
	I2C_Start();                  //起始信号
	I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
	I2C_SendByte(ACCEL_XOUT_H);    //内部寄存器地址，
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号
	for(i=0; i<13; i++)
	{
		buf[i] = I2C_RecvByte();       //读出寄存器数据
		SDA = 0;                    //写应答信号
		SCL = 1;                    //拉高时钟线
		Delay2us();                 //延时
		SCL = 0;                    //拉低时钟线
		Delay2us();                 //延时
	}
		buf[i] = I2C_RecvByte();	//最后一个字节
		SDA = 1;                    //写非应答信号
		SCL = 1;                    //拉高时钟线
		Delay2us();                 //延时
		SCL = 0;                    //拉低时钟线
		Delay2us();                 //延时
	I2C_Stop();                    //停止信号
}
