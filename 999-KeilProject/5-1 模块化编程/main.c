#include <REGX52.H>
#include "Delay.h"	//包含Delay头文件
#include "Nixie.h"	//包含数码管头文件

void main()
{
	while(1)
	{
		Nixie(1,1);	//在数码管的第1位置显示1
		Nixie(2,2);	//在数码管的第2位置显示2
		Nixie(3,3);	//在数码管的第3位置显示3
		Nixie(4,4);	//在数码管的第4位置显示4
		Nixie(5,5);	//在数码管的第5位置显示5
		Nixie(6,6);	//在数码管的第6位置显示6
	}
}
