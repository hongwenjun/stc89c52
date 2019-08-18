/*  # 初识LCD1602液晶模块
    LCD1602什么意思，LCD表示LiquidCrystal Display
    1602表示一行可以显示16个字符，一共有两行
*/

#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

#define LcdDB  P0
sbit  LcdRS = P2 ^ 6;
sbit  LcdRW = P2 ^ 5;
sbit  LcdEN = P2 ^ 7;

uchar code tabel1[] = "I love MCU";
uchar code tabel2[] = "I love ZheJiang";

uchar* str1 = tabel1;
uchar* str2 = tabel2;

void Lcd_Init();
void LcdWrDat(uchar dat);
void LcdWrCmd(uchar cmd);
void LcdBusy();
void Lcd_Show(uchar x, uchar y);

void main(void)
{
    Lcd_Init();       // 第一步：初始化  (单片机先跟1602打个招呼)

    Lcd_Show(2, 0);   // 第二步：确定显示位置  (单片机告诉1602在哪里显示)

    while (*str1 != '\0') {
        LcdWrDat(*str1++);   // 第三部：确定显示内容  (单片机告诉1602显示什么内容)
    }

    // 显示坐标 0 行首，1 第2行
    Lcd_Show(0, 1);
    while (*str2 != '\0') {
        LcdWrDat(*str2++);
    }

    while (1) {

    }

}

void Lcd_Init()
{
    LcdWrCmd(0x38);
    LcdWrCmd(0x0C);
    LcdWrCmd(0x06);
    LcdWrCmd(0x01);
}

void LcdWrDat(uchar dat)
{
    LcdBusy();
    LcdRS = 1;
    LcdRW = 0;
    LcdDB = dat;
    LcdEN = 1;
    LcdEN = 0;
}

void LcdWrCmd(uchar cmd)
{
    LcdBusy();
    LcdRS = 0;
    LcdRW = 0;
    LcdDB = cmd;
    LcdEN = 1;
    LcdEN = 0;
}

void LcdBusy()
{
    LcdDB = 0xFF;
    LcdRS = 0;
    LcdRW = 1;
    LcdEN = 1;
    while (LcdDB & 0x80);
    LcdEN = 0;
}

void Lcd_Show(uchar x, uchar y)
{
    uchar addr;
    if (0 == y) {
        addr = 0x00 + x;
    } else
        addr = 0x40 + x;
    LcdWrCmd(addr | 0x80);
}
