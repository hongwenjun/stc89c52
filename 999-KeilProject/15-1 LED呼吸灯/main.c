#include <REGX52.H>

sbit LED=P2^0;

void Delay(unsigned int t)
{
	while(t--);
}

void main()
{
	unsigned char Time,i;
	while(1)
	{
		for(Time=0;Time<100;Time++)		//改变亮灭时间，由暗到亮
		{
			for(i=0;i<20;i++)			//计次延时
			{
				LED=0;					//LED亮
				Delay(Time);			//延时Time
				LED=1;					//LED灭
				Delay(100-Time);		//延时100-Time
			}
		}
		for(Time=100;Time>0;Time--)		//改变亮灭时间，由亮到暗
		{
			for(i=0;i<20;i++)			//计次延时
			{
				LED=0;					//LED亮
				Delay(Time);			//延时Time
				LED=1;					//LED灭
				Delay(100-Time);		//延时100-Time
			}
		}
	}
}
