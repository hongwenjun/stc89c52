// D1 - D16  LED流水灯  和 数码管流水灯

#include <reg51.h>           //此文件中定义了单片机的一些特殊功能寄存器
#include <INTRINS.H>
typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

sbit SRCLK = P3 ^ 6;
sbit RCLK = P3 ^ 5;   // 这个变量名 reg52.h 头文件有使用，所以使用 reg51.h
sbit SER = P3 ^ 4;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;  //控制38译码器的Y0输出低电平


void delay(u16 i)
{
    while (i--);
}


void Hc595SendByte(u8 dat)
{
    u8 a;
    SRCLK = 0;
    RCLK = 0;
    for (a = 0; a < 8; a++) {
        SER = dat >> 7;  // 获取最高位  0xA3 :  1010 0011  等于 1
        dat <<= 1;      //  数据移位，移除最高位1补0  0100 0110

        SRCLK = 1;    // 上升沿时数据寄存器的数据移位
        _nop_();
        _nop_();      // 延时
        SRCLK = 0;    // 下降沿移位寄存器数据不变
    }

    RCLK = 1;   // 上升沿时移位寄存器的数据进入数据存储寄存器
    _nop_();
    _nop_();    // 延时
    RCLK = 0;   // 下降沿时存储寄存器数据不变
}


void DigDisplay(u8 i, u8 c)
{
    switch (i) { //位选，选择点亮的数码管，
    case (0):
        LSA = 0;
        LSB = 0;
        LSC = 0;
        break;//显示第0位
    case (1):
        LSA = 1;
        LSB = 0;
        LSC = 0;
        break;//显示第1位
    case (2):
        LSA = 0;
        LSB = 1;
        LSC = 0;
        break;//显示第2位
    case (3):
        LSA = 1;
        LSB = 1;
        LSC = 0;
        break;//显示第3位
    case (4):
        LSA = 0;
        LSB = 0;
        LSC = 1;
        break;//显示第4位
    case (5):
        LSA = 1;
        LSB = 0;
        LSC = 1;
        break;//显示第5位
    case (6):
        LSA = 0;
        LSB = 1;
        LSC = 1;
        break;//显示第6位
    case (7):
        LSA = 1;
        LSB = 1;
        LSC = 1;
        break;//显示第7位
    }
    P0 = c;
}


void main()
{
    u8 i;
    u8 led = 0x1;
    while (1) {

        // D1 - D8  LED流水灯
        for (i = 0; i < 9; i++) {
            P2 = ~led;
            delay(55000);
            led = led << 1;
        }
        led = 0x1;

        // D9 - D16  LED流水灯
        P0 = 0x7f; // 8x8 LED
        for (i = 0; i < 9; i++) {
            Hc595SendByte(~led);
            delay(55000);        //延时
            led = led << 1;
        }
        led = 0x1;

        // 数码管  LED流水灯
        for (i = 0; i < 8; i++) {
            DigDisplay(i, 0x88);   // 从右到左依次显示 _.
            delay(55000);
        }

    }
}
