# stc89c52  :+1: 我的征途是星辰大海！

## 基础实验例程更新 :gift: [Keil C51 编译源码](https://github.com/hongwenjun/stc89c52/tree/master/src) :smile: [SDCC lib源码](https://github.com/hongwenjun/stc89c52/tree/master/sdcc/lib_src)

### CodeBlocks + Keil_C51编译器 C51单片机学习 设置视频演示
- 网址：  https://youtu.be/2YKXRX7Nckk   :smile:  B站: https://www.bilibili.com/video/av62289305
- 龙芯小本: [海创电子 51单片机基础 视频教程，使用Altium Designer10绘制Arduino单片机](http://srgb.vicp.net/2019/08/17/c51_pcb_vod/)

### 推荐新手2个讲的挺好的基础视频教程集合

- 海创电子 51单片机基础   https://space.bilibili.com/93630735/channel/detail?cid=76908

- 夏老师十天玩转单片机视屏教程-零基础教学  https://www.bilibili.com/video/av37406640

## 2023.03.26 我去年买了个表，一直走不准，现在终于可以设置时间了

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/digital_watch.webp)

### 相关链接：[74H芯片到底是什么](https://youtu.be/uETwQYJhoXs)  [1602A LCD的工作原理](https://youtu.be/GEKVSmihi3Y)  [数码管如何工作](https://youtu.be/UfhU9_y-CGM) 

### 电子表源码 [999-KeilProject](https://github.com/hongwenjun/stc89c52/tree/master/999-KeilProject)

### :100: [51单片机电路原理图_HC6800-ES_V2.0新版.pdf](https://github.com/hongwenjun/stc89c52/tree/master/Document)  :+1: [开发板其他器件芯片中文手册](https://github.com/hongwenjun/img/tree/master/c51)

---

## CodeBlocks配置使用Keil_C51编译器单片机编译设置方法

- [Keil uVision5  C51](https://www.keil.com/download/product/)编译器, 安装目录

	C:\Keil

- CodeBlocks编译器设置，选择 Keil C51 Compiler
```
编译器目录填	        C:\Keil\C51
搜索目录-编译器头文件   C:\Keil\C51\INC
搜索目录-编译器库文件   C:\Keil\C51\LIB
```
### 转换 HEX 工具配置
```
名称: Keil_C51编译_生成HEX
可执行程序:  OH51.EXE

$(TARGET_OUTPUT_DIR)$(TARGET_OUTPUT_BASENAME).omf
```

---

## CodeBlocks + [SDCC开源编译器](http://sdcc.sourceforge.net) C51单片机编译设置
:100: SDCC-小型设备C编译器,是一个可重新定位的优化标准C（ANSI C89，ISO C99，ISO C11）编译器套件，针对基于Intel MCS51的微处理器（8031,8032,8051,8052 等），
Maxim（以前的Dallas）DS80C390变体， Freescale（以前的摩托罗拉）基于HC08 （hc08，s08）， 基于Zilog Z80的MCU （z80，z180，gbz80，Rabbit 2000/3000，Rabbit 3000A，TLCS-90），Padauk（pdk14，pdk15）和 STMicroelectronics STM8。
正在开展支持 Padauk（pdk13），Microchip PIC16和PIC18 目标的工作。它可以重新定位到其他微处理器。

- SDCC-小型设备C编译器 下载网址: http://sdcc.sourceforge.net

- 推荐安装目录  C:\sdcc

- CodeBlocks编译器设置，选择 SDCC Compiler
```
编译器目录填	        C:\sdcc
搜索目录-编译器头文件   C:\sdcc\include
搜索目录-编译器库文件   C:\sdcc\lib

# CodeBlocks 新建项目，选 MCS51 Project，默认选择 SDCC Compiler，模版会自动添加 转换C51使用HEX文件 的命令
cmd /c "packihx <$(TARGET_OUTPUT_DIR)$(TARGET_OUTPUT_BASENAME).ihx >$(TARGET_OUTPUT_DIR)$(TARGET_OUTPUT_BASENAME).hex"

```

---

### 1. LED闪烁实验 和 跑马灯 [源码](https://github.com/hongwenjun/stc89c52/tree/master/1-led)

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/1-led.webp)

### 2. 使用蜂鸣器演奏音乐 [源码](https://github.com/hongwenjun/stc89c52/tree/master/2-beep_music)
```c
// 音乐播放器 :  挥着翅膀的女孩  同一首歌  两只蝴蝶
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
        // K3 按键点歌   同一首歌
        // K4  beep 声音
    }
}
```

### 3. 动态数码管显示 [源码](https://github.com/hongwenjun/stc89c52/tree/master/3-led_segment_displays)  :gift: [7段26字母 显示 Helloworld](https://github.com/hongwenjun/stc89c52/tree/master/src/str_7segment/)

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/hello_world.webp)

```c
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;  //控制38译码器的Y0输出低电平

u8 code smgduan[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66,   // 0 1 2 3 4
    0x6d, 0x7d, 0x07, 0x7f, 0x6f,   // 5 6 7 8 9
    0x77, 0x7c, 0x39, 0x5e, 0x79,   // A B C D E
    0x71, 0x00                      // F NULL
};
```

- 文件: * 7段数码管-26字母表.xls * 用来扩展自定义字母和符号

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/str-7segment.png)

### 4. 矩阵按键实验 [源码](https://github.com/hongwenjun/stc89c52/tree/master/4-matrix_key)
```c
void KeyDown(void)
{
  char a=0;
  GPIO_KEY=0x0f;
  if(GPIO_KEY!=0x0f)//读取按键是否按下
  {
    delay(1000);//延时10ms进行消抖
    if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
    {
      //测试列
      GPIO_KEY=0X0F;
      switch(GPIO_KEY)
      {
          case(0X07):	KeyValue=0;break;
          case(0X0b):	KeyValue=1;break;
          case(0X0d): KeyValue=2;break;
          case(0X0e):	KeyValue=3;break;
      }
      //测试行
      GPIO_KEY=0XF0;
      switch(GPIO_KEY)
      {
          case(0X70):	KeyValue=KeyValue;break;
          case(0Xb0):	KeyValue=KeyValue+4;break;
          case(0Xd0): KeyValue=KeyValue+8;break;
          case(0Xe0):	KeyValue=KeyValue+12;break;
      }
      while((a<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
      {
          delay(1000);
          a++;
      }
    }
  }
}

```

### 5. 8*8LED点阵-显示文字实验 [源码](https://github.com/hongwenjun/stc89c52/tree/master/5-matrix_8x8LED)

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/8x8led_hong.jpg)

```c
void Hc595SendByte(u8 dat)     // 函数向74HC595发送一个字节的数据
{
    u8 a;
    SRCLK = 0;
    RCLK = 0;
    for (a = 0; a < 8; a++) {
        SER = dat >> 7;  // 获取最高位  0xA3 :  1010 0011  等于 1
        dat <<= 1;      //  数据移位，移除最高位1补0  0100 0110

        SRCLK = 1;    // 升沿时数据寄存器的数据移位
        _nop_();
        _nop_();      // 延时
        SRCLK = 0;    // 下降沿移位寄存器数据不变
    }

    RCLK = 1;   // 上升沿时移位寄存器的数据进入数据存储寄存器
    _nop_();
    _nop_();    // 延时
    RCLK = 0;   // 下降沿时存储寄存器数据不变
}

```

### 6. 定时器和中断 [源码](https://github.com/hongwenjun/stc89c52/tree/master/6-timer)
```c
// 中断法使用定时器
void Timer0Init(void)       //2毫秒@12.000MHz
{
  EA = 1 ; // 使能总中断
  TMOD &= 0xFC;       //设置定时器模式
  TMOD |= 0x01;
  TH0 = (655536 - 2000) / 256;  //定时 2ms
  TL0 = (655536 - 2000) % 256;
  ET0 = 1;       //  打开定时器0
  TR0 = 1;        //定时器0开始计时
}

void inter_timer0() interrupt 1
{
  static unsigned int cnt;
  TH0 = (655536 - 2000) / 256;
  TL0 = (655536 - 2000) % 256;
  cnt++;
  if (cnt >= 1000) {   // 2ms × 1000  = 2秒触发一次
      cnt = 0;
      P2 = ~P2;

  }
}
```

### 7. 按键控制外部中断 [源码](https://github.com/hongwenjun/stc89c52/tree/master/7-external_interrupt)
```c
#include <reg51.h>
// K3 独立按键 触发外部中断 INT0
//External interrupt0 service routine //外部中断0服务程序
void exint0() interrupt 0           //(location at 0003H)
{
    P2++;      // LED组灯在 P2 I/O 端口
}

void main()
{
    IT0 = 1;    //set INT0 int type  //设置INT0 int类型(1:下降 0:低级别)
    EX0 = 1;    //enable INT0 interrupt  //启用INT0中断
    EA = 1;     //open global interrupt switch  //打开全局中断开关

    while (1);
}
```

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

---

### :100: HC6800-ES V2.0光盘资料(180515)
```
V2.0链接: 链接：https://pan.baidu.com/s/1nJyHVv4effJ5y5ffUJFMoQ
提取码：quux
```
### 百度盘下载很慢怎么办?  https://pandownload.com/
- 使用第三方客户端 手机扫描登陆，可以全速下载，我的20M网络，可以满速2.6M/s下载

### :+1: 普中51单片机开发版 stc89c52芯片实验板DIY套件

![](https://img.alicdn.com/imgextra/i2/222939413/TB2xOgJd67nBKNjSZLeXXbxCFXa_!!222939413.jpg)
