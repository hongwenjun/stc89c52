#include <reg51.h>           //此文件中定义了单片机的一些特殊功能寄存器
#include <intrins.h>

#include <string.h>
#include <ctype.h>

#include "SoundPlay.h"
#include "music.h"

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

#define leds P2



sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

u8 key_id = 0;
u8 KeyValue = 0xFF;    //用来存放读取到的键值

#define GPIO_DIG P0
#define GPIO_KEY P1


// 蜂鸣器电路定义
sbit beep = P1 ^ 5;
u16 x = 200 ;

// 控制38译码器的Y0 电路定义a
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

u8 ledduan[] = {0xA3, 0x54, 0x4B, 0xFC, 0x48, 0xFC, 0x4B, 0x48};    // 汉字 洪 字模
u8 ledwei[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};     // 逐列点亮不改



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

// 扫描 矩阵键盘 S1-S16
void KeyDown(void);

void DigDisplay(char* str_7segment, u8 n);
void str2_7segment(char* s, u8 n);
void Hc595SendByte(u8 dat);

void test_matrix_key()
{
    LSA = LSB = LSC = 0;
    while (1) {
        KeyDown();         //按键判断函数
        GPIO_DIG = smgduan[KeyValue]; //

        if (KeyValue == 15) {
            KeyValue = 0xFF;
            return ;
        }

    }
}

void hello_digdisplay()
{

    char* ps;
    u8 n = 0;
    u16 X = 400;
    u8 cnt = 0;
    char str[] = "Hello World! 0123456789AbcdEFGHIJKLMnoPqrStUvWXYZ-=.";

    n = strlen(str);

    str2_7segment(str, n);

    cnt = n - 8;
    ps = str;

    while (1) {

        while (X--) {
            DigDisplay(ps, 8);   //数码管显示函数
        }
        if (cnt--)
            ps++;
        else {
            cnt = n - 8;
            ps = str;
        }

        X = 200;

        // 矩阵键 S16 长按退出测试
        KeyDown();
        if (KeyValue == 15) {
            KeyValue = 0xFF;
            return ;
        }
    }

}

void test_8x8_LED()
{
    u8 i;
    while (1) {
        P0 = 0x7f;
        for (i = 0; i < 8; i++) {
            P0 = ledwei[i];       //位选
            Hc595SendByte(ledduan[i]);  //发送段选数据
            delay(100);        //延时
            Hc595SendByte(0x00);  //消隐
        }

        // 矩阵键 S16 长按退出测试
        KeyDown();
        if (KeyValue == 15) {
            KeyValue = 0xFF;
            return ;
        }
    }
}

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

        // K2  Led 跑马灯  显示 Hello World
        if (key_id == 2) {
            leds = 0xfe; // led:  1111 1110
            delay(50000);

            for (i = 0; i < 7; i++) { //将led左移一位
                leds = leds << 1;
                delay(50000);
            }

            leds = 0x7F; // led:  1111 1110
            delay(50000);

            for (i = 0; i < 7; i++) { //将led右移一位
                leds = leds >> 1;
                delay(50000);
            }

            for (i = 0 ; i != 3 ; i++) {
                leds = 0x0; // led: 全亮
                delay(50000);
                leds = 0xff; // led: 全熄灭
                delay(50000);
            }
            key_id = 0;

            hello_digdisplay();
        }


        // K3 数码管  0-9 A-Z  计数显示  结束 beep 长声
        if (key_id == 3) {

            LSA = 0;
            LSB = 0;
            LSC = 0; //控制38译码器的Y0输出低电平

            // 数码管 0-9 A-Z 计数显示
            for (i = 0 ; i != 40 ; i++) {
                P0 = smgduan[i];
                delay(55000);
                P0 = smgduan[39];
                delay(55000);
            }

            // 状态复位
            LSA = LSB = LSC = 1 ;
            P0 = 0xff;

            // beep 长声
            x = 1000 ;
            while (x--) {
                beep = !beep;
                delay(100);
            }

            key_id = 0;

            test_8x8_LED();
        }

        // K4 调用 扫描矩阵键盘 S1-S16 测试程序 结束 beep 声音
        if (key_id == 4) {

            test_matrix_key();

            x = 200 ;
            while (x--) {
                beep = !beep;
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

// 扫描 矩阵键盘 S1-S16
void KeyDown(void)
{
    char a = 0;
    GPIO_KEY = 0x0f;
    if (GPIO_KEY != 0x0f) {             //读取按键是否按下
        delay(1000);                    //延时10ms进行消抖
        if (GPIO_KEY != 0x0f) {         //再次检测键盘是否按下
            //测试列
            GPIO_KEY = 0X0F;
            switch (GPIO_KEY) {
            case (0X07):
                KeyValue = 0;
                break;
            case (0X0b):
                KeyValue = 1;
                break;
            case (0X0d):
                KeyValue = 2;
                break;
            case (0X0e):
                KeyValue = 3;
                break;
            }
            //测试行
            GPIO_KEY = 0XF0;
            switch (GPIO_KEY) {
            case (0X70):
                KeyValue = KeyValue;
                break;
            case (0Xb0):
                KeyValue = KeyValue + 4;
                break;
            case (0Xd0):
                KeyValue = KeyValue + 8;
                break;
            case (0Xe0):
                KeyValue = KeyValue + 12;
                break;
            }
            while ((a < 50) && (GPIO_KEY != 0xf0)) { //检测按键松手检测
                delay(1000);
                a++;
            }
        }
    }
}

void DigDisplay(char* str_7segment, u8 n)
{
    u8 i;
    for (i = 0; i != n; i++) {
        switch (i) { //位选，选择点亮的数码管，
        case (7):
            LSA = 0;
            LSB = 0;
            LSC = 0;
            break;//显示第0位
        case (6):
            LSA = 1;
            LSB = 0;
            LSC = 0;
            break;//显示第1位
        case (5):
            LSA = 0;
            LSB = 1;
            LSC = 0;
            break;//显示第2位
        case (4):
            LSA = 1;
            LSB = 1;
            LSC = 0;
            break;//显示第3位
        case (3):
            LSA = 0;
            LSB = 0;
            LSC = 1;
            break;//显示第4位
        case (2):
            LSA = 1;
            LSB = 0;
            LSC = 1;
            break;//显示第5位
        case (1):
            LSA = 0;
            LSB = 1;
            LSC = 1;
            break;//显示第6位
        case (0):
            LSA = 1;
            LSB = 1;
            LSC = 1;
            break;//显示第7位
        }
        P0 = smgduan[*str_7segment]; //发送段码
        delay(100); //间隔一段时间扫描
        P0 = 0x00; //消隐
        str_7segment++;
    }
}

void str2_7segment(char* s, u8 n)
{
    u8 i;
    for (i = 0 ; i != n; ++i) {
        if (isdigit(*s))
            *s -= '0' ;

        if (*s > 0x1F  && *s < 0x40)
            *s = 39;   // 符号不显示  Null

        if (isupper(*s))
            *s = tolower(*s);
        if (islower(*s))
            *s = *s - 'a' + 10 ;
        s++;
    }
}

/*******************************************************************************
* 函数名         : Hc595SendByte(u8 dat)
* 函数功能         : 向74HC595发送一个字节的数据
    74595的控制端说明：
    SCK(11脚)：上升沿时数据寄存器的数据移位。QA-->QB-->QC-->...-->QH；下降沿移位寄存器数据不变。
    RCK(12脚)：上升沿时移位寄存器的数据进入数据存储寄存器，下降沿时存储寄存器数据不变。
               通常我将RCK置为低点平，当移位结束后，在RCK端产生一个正脉冲，更新显示数据。
*******************************************************************************/
void Hc595SendByte(u8 dat)
{
    u8 a;
    SRCLK = 0;
    RCLK = 0;
    for (a = 0; a < 8; a++) {
        SER = dat >> 7;  // 获取最高位  0xA3 :  1010 0011  等于 1
        dat <<= 1;      //  数据移位，移除最高位1补0  0100 0110

        SRCLK = 1;    // 上升沿时数据寄存器的数据移位
        _nop_();
        _nop_();      // 延时
        SRCLK = 0;    // 下降沿移位寄存器数据不变
    }

    RCLK = 1;   // 上升沿时移位寄存器的数据进入数据存储寄存器
    _nop_();
    _nop_();    // 延时
    RCLK = 0;   // 下降沿时存储寄存器数据不变
}
