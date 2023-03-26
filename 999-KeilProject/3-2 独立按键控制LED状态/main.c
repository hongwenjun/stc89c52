#include <REGX52.H>

void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

void main()
{
	while(1)
	{
		if(P3_1==0)			//如果K1按键按下
		{
			Delay(20);		//延时消抖
			while(P3_1==0);	//松手检测
			Delay(20);		//延时消抖
			
			P2_0=~P2_0;		//LED1取反
		}
	}
}
