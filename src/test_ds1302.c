/**************************************************************************************
*		              DS1302时钟实验												  *
实现现象：下载程序后，数码管显示时钟数据
注意事项：
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include"ds1302.h"

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


char num=0;
u8 DisplayData[8];
u8 code ds_smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void delay(u16 i);

/*******************************************************************************
* 函 数 名         : datapros()
* 函数功能		   : 时间读取处理转换函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void datapros()
{
   	Ds1302ReadTime();
	DisplayData[0] = ds_smgduan[TIME[2]/16];				//时
	DisplayData[1] = ds_smgduan[TIME[2]&0x0f];
	DisplayData[2] = 0x40;
	DisplayData[3] = ds_smgduan[TIME[1]/16];				//分
	DisplayData[4] = ds_smgduan[TIME[1]&0x0f];
	DisplayData[5] = 0x40;
	DisplayData[6] = ds_smgduan[TIME[0]/16];				//秒
	DisplayData[7] = ds_smgduan[TIME[0]&0x0f];
}


void calendar()
{
   	Ds1302ReadTime();
	DisplayData[0] = ds_smgduan[TIME[6]/16];				//年
	DisplayData[1] = ds_smgduan[TIME[6]&0x0f];
	DisplayData[2] = 0x40;
	DisplayData[3] = ds_smgduan[TIME[4]/16];				//月
	DisplayData[4] = ds_smgduan[TIME[4]&0x0f];
	DisplayData[5] = 0x40;
	DisplayData[6] = ds_smgduan[TIME[3]/16];				//日
	DisplayData[7] = ds_smgduan[TIME[3]&0x0f];
}


/*******************************************************************************
* 函数名         :DigDisplay()
* 函数功能		 :数码管显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位
		}
		P0=DisplayData[7-i];//发送数据
		delay(100); //间隔一段时间扫描
		P0=0x00;//消隐
	}
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void test_ds1302_main()
{
	Ds1302Init();
	while(1)
	{
		datapros();	 //数据处理函数
		DigDisplay();//数码管显示函数
	}
}

void test_ds1302_calendar()
{
	Ds1302Init();
	while(1)
	{
		calendar();	 //数据处理函数
		DigDisplay();//数码管显示函数
	}
}

