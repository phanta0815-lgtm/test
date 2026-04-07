#include "app_bmp280.h"

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：BMP280气压计
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

unsigned short dig_T1;
short dig_T2;
short dig_T3;
unsigned short dig_P1;
short dig_P2;
short dig_P3;
short dig_P4;
short dig_P5;
short dig_P6;
short dig_P7;
short dig_P8;
short dig_P9;

/**************************************************************************************************
* 功能：BMP280气压计初始化
* 参数：无
* 描述：无
**************************************************************************************************/
void BMP280_Init(void)
{
	//状态全部清零
    bmp280_WriteByte(0xe0, 0xb6);
	bmp280_WriteByte(0xf4, 0xff);
    bmp280_WriteByte(0xf5, 0x00);
	delay_ms(2); 
	dig_T1 = bmp280_MultipleReadTwo(0x88);
    dig_T2 = bmp280_MultipleReadTwo(0x8A);
    dig_T3 = bmp280_MultipleReadTwo(0x8C);
    dig_P1 = bmp280_MultipleReadTwo(0x8E);
    dig_P2 = bmp280_MultipleReadTwo(0x90);
    dig_P3 = bmp280_MultipleReadTwo(0x92);
    dig_P4 = bmp280_MultipleReadTwo(0x94);
    dig_P5 = bmp280_MultipleReadTwo(0x96);
    dig_P6 = bmp280_MultipleReadTwo(0x98);
    dig_P7 = bmp280_MultipleReadTwo(0x9A);
    dig_P8 = bmp280_MultipleReadTwo(0x9C);
    dig_P9 = bmp280_MultipleReadTwo(0x9E);
}

void bmp280_WriteByte(u8 addr, u8 dat)
{
    I2C_Start();
    I2C_SendByte(BMP280_ADDR);
    I2C_SendByte(addr);
    I2C_SendByte(dat);
    I2C_Stop();
}

u8 bmp280_ReadByte(u8 addr)
{
    u8 temp;

    I2C_Start();
    I2C_SendByte(BMP280_ADDR);
    I2C_SendByte(addr);

    I2C_Start();
    I2C_SendByte(BMP280_ADDR + 1);
    temp = I2C_RecvByte();
    SDA = 1;                    //写非应答信号
	Delay2us();                 //延时
	SCL = 1;                    //拉高时钟线
	Delay2us();                 //延时
	SCL = 0;                    //拉低时钟线
	Delay2us();                 //延时
    I2C_Stop();

    return temp;
}

short bmp280_MultipleReadTwo(u8 addr)
{
    u8 msb, lsb;
    short temp = 0;
	
    lsb = bmp280_ReadByte(addr);
    msb = bmp280_ReadByte((u8)(addr + 1));

    temp = (short)msb << 8;
    temp |= (short)lsb;

    return temp;
}

long bmp280_MultipleReadThree(u8 addr)
{
    unsigned char msb, lsb, xlsb;
    long temp = 0;
    msb = bmp280_ReadByte(addr);
    lsb = bmp280_ReadByte((u8)(addr + 1));
    xlsb = bmp280_ReadByte((u8)(addr + 2));

    temp = (long)(((unsigned long)msb << 12)|((unsigned long)lsb << 4)|((unsigned long)xlsb >> 4));

    return temp;
}

long var1, var2, t_fine, T, p;

float bmp280_GetPress(void)
{
    long adc_T;
    long adc_P;
    

    adc_T = bmp280_MultipleReadThree(BMP280_TEMP_ADDR);
    adc_P = bmp280_MultipleReadThree(BMP280_PRESS_ADDR);

    if(adc_P == 0)
    {
        return 0;
    }

    //Temperature
    var1 = (((float)adc_T)/16384.0-((float)dig_T1)/1024.0)*((float)dig_T2);
    var2 = ((((float)adc_T)/131072.0-((float)dig_T1)/8192.0)*(((float)adc_T)
                /131072.0-((float)dig_T1)/8192.0))*((float)dig_T3);

    t_fine = (unsigned long)(var1+var2);

    T = (var1+var2)/5120.0;

    var1 = ((float)t_fine/2.0)-64000.0;
    var2 = var1*var1*((float)dig_P6)/32768.0;
    var2 = var2 +var1*((float)dig_P5)*2.0;
    var2 = (var2/4.0)+(((float)dig_P4)*65536.0);
    var1 = (((float)dig_P3)*var1*var1/524288.0+((float)dig_P2)*var1)/524288.0;
    var1 = (1.0+var1/32768.0)*((float)dig_P1);
    p = 1048576.0-(float)adc_P;
    p = (p-(var2/4096.0))*6250.0/var1;
    var1 = ((float)dig_P9)*p*p/2147483648.0;
    var2 = p*((float)dig_P8)/32768.0;
    p = p+(var1+var2+((float)dig_P7))/16.0;

    return p;
}

/**************************************************************************************************
* 功能：BMP280气压计任务
* 参数：无
* 描述：滚动滤波时间3s，50ms计算一次，最低位变化1大约对应10cm高度
**************************************************************************************************/
void BMP280_Task(void)
{
	uint8_t i;
	uint32_t sum=0;
	static uint8_t num=0;
	static uint16_t peress_buff[60]={0};
	
	peress_buff[num]=(uint16_t)bmp280_GetPress();
	run.air_press_now = peress_buff[num];
	
	num++;
	if(num>=60)
	{
		num=0;
	}
	
	for(i=0;i<60;i++)
	{
		sum += peress_buff[i];
	}
	run.air_press = sum/60;
}
