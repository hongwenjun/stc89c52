/*******   外部中断0 和 中断1 实验  *******************

实现现象：下载程序后按下K3或k4 按键可以对D1小灯状态取反。
********************************************************/

#include "reg52.h"           //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

sbit k3 = P3 ^ 2; //定义按键K3
sbit k4 = P3 ^ 3; //定义按键K4
sbit led = P2 ^ 0; //定义P20口是led
#define LEDS P2    // P2 led灯组

void delay(u16 i)
{
    while (i--);
}

void Int0Init()
{
    //设置INT0
    IT0 = 1; //跳变沿出发方式（下降沿）
    EX0 = 1; //打开INT0的中断允许。

    //设置INT1
    IT1 = 1; //跳变沿出发方式（下降沿）
    EX1 = 1; //打开INT1的中断允许。

    EA = 1; //打开总中断
}

void main()
{
    Int0Init();  // 设置外部中断0和1
    while (1);
}

//外部中断0的中断函数
void Int0() interrupt 0
{
    delay(1000);     //延时消抖
    if (k3 == 0) {
        led = ~led;
    }
}

//外部中断1的中断函数
void Int1() interrupt 2
{
    delay(1000);     //延时消抖
    if (k4 == 0) {
        LEDS = ~(~LEDS << 1);
    }
}
