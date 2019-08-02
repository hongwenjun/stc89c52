// LED闪烁实验 和 跑马灯

#include <reg52.h>           //此文件中定义了单片机的一些特殊功能寄存器
#include <intrins.h>        //因为要用到左右移函数，所以加入这个头文件

#define leds P2

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

sbit led = P2 ^ 0;   //将单片机的P2.0端口定义为led
sbit led3 = P2 ^ 2;
sbit led5 = P2 ^ 4;
sbit led7 = P2 ^ 6;


void delay(u16 i);
void wait(u8 i);
void led_work(u8 i);


int main()
{
    u8 i = 0;

    while (1) {

        for (i = 0; i != 5; i++) {
            led_work(i % 2);
            wait(1); //大约 s
        }


        leds = 0xfe; // led:  1111 1110
        wait(1); //大约 1s

        for (i = 0; i < 7; i++) { //将led左移一位
            leds = _crol_(leds, 1);
            delay(50000);
        }
        for (i = 0; i < 7; i++) { //将led右移一位
            leds = _cror_(leds, 1);
            delay(50000);
        }

    }

    return 0;
}


void delay(u16 i)
{
    while (i--);
}

void wait(u8 i)
{
    while (i--) {
        delay(50000); //大约延时450ms
        delay(5000); //大约延时45ms
        delay(50000); //大约延时450ms
        delay(5000); //大约延时45ms
    }
}

void led_work(u8 i)
{
    led = i;
    led3 = i;
    led5 = i;
    led7 = i;
}
