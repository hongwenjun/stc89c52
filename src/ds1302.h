#ifndef DS1302_H_INCLUDED
#define DS1302_H_INCLUDED

//---包含头文件---//
#include<reg52.h>
#include<intrins.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

//---定义ds1302使用的IO口---//
sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

//---定义全局函数---//
void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void Ds1302ReadTime();

//---加入全局变量--//
extern uchar TIME[7];	//加入全局变量

#endif
