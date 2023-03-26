#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"

unsigned char Num;
unsigned char Address;
unsigned char Command;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"ADDR  CMD  NUM");
	LCD_ShowString(2,1,"00    00   000");
	
	IR_Init();
	
	while(1)
	{
		if(IR_GetDataFlag() || IR_GetRepeatFlag())	//如果收到数据帧或者收到连发帧
		{
			Address=IR_GetAddress();		//获取遥控器地址码
			Command=IR_GetCommand();		//获取遥控器命令码
			
			LCD_ShowHexNum(2,1,Address,2);	//显示遥控器地址码
			LCD_ShowHexNum(2,7,Command,2);	//显示遥控器命令码
			
			if(Command==IR_VOL_MINUS)		//如果遥控器VOL-按键按下
			{
				Num--;						//Num自减
			}
			if(Command==IR_VOL_ADD)			//如果遥控器VOL+按键按下
			{
				Num++;						//Num自增
			}
			
			LCD_ShowNum(2,12,Num,3);		//显示Num
		}
	}
}

