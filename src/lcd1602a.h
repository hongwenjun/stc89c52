#ifndef LCD1602A_H_INCLUDED
#define LCD1602A_H_INCLUDED

/*  # 初识LCD1602液晶模块
    LCD1602什么意思，LCD表示LiquidCrystal Display
    1602表示一行可以显示16个字符，一共有两行
*/

#include <reg51.h>

#define uchar unsigned char
#define uint unsigned int

#define LcdDB  P0       // D0-D7 为8位双向数据线，传输数据或命令
sbit  LcdRS = P2 ^ 6;   // RS 为寄存器选择，高电平时选择数据寄存器，低电平时选择指令寄存
sbit  LcdRW = P2 ^ 5;   // R/W 为读写信号线, 高电平时进行读操作，低电平时进行写操作
sbit  LcdEN = P2 ^ 7;   // E 为使能端，当高电平跳变成低电平时，液晶模块执行命令

void Lcd_Init();            // LCD1602初始化函数
void LcdWrDat(uchar dat);   // LCD1602写8bit数据函数
void LcdWrCmd(uchar cmd);   // LCD1602写入8bit命令函数
void LcdBusy();             // 检测忙信号，等待
void Lcd_Show(uchar x, uchar y); // 显示坐标 0 行首，1 第2行


#endif // LCD1602A_H_INCLUDED
