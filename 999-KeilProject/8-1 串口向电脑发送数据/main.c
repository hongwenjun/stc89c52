#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

unsigned char Sec;

void main()
{
	UART_Init();			//串口初始化
	while(1)
	{
		UART_SendByte(Sec);	//串口发送一个字节
		Sec++;				//Sec自增
		Delay(1000);		//延时1秒
	}
}
