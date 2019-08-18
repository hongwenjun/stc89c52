- 开源项目网址  http://git.io/CB51

### 8. 初识LCD1602液晶模块 [源码](https://github.com/hongwenjun/stc89c52/tree/master/8-lcd1602_display)

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/lcd1602.jpg)

```c
#define LcdDB  P0       // D0-D7 为8位双向数据线，传输数据或命令
sbit  LcdRS = P2 ^ 6;   // RS 为寄存器选择，高电平时选择数据寄存器，低电平时选择指令寄存
sbit  LcdRW = P2 ^ 5;   // R/W 为读写信号线, 高电平时进行读操作，低电平时进行写操作
sbit  LcdEN = P2 ^ 7;   // E 为使能端，当高电平跳变成低电平时，液晶模块执行命令

void Lcd_Init();            // LCD1602初始化函数
void LcdWrDat(uchar dat);   // LCD1602写8bit数据函数
void LcdWrCmd(uchar cmd);   // LCD1602写入8bit命令函数
void LcdBusy();             // 检测忙信号，等待
void Lcd_Show(uchar x, uchar y); // 显示坐标: x为横坐标;  y为竖坐标 y=0; 第一行 y=1; 第二行

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

```