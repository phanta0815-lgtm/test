#include "app_qmc5883l.h"

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：QMC5883L地磁仪
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

u8 BUF[8]={0}; 						 //数据缓冲区

int QMC_X=0,QMC_Y=0,QMC_Z=0;
float Angle_XY=0;	

/**************************************************************************************************
* 功能：QMC5883L地磁仪初始化
* 参数：无
* 描述：无
**************************************************************************************************/
void QMC5883L_Init(void)
{
	Single_Write_QMC5883(0x0A,0x80);  //控制寄存器配置，复位芯片
	delay_ms(100);
	Single_Write_QMC5883(0x09,0x0d);  //连续模式，50Hz
	Single_Write_QMC5883(0x0A,0x00);  //控制寄存器配置
	Single_Write_QMC5883(0x0B,0x01);  //
}

//************************写入单字节数据***************************
void Single_Write_QMC5883(uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  	//起始信号
    I2C_SendByte(QMC5883_Address);  //发送设备地址+写信号
    I2C_SendByte(REG_Address);    	//内部寄存器地址，请参考中文pdf 
    I2C_SendByte(REG_data);       	//内部寄存器数据，请参考中文pdf
    I2C_Stop();                   	//发送停止信号
}

//******************************************************
//连续读出QMC5883内部角度数据，地址范围0x00~0x05
//******************************************************
void Multiple_Read_QMC5883(void)
{   
    uchar i;
    I2C_Start();                          //起始信号
    I2C_SendByte(QMC5883_Address);          //发送设备地址+写信号
    I2C_SendByte(0x00);                   //发送存储单元地址，从0x00开始	
    I2C_Start();                          //起始信号
    I2C_SendByte(QMC5883_Address+1);        //发送设备地址+读信号
	for (i=0; i<5; i++)                      //连续读取6个地址数据，存储中BUF
	{
		BUF[i] = I2C_RecvByte();          //BUF[0]存储数据
		SDA = 0;                    //写应答信号
		SCL = 1;                    //拉高时钟线
		Delay2us();                 //延时
		SCL = 0;                    //拉低时钟线
		Delay2us();                 //延时
	}
	BUF[i] = I2C_RecvByte();	//最后一个字节
	SDA = 1;                    //写非应答信号
	SCL = 1;                    //拉高时钟线
	Delay2us();                 //延时
	SCL = 0;                    //拉低时钟线
	Delay2us();                 //延时
	
    I2C_Stop();                    //停止信号
}

/**************************************************************************************************
* 功能：QMC5883L地磁仪任务
* 参数：无
* 描述：无
**************************************************************************************************/
void QMC5883L_Task(void)
{
	Multiple_Read_QMC5883();
	
	QMC_X = (BUF[1]<<8) | BUF[0]; //Combine MSB and LSB of X Data output register  最高有效位
	QMC_Y = (BUF[3]<<8) | BUF[2]; //Combine MSB and LSB of Y Data output register
	QMC_Z = (BUF[5]<<8) | BUF[4]; //Combine MSB and LSB of Z Data output register

	Angle_XY= (float)atan2(QMC_Y,QMC_X) * 180.0 / 3.1415926 + 180.0; //计算XY平面角度
}
