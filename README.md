# stc89c52  :+1: 我的征途是星辰大海！

## 基础实验例程更新 :gift: [Keil C51 编译源码](https://github.com/hongwenjun/stc89c52/tree/master/src) :smile: [SDCC 编译源码](https://github.com/hongwenjun/stc89c52/tree/master/src/sdcc)

- 开源项目网址  http://git.io/CB51    CodeBlocks 漂亮主题项目： https://git.io/codeblocks
- CodeBlocks + Keil_C51编译器 C51单片机学习 设置视频演示网址：  https://youtu.be/2YKXRX7Nckk   B站: https://www.bilibili.com/video/av62289305

### :100: [51单片机电路原理图_HC6800-ES_V2.0新版.pdf](https://github.com/hongwenjun/stc89c52/tree/master/Document)  :+1: [开发板其他器件芯片中文手册](https://github.com/hongwenjun/img/tree/master/c51)

---

## CodeBlocks配置使用Keil_C51编译器单片机编译设置方法

- Keil uVision4  C51编译器, 安装目录

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

### 3. 动态数码管显示 [源码](https://github.com/hongwenjun/stc89c52/tree/master/3-lcd_display)  :gift: [7段26字母 显示 Helloworld](https://github.com/hongwenjun/stc89c52/tree/master/src/str_7segment/)

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
