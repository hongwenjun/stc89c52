// 查询法使用定时器
#include <reg52.h>

typedef unsigned int u16;     //对数据类型进行声明定义
typedef unsigned char u8;

void Timer0Init(void)       //20毫秒@12.000MHz
{
    TMOD &= 0xFC;       //设置定时器模式
    TMOD |= 0x01;
    TH0 = 0xB1;     //设置定时 20ms
    TL0 = 0xF4;
    TF0 = 0;        //清除TF0标志
    TR0 = 1;        //定时器0开始计时
}


void wait20ms(u8 n)
{
    while (n) {
        if (1 == TF0) {
            n--;
            TH0 = 0xB1;     //设置定时 20ms
            TL0 = 0xF4;
            TF0 = 0;        //清除TF0标志
        }
    }
}

void main(void)
{
    u8 i;
    u8 led = 0x1;

    Timer0Init();

    while (1) {
        // D1 - D8  LED流水灯
        for (i = 0; i < 8; i++) {
            P2 = ~led;
            wait20ms(50);   // 等待 20ms × 50  = 1000ms
            led = led << 1;
        }
        led = 0x1;
    }
}
