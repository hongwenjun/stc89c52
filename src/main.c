#include <reg52.h>           //此文件中定义了单片机的一些特殊功能寄存器
#include <intrins.h>        //因为要用到左右移函数，所以加入这个头文件

#include "SoundPlay.h"
#include "music.h"

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

#define leds P2

u8 key_id = 0;

sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

// 蜂鸣器电路定义
sbit beep = P1 ^ 5;
u16 x = 200 ;

// 控制38译码器的Y0 电路定义a
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u8 code smgduan[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66,   // 0 1 2 3 4
    0x6d, 0x7d, 0x07, 0x7f, 0x6f,   // 5 6 7 8 9
    0x77, 0x7c, 0x39, 0x5e, 0x79,   // A B C D E
    0x71, 0x00                      // F        NULL
};



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

// 扫描 按键 K1-K4
void keypros();

void main()
{
    u8 i = 0;
    InitialSound();

    while (1) {
        keypros();

        // K1 按键点歌   两只蝴蝶
        if (key_id == 1) {
            Play(Music_Two, 0, 3, 360);
            Delay1ms(500);

            key_id = 0;
        }

        // K2  Led 跑马灯
        if (key_id == 2) {
            leds = 0xfe; // led:  1111 1110
            delay(50000);

            for (i = 0; i < 7; i++) { //将led左移一位
                leds = _crol_(leds, 1);
                delay(50000);
            }
            for (i = 0; i < 7; i++) { //将led右移一位
                leds = _cror_(leds, 1);
                delay(50000);
            }

            for (i = 0 ; i != 3 ; i++) {
                leds = 0x0; // led: 全亮
                delay(50000);
                leds = 0xff; // led: 全熄灭
                delay(50000);
            }
            key_id = 0;
        }


        // K3 数码管 0-F 计数显示  结束 beep 长声
        if (key_id == 3) {
            LSA = 0;
            LSB = 0;
            LSC = 0; //控制38译码器的Y0输出低电平

			// 数码管 0-F 计数显示
            for (i = 0 ; i != 17 ; i++) {
                P0 = smgduan[i];
                delay(55000);
                P0 = smgduan[16];
                delay(55000);
            }

            // 状态复位
			LSA = LSB = LSC = 1	;
			P0 = 0xff;

			// beep 长声
            x = 1000 ;
            while (x--) {
                beep = ~beep;
                delay(100);
            }

            key_id = 0;
        }

        // K4  beep 声音
        if (key_id == 4) {
            x = 200 ;
            while (x--) {
                beep = ~beep;
                delay(100);
            }
            key_id = 0;

        }
    }
}

// 扫描 按键 K1-K4
void keypros()
{
    if (k1 == 0) {       // 按键 K1 ;  key_id = 1
        delay(1000);
        if (k1 == 0) {
            key_id = 1;
        }
        while (!k1);
    }

    if (k2 == 0) {      // 按键 K2 ;  key_id = 2
        delay(1000);
        if (k2 == 0) {
            key_id = 2;
        }
        while (!k2);
    }

    if (k3 == 0) {
        delay(1000);
        if (k3 == 0) {
            key_id = 3;
        }
        while (!k3);
    }

    if (k4 == 0) {
        delay(1000);
        if (k4 == 0) {
            key_id = 4;
        }
        while (!k4);
    }
}
