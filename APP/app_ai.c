#include "app_ai.h"

/**************************************************************************************************
* 版本：V1.00
* 日期：2024-10-01
* 功能：模拟量输入
* 更新：初始版本
* 作者：专业理工男
**************************************************************************************************/

/**************************************************************************************************
* 功能：模拟量输入初始化
* 参数：无
* 描述：无
**************************************************************************************************/
void AI_Init(void)
{
	ADCTIM = 0x3f;		//设置 ADC 内部时序，ADC采样时间建议设最大值
    ADCCFG = 0x2f;		//设置 ADC 时钟为系统时钟/2/16/16
    ADC_CONTR = 0x80; 	//使能 ADC 模块
}

/**************************************************************************************************
* 功能：模拟量采集任务
* 参数：channel: 选择要转换的ADC，channel = 0~15
* 描述：无
**************************************************************************************************/
void ADC_Task(void)
{
	static u16 num = 0;
	static u32 sum = 0;
	uint16_t ad_cur_val, ad_range_val;

	sum += Get_ADC12bitResult(3); 
	
	num++;
	if(num >= 50)
	{
		num=0;
		run.aircraft_power = sum/50;
		
		if(run.aircraft_power>=sys.battery_zero)
		{
			ad_cur_val=run.aircraft_power-sys.battery_zero;						//分子
		}
		else
		{
			ad_cur_val = 0;
		}
		
		ad_range_val=sys.battery_full-sys.battery_zero;						//分母
		run.aircraft_power = ad_cur_val*100.0 / ad_range_val;
		
		if(run.aircraft_power>100) run.aircraft_power = 100;
		
		sum= 0;
	}
}

/**************************************************************************************************
* 功能：模拟量采集
* 参数：channel: 选择要转换的ADC，channel = 0~15
* 描述：无
**************************************************************************************************/
u16 Get_ADC12bitResult(u8 channel)  
{
    ADC_RES = 0;
    ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xf0) | channel; //设置ADC转换通道
	ADC_START = 1;//启动ADC转换
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    while(ADC_FLAG == 0);   //wait for ADC finish
    ADC_FLAG = 0;     //清除ADC结束标志
    return  (((u16)ADC_RES << 8) | ADC_RESL);
}
