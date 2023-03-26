#include <REGX52.H>

/**
  * @brief  定时器1初始化，100us@12.000MHz
  * @param  无
  * @retval 无
  */
void Timer1_Init(void)
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x9C;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1=1;
	EA=1;
	PT1=0;
}

/*定时器中断函数模板
void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count;
	TL1 = 0x9C;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	T1Count++;
	if(T1Count>=1000)
	{
		T1Count=0;
		
	}
}
*/
