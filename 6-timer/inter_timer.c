// 中断法使用定时器

#include <reg52.h>

void Timer0Init(void)       //20毫秒@12.000MHz
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
    if (cnt >= 1000) {    // 2ms × 1000  = 2秒触发一次
        cnt = 0;
        P2 = ~P2;

    }

}

void main(void)
{

    Timer0Init();

    while (1)
        ;
}
