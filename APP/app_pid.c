#include "app_pid.h"

/**************************************************************************************************
* �汾��V1.00
* ���ڣ�2024-10-01
* ���ܣ����PID����ͷ�ļ�
* ���£���ʼ�汾
* ���ߣ�רҵ������
**************************************************************************************************/

int		edata g_x=0,g_y=0,g_z=0;					//�����ǽ�������
float	edata AngleX=0,AngleY=0,AngleZ=0;			//��Ԫ���������ŷ����
float	edata Angle_gx=0,Angle_gy=0,Angle_gz=0;		//�ɽ��ٶȼ���Ľ�����(�Ƕ���)
float	edata Angle_ax=0,Angle_ay=0,Angle_az=0;		//�ɼ��ٶȼ���ļ��ٶ�(������)
float	edata Ax=0,Ay=0,Az=0,Ah;					//����ң������������ĽǶ�    
float	edata PID_x=0,PID_y=0,PID_z=0;				//PID���������
int		edata speed0=0,speed1=0,speed2=0,speed3=0;	//����ٶȲ���
int		edata PWM00=200,PWM01=200,PWM02=200,PWM03=200;		//������PWMģ��Ĳ���

int		int_tmp;
u8		YM=0,FRX=128,FRY=128,FRZ=128;				//4ͨ��ң���ź�
u8		edata	tp[16];		//��MP6050����


//****************��̬������PID*********************************************

float edata Out_PID_X=0,Last_Angle_gx=0;					//�⻷PI�����  ��һ������������
float edata ERRORX_Out=0,ERRORX_In=0;			//�⻷P  �⻷I  �⻷������
float edata Out_PID_Y=0,Last_Angle_gy=0;
float edata ERRORY_Out=0,ERRORY_In=0;            //����1:���⻷P�˻�����10.5
float edata ERROR_H=0;

float edata Last_Ax=0,Last_Ay=0,Last_Az=0,Last_Ah=0;

/******************************************************************************/
//	#define	PID_MODE	0	// PID����ģʽ
	#define	PID_MODE	5	// DIY F380 ������ 2212��� 9450�ҽ�

#if (PID_MODE == 0)	/* PID����ģʽ */
	float edata	Out_XP = 6.65f;		//ADC0	�⻷P	V1 / 10
	float edata	Out_XI = 0.0074f;	//ADC4	�⻷I	V2 / 10000
	float edata	Out_XD = 6.0;		//ADC5	�⻷D	V3 / 10

	float edata	In_XP =	0.8275f;	//ADC6	�ڻ�P	V4 / 100
	float edata	In_XI =	0.0074f;	//ADC4	�ڻ�I	V2 / 10000
	float edata	In_XD =	6.0f;		//ADC5	�ڻ�D	V3 / 10
#endif

#if (PID_MODE == 5)		//DIY F380 ������ 2212��� 9450�ҽ�		�����������, �����½�ʱ����С(������ƽ��, �Ƕ�/4.0)
	#define	Out_XP	6.65f	//ADC0	�⻷P	V1 / 10
	#define	Out_XI	0.0074f	//ADC4	�⻷I	V2 / 10000
	#define	Out_XD	6.0f	//ADC5	�⻷D	V3 / 10

	#define	In_XP	0.8275f	//ADC6	�ڻ�P	V4 / 100
	#define	In_XI	0.0074f	//ADC4	�ڻ�I	V2 / 10000
	#define	In_XD	6.0f	//ADC5	�ڻ�D	V3 / 10
#endif


#define	Out_YP	Out_XP
#define	Out_YI	Out_XI
#define	Out_YD	Out_XD

#define	In_YP	In_XP
#define	In_YI	In_XI
#define	In_YD	In_XD

//=================== �������Ƶ�P I D ==================================

//float ZP=5.0,ZI=0.1;	//�������Ƶ�P D

#define	ZP	5.0f
#define	ZI	0.1f
#define	ZD	4.0f	//�������Ƶ�P D

float Z_integral=0;//Z�����

#define	ERR_MAX	500

/**************************************************************************************************
* ���ܣ�PID��ʼ��
* ��������
* ��������
**************************************************************************************************/
void PID_Init(void)
{

}

//*********************************************************************
//****************�Ƕȼ���*********************************************
//*********************************************************************
#define	pi		3.14159265f                           
#define	Kp		0.8f                        
#define	Ki		0.001f                         
#define	halfT	0.004f           

float edata q0=1,q1=0,q2=0,q3=0;   
float edata exInt=0,eyInt=0,ezInt=0;  


void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
	float edata norm;
	float edata vx, vy, vz;
	float edata ex, ey, ez;

	norm = sqrt(ax*ax + ay*ay + az*az);
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;

	vx = 2*(q1*q3 - q0*q2);
	vy = 2*(q0*q1 + q2*q3);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3 ;

	ex = (ay*vz - az*vy) ;
	ey = (az*vx - ax*vz) ;
	ez = (ax*vy - ay*vx) ;

	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	gx = gx + Kp*ex + exInt;
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;

	q0 = q0 + (-q1*gx - q2*gy - q3*gz) * halfT;
	q1 = q1 + ( q0*gx + q2*gz - q3*gy) * halfT;
	q2 = q2 + ( q0*gy - q1*gz + q3*gx) * halfT;
	q3 = q3 + ( q0*gz + q1*gy - q2*gx) * halfT;

	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;
	
	AngleX = asin(2*(q0*q2 - q1*q3 )) * 57.2957795f;
	AngleY = asin(2*(q0*q1 + q2*q3 )) * 57.2957795f; 
	AngleZ = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.2957795f;//����

}

void PID_Task(void)
{
	FRX = run.direction_x;			//���
	FRY = run.direction_y;			//����
	FRZ = run.telecontrol_direction;//����
	if(run.aircraft_state!=2)		//����ͣ״̬�����ſ���
	{
		YM  = run.accelerator;		//����0-255
		if(YM >= 190)	YM = 190;	//�����������һ������ռ䣬����������ʱƫ��
	}
	
//	 
////	//********************************************************************************************
	Read_MPU6050(tp);	// 720us @24MHz

	Angle_ax = ((float)(((int *)&tp)[0])) / 8192.0;	//���ٶȴ���	�����λ�� +- g
	Angle_ay = ((float)(((int *)&tp)[1])) / 8192.0;	//ת����ϵ	8192 LSB/g, 1g��Ӧ����8192
	Angle_az = ((float)(((int *)&tp)[2])) / 8192.0;	//���ٶ����� +-4g/S
	Last_Angle_gx = Angle_gx;		//������һ�ν��ٶ�����
	Last_Angle_gy = Angle_gy;
	Angle_gx = ((float)(((int *)&tp)[4] - g_x)) / 65.5;	//�����Ǵ���	�����λ�� +-��
	Angle_gy = ((float)(((int *)&tp)[5] - g_y)) / 65.5;	//���������� +-500��/S, 1��/�� ��Ӧ���� 65.536
	Angle_gz = ((float)(((int *)&tp)[6] - g_z)) / 65.5;	//ת����ϵ65.5 LSB/��

	IMUupdate(Angle_gx*0.0174533f, Angle_gy*0.0174533f, Angle_gz*0.0174533f, Angle_ax,Angle_ay,Angle_az);	// 0.8~1.0ms @24MHz

//**********************************X��ָ��************************************************
	Ax  = AngleX - sys.mpu_x*0.1 - ((float)FRX - 128) / 4.0;		//�Ƕȿ������������Ƕ�

	if(YM > 20)	ERRORX_Out += Ax,	ERRORX_Out += Ax,	ERRORX_Out += Ax;	//�⻷����(����С��ĳ��ֵʱ������)
	else		ERRORX_Out = 0; //����С�ڶ�ֵʱ�������ֵ
		 if(ERRORX_Out >  1500)	ERRORX_Out =  1500;
	else if(ERRORX_Out < -1500)	ERRORX_Out = -1500;	//�����޷�

	Out_PID_X = Ax*Out_XP + ERRORX_Out*Out_XI + (Ax-Last_Ax)*Out_XD;	//�⻷PID
	Last_Ax = Ax;
	
	if(YM > 20)	ERRORX_In += (Angle_gy - Out_PID_X);	//�ڻ�����(����С��ĳ��ֵʱ������)
	else		ERRORX_In = 0;	//����С�ڶ�ֵʱ�������ֵ
		 if(ERRORX_In >  500)	ERRORX_In =  500;
	else if(ERRORX_In < -500)	ERRORX_In = -500;	//�����޷�

	PID_x = (Angle_gy + Out_PID_X) * In_XP + ERRORX_In * In_XI + (Angle_gy - Last_Angle_gy) * In_XD;	//�ڻ�PID
	if(PID_x >  500)	PID_x =  500;	//������޷�
	if(PID_x < -500)	PID_x = -500;

//**************Y��ָ��**************************************************
	Ay  = AngleY - sys.mpu_y*0.1 + ((float)FRY - 128) / 4.0;		//�Ƕȿ������������Ƕ�
	
	if(YM > 20)	ERRORY_Out += Ay,	ERRORY_Out += Ay,	ERRORY_Out += Ay;	//�⻷����(����С��ĳ��ֵʱ������)
	else		ERRORY_Out = 0; //����С�ڶ�ֵʱ�������ֵ
		 if(ERRORY_Out >  1500)	ERRORY_Out =  1500;
	else if(ERRORY_Out < -1500)	ERRORY_Out = -1500;	//�����޷�
	
	Out_PID_Y = Ay * Out_YP + ERRORY_Out * Out_YI + (Ay-Last_Ay)*Out_YD;	//�⻷PID
	Last_Ay = Ay;

	if(YM > 20)	ERRORY_In += (Angle_gx - Out_PID_Y);  //�ڻ�����(����С��ĳ��ֵʱ������)
	else		ERRORY_In = 0; //����С�ڶ�ֵʱ�������ֵ
		 if(ERRORY_In >  500)	ERRORY_In =  500;
	else if(ERRORY_In < -500)	ERRORY_In = -500;	//�����޷�
	
	PID_y = (Angle_gx + Out_PID_Y) * In_YP + ERRORY_In * In_YI + (Angle_gx - Last_Angle_gx) * In_YD;	//�ڻ�PID
	
	if(PID_y > 500)	PID_y =  500;	//������޷�
	if(PID_y <-500)	PID_y = -500;
	
//**************Z��ָ��*****************************	
	Az = Angle_gz + ((float)FRZ - 128);
	
	run.aircraft_direction = 360-AngleZ;		//����
	if(run.aircraft_direction>=360)
	{
		run.aircraft_direction = run.aircraft_direction - 360;
	}
	
	if(YM > 20)	Z_integral += Az;	//Z�����
	else		Z_integral = 0;		//����С��40��������
		 if(Z_integral >  1000.0f)	Z_integral =  1000.0f;	//�����޷�
	else if(Z_integral < -1000.0f)	Z_integral = -1000.0f;	//�����޷�

	PID_z = Az * ZP + Z_integral * ZI + (Az - Last_Az) * ZD;
	Last_Az = Az;
	if(PID_z >  200)	PID_z =  200;	//������޷�
	if(PID_z < -200)	PID_z = -200;

	speed0 = (int)(  PID_x - PID_y - PID_z);	//��������ٶ�����ֵ
	speed1 = (int)(0-PID_x - PID_y + PID_z);
	speed2 = (int)(  PID_x + PID_y + PID_z);
	speed3 = (int)(0-PID_x + PID_y - PID_z);

//**************��ͣPID����*****************************	
	if(run.aircraft_state==2)		//��ͣ״̬
	{
		Ah = run.hover_height - run.height_now;
	
		ERROR_H += Ah;ERROR_H += Ah;ERROR_H += Ah;
		if(ERROR_H >  3000)	ERROR_H =  3000;
		else if(ERROR_H < -3000)	ERROR_H = -3000;	//�����޷�
		
		if(((Ah>=0)&&(Last_Ah<0))||((Ah<0)&&(Last_Ah>=0)))	//��������
		{
			ERROR_H = 0;
		}
		
		run.hover_accelerator = (int16_t)(sys.hover_P*Ah*1.0 + sys.hover_I*ERROR_H*0.2 + sys.hover_D*(Ah-Last_Ah)*0.1);
		Last_Ah = Ah;
		
		if(run.hover_accelerator > 250)	run.hover_accelerator =  250;	//������޷�
		if(run.hover_accelerator <-250)	run.hover_accelerator = -250;
	}
	else
	{
		run.hover_accelerator = 0;
		ERROR_H = 0;
		Ah = 0;
		Last_Ah = 0;
	}
	
//**************���ٶȲ���������PWMģ��*************************************************	
	if(YM < 10)	run.motor_speed[0] = 0, run.motor_speed[1] = 0, run.motor_speed[2] = 0, run.motor_speed[3] = 0;
	else
	{
		int_tmp = run.hover_accelerator + (int)YM * 8;	//��ͣPID + ����

		run.motor_speed[0] = int_tmp + speed0;	// +�ٶ�����ֵ
			 if(run.motor_speed[0] > 2000)	run.motor_speed[0] = 2000;    //�ٶȲ������ƣ���ֹ����PWM������Χ0-2000
		else if(run.motor_speed[0] < 0)	run.motor_speed[0] = 0;

		run.motor_speed[1] = int_tmp + speed1;	// +�ٶ�����ֵ
			 if(run.motor_speed[1] > 2000)	run.motor_speed[1] = 2000;
		else if(run.motor_speed[1] < 0)	run.motor_speed[1] = 0;

		run.motor_speed[2] = int_tmp + speed2;	// +�ٶ�����ֵ
			 if(run.motor_speed[2] > 2000)	run.motor_speed[2] = 2000;
		else if(run.motor_speed[2] < 0)	run.motor_speed[2] = 0;

		run.motor_speed[3] = int_tmp + speed3;	// +�ٶ�����ֵ
			 if(run.motor_speed[3] > 2000)	run.motor_speed[3] = 2000;
		else if(run.motor_speed[3] < 0)	run.motor_speed[3] = 0;
	}
	
	Lock_Task();		//���˻�������
}
