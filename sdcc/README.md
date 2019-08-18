## :smile: [SDCC lib源码](https://github.com/hongwenjun/stc89c52/tree/master/sdcc/lib_src)

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

###  CodeBlocks 构建: 在 MCS51 中 (编译器: SDCC Compiler)
```
sdcc.exe -mmcs51 --model-medium --opt-code-size -IC:\sdcc\include  -IR:\t\src\sdcc -c main.c -o obj\Release\main.rel

sdcc.exe -LC:\sdcc\lib -o bin\Release\MCS51.ihx -mmcs51 --model-medium --opt-code-size --xram-size 8192 --iram-size 512 --code-size 65536 --out-fmt-ihx obj\Release\main.rel

输出文件为 bin\Release\MCS51.ihx，大小为 10.08 KB

cmd /c "packihx <bin\Release\MCS51.ihx >bin\Release\MCS51.hex"

packihx: read 146 lines, wrote 272: OK.
```

### Keil C51语法修改适合SDCC 编译器

```c
/**********  Keil  C51 的 语法要修改  ***********
sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

sbit SRCLK = P3 ^ 6;
sbit RCLK = P3 ^ 5;   // 这个变量名 reg52.h 头文件有使用，所以使用 reg51.h
sbit SER = P3 ^ 4;

// 蜂鸣器电路定义
sbit beep = P1 ^ 5;

// 控制38译码器的Y0 电路定义
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;
****************************************/

///  使用 CodeBlocks + SDCC 编译 51 单片程序，绑定单片机 I/O 端口，需要改写语法
///  数组 code 和 计时器 interrupt 关键字 需要改写成  __code  __interrupt
///  _nop_() 函数 要改下宏定义   #define _nop_() __asm nop __endasm

#define _nop_() __asm nop __endasm

#define LSA P2_2
#define LSB P2_3
#define LSC P2_4

#define GPIO_DIG P0
#define GPIO_KEY P1

#define leds P2

#define k1 P3_1
#define k2 P3_0
#define k3 P3_2
#define k4 P3_3

#define SRCLK P3_6
#define RCLK P3_5
#define SER P3_4

#define beep P1_5
```