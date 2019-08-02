// 音乐播放器 :  挥着翅膀的女孩  同一首歌  两只蝴蝶
#include <reg52.h>           //此文件中定义了单片机的一些特殊功能寄存器
#include "SoundPlay.h"
#include "music.h"

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;


u8 key_id = 0;

sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

sbit beep = P1 ^ 5;
u8 x = 200 ;

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
    InitialSound();
    while (1) {
        keypros();

        // K1 按键点歌   两只蝴蝶
        if (key_id == 1) {
            Play(Music_Two, 0, 3, 360);
            Delay1ms(500);

            key_id = 0;
        }

        // K2 按键点歌   挥着翅膀的女孩
        if (key_id == 2) {
            Play(Music_Girl, 0, 3, 360);
            Delay1ms(500);

            key_id = 0;
        }

        // K3 按键点歌   同一首歌
        if (key_id == 3) {
            Play(Music_Same, 0, 3, 360);
            Delay1ms(500);
            key_id = 0;
        }

        // K4  beep 声音
        if (key_id == 4) {
            while (x--) {
                beep = ~beep;
                delay(100);
            }
            key_id = 0;
            x = 200 ;
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
