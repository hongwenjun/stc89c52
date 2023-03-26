#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "Nixie.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned char Min,Sec,MiniSec;
unsigned char RunFlag;

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)			//K1按键按下
		{
			RunFlag=!RunFlag;	//启动标志位翻转
		}
		if(KeyNum==2)			//K2按键按下
		{
			Min=0;				//分秒清0
			Sec=0;
			MiniSec=0;
		}
		if(KeyNum==3)			//K3按键按下
		{
			AT24C02_WriteByte(0,Min);	//将分秒写入AT24C02
			Delay(5);
			AT24C02_WriteByte(1,Sec);
			Delay(5);
			AT24C02_WriteByte(2,MiniSec);
			Delay(5);
		}
		if(KeyNum==4)			//K4按键按下
		{
			Min=AT24C02_ReadByte(0);	//读出AT24C02数据
			Sec=AT24C02_ReadByte(1);
			MiniSec=AT24C02_ReadByte(2);
		}
		Nixie_SetBuf(1,Min/10);	//设置显示缓存，显示数据
		Nixie_SetBuf(2,Min%10);
		Nixie_SetBuf(3,11);
		Nixie_SetBuf(4,Sec/10);
		Nixie_SetBuf(5,Sec%10);
		Nixie_SetBuf(6,11);
		Nixie_SetBuf(7,MiniSec/10);
		Nixie_SetBuf(8,MiniSec%10);
	}
}

/**
  * @brief  秒表驱动函数，在中断中调用
  * @param  无
  * @retval 无
  */
void Sec_Loop(void)
{
	if(RunFlag)
	{
		MiniSec++;
		if(MiniSec>=100)
		{
			MiniSec=0;
			Sec++;
			if(Sec>=60)
			{
				Sec=0;
				Min++;
				if(Min>=60)
				{
					Min=0;
				}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count1,T0Count2,T0Count3;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count1++;
	if(T0Count1>=20)
	{
		T0Count1=0;
		Key_Loop();	//20ms调用一次按键驱动函数
	}
	T0Count2++;
	if(T0Count2>=2)
	{
		T0Count2=0;
		Nixie_Loop();//2ms调用一次数码管驱动函数
	}
	T0Count3++;
	if(T0Count3>=10)
	{
		T0Count3=0;
		Sec_Loop();	//10ms调用一次数秒表驱动函数
	}
}
