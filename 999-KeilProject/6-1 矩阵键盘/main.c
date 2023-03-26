#include <REGX52.H>
#include "Delay.h"		//包含Delay头文件
#include "LCD1602.h"	//包含LCD1602头文件
#include "MatrixKey.h"	//包含矩阵键盘头文件

unsigned char KeyNum;

void main()
{
	LCD_Init();							//LCD初始化
	LCD_ShowString(1,1,"MatrixKey:");	//LCD显示字符串
	while(1)
	{
		KeyNum=MatrixKey();				//获取矩阵键盘键码
		if(KeyNum)						//如果有按键按下
		{
			LCD_ShowNum(2,1,KeyNum,2);	//LCD显示键码
		}
	}
}
