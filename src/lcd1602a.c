#include "lcd1602a.h"

void Lcd_Init()
{
    LcdWrCmd(0x38); // 写指令38H: 显示模式设置
    LcdWrCmd(0x0C); // 写指令0CH: 开显示，不显示光标
    LcdWrCmd(0x06); // 写指令06H: 光标移动设置
    LcdWrCmd(0x01); // 写指令01H: 显示清屏
                    // 写指令08H 显示关闭
}

void LcdWrDat(uchar dat)
{
    LcdBusy();   // 检测忙信号
    LcdRS = 1;   // 高电平时选择数据寄存器
    LcdRW = 0;   // 低电平时进行写操作
    LcdDB = dat; // 写数据
    LcdEN = 1;   // 电平下降沿，使能
    LcdEN = 0;
}

void LcdWrCmd(uchar cmd)
{
    LcdBusy();
    LcdRS = 0;  // 低电平时选择指令寄存
    LcdRW = 0;
    LcdDB = cmd; // 传输命令
    LcdEN = 1;
    LcdEN = 0;
}

void LcdBusy()
{
    uint cnt = 0;
    LcdDB = 0xFF;   // I/O 口重置
    LcdRS = 0;
    LcdRW = 1;      // 高电平时进行读操作
    LcdEN = 1;
    while (LcdDB & 0x80) { // 检测忙信号，等待
        if (cnt >= 1000)
            return ;
        cnt++;
    }
    LcdEN = 0;
}

// 显示坐标: x为横坐标;  y为竖坐标 y=0; 第一行 y=1; 第二行
void Lcd_Show(uchar x, uchar y)
{
    uchar addr;
    if (0 == y) {
        addr = 0x00 + x;
    } else
        addr = 0x40 + x;

    // 因为写入显示地址时要求最高位 D7恒定为高电平 1 所以实际写入的数据应该 + 80H
    LcdWrCmd(addr | 0x80);
}


//    uchar code tabel1[] = "I love MCU";
//    uchar code tabel2[] = "I love ZheJiang";
//
//    uchar* str1 = tabel1;
//    uchar* str2 = tabel2;


//    void main(void)
//    {
//        Lcd_Init();       // 第一步：初始化  (单片机先跟1602打个招呼)
//
//        Lcd_Show(2, 0);   // 第二步：确定显示位置  (单片机告诉1602在哪里显示)
//
//        while (*str1 != '\0') {
//            LcdWrDat(*str1++);   // 第三部：确定显示内容  (单片机告诉1602显示什么内容)
//        }
//
//        // 显示坐标 0 行首，1 第2行
//        Lcd_Show(0, 1);
//        while (*str2 != '\0') {
//            LcdWrDat(*str2++);
//        }
//
//        while (1) {
//
//        }
//
//    }
