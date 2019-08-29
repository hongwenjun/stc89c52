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