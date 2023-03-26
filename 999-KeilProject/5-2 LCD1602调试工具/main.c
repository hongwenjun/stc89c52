#include <REGX52.H>
#include "LCD1602.h"	//包含LCD1602头文件
#include "Delay.h"		//包含Delay头文件

int Result=0;

void main()
{
	LCD_Init();
	while(1)
	{
		Result++;					//Result自增
		Delay(1000);				//延时1秒
		LCD_ShowNum(1,1,Result,3);	//在LCD的1行1列显示Result，长度为3位
	}
}
