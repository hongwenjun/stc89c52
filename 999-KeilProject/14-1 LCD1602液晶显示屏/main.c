#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
	LCD_Init();						//LCD初始化
	LCD_ShowChar(1,1,'A');			//在1行1列显示字符A
	LCD_ShowString(1,3,"Hello");	//在1行3列显示字符串Hello
	LCD_ShowNum(1,9,66,2);			//在1行9列显示数字66，长度为2
	LCD_ShowSignedNum(1,12,-88,2);	//在1行12列显示有符号数字-88，长度为2
	LCD_ShowHexNum(2,1,0xA5,2);		//在2行1列显示十六进制数字0xA5，长度为2
	LCD_ShowBinNum(2,4,0xA5,8);		//在2行4列显示二进制数字0xA5，长度为8
	LCD_ShowChar(2,13,0xDF);		//在2行13列显示编码为0xDF的字符
	LCD_ShowChar(2,14,'C');			//在2行14列显示字符C
	while(1)
	{
	}
}
