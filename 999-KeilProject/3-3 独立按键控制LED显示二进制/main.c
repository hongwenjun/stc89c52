#include <REGX52.H>

void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main()
{
	unsigned char LEDNum=0;
	while(1)
	{
		if(P3_1==0)			//如果K1按键按下
		{
			Delay(20);		//延时消抖
			while(P3_1==0);	//松手检测
			Delay(20);		//延时消抖
			
			LEDNum++;		//变量自增
			P2=~LEDNum;		//变量取反输出给LED
		}
	}
}
