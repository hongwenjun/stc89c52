/**************************************************************************************
*                     静态数码管显示实验                                                 *
实现现象：下载程序后数码管静态显示0。
注意事项：如果不想让点阵模块显示，可以将74HC595模块上的JP595短接片拔掉。
***************************************************************************************/

#include <reg52.h>           //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u8 code smgduan[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66,   // 0 1 2 3 4
    0x6d, 0x7d, 0x07, 0x7f, 0x6f,   // 5 6 7 8 9
    0x77, 0x7c, 0x39, 0x5e, 0x79,   // A B C D E
    0x71, 0x00                      // F NULL
};

void delay(u16 i);

void main()
{
	u8 i = 0;

    LSA = 0;
    LSB = 0;
    LSC = 0; //控制38译码器的Y0输出低电平

    while (1) {
        for (i = 0 ; i != 17 ; i++) {
            P0 = smgduan[i];
            delay(55000);
	        delay(55000);
			P0 = smgduan[16];
		   	delay(55000);
        }
    }
}

void delay(u16 i)
{
    while (i--);
}
