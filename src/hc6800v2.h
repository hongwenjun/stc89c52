#ifndef HC6800V2_H_INCLUDED
#define HC6800V2_H_INCLUDED

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

#define GPIO_DIG P0
#define GPIO_KEY P1

#define leds P2

// 蜂鸣器电路定义
sbit beep = P1 ^ 5;

// 控制38译码器的Y0 电路定义
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u8 code smgduan[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,  // 0 1 2 3 4 5 6 7 8 9
    0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3D, 0x76, 0x8F, 0x0E,  // A b c d E F G H I J
    0x75, 0x38, 0xB7, 0x54, 0x5C, 0x73, 0x67, 0x31, 0xC9, 0x78,  // K L M n o P q r S t
    0x3E, 0x1C, 0xFE, 0xE4, 0x6E, 0xDA, 0x40, 0x48, 0x80, 0x00   // U v W X Y Z - = . Null
};

sbit SRCLK = P3 ^ 6;
sbit RCLK = P3 ^ 5;   // 这个变量名 reg52.h 头文件有使用，所以使用 reg51.h
sbit SER = P3 ^ 4;


//    汉字 "洪" 字模
//    1 0 0 1 0 1 0 0
//    0 1 1 1 1 1 1 1
//    1 0 0 1 0 1 0 0
//    0 1 0 1 0 1 0 0
//    0 0 1 1 1 1 1 1
//    0 1 0 1 0 1 0 0
//    1 0 1 0 0 0 1 0
//    1 0 1 0 0 0 1 0
// 从左-->右，每一列取二进制换算16进制

u8 code ledduan[] = {0xA3, 0x54, 0x4B, 0xFC, 0x48, 0xFC, 0x4B, 0x48};    // 汉字 洪 字模
u8 code ledwei[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};     // 逐列点亮不改

///  函数申明  ///

// 扫描 按键 K1-K4
u8 keypros(u8 n);

// 扫描 矩阵键盘 S1-S16
u8 KeyDown(void);

void DigDisplay(char* str_7segment, u8 n);
void str2_7segment(char* s, u8 n);
void Hc595SendByte(u8 dat);


/// 基本函数  ///
void Delay1ms(unsigned int count)
{
    unsigned int i, j;
    for (i = 0; i < count; i++)
        for (j = 0; j < 120; j++);
}

void delay(u16 i)
{
    while (i--);
}

// beep 声音
void beep_ring(u16 x)
{
    while (x--) {
        beep = !beep;
        delay(100);
    }
}

#include "SoundPlay.h"
#include "music.h"

#endif // HC6800V2_H_INCLUDED
