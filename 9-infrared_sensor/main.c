// 红外通信实验
#include <reg52.h>           // 此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;     // 对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

sbit IRIN = P3 ^ 2;    // 红外传感器接口，使用INT0中断

u8 IrValue[6];
u8 Time;

u8 DisplayData[8];
u8 code smgduan[17] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,       // 0 1 2 3 4 5 6 7 显示码
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0X76  // 8 9 A b C d E F H
};

// 延时函数，i=1时，大约延时10us
void delay(u16 i)
{
  while (i--);
}

// 数码管显示函数
void DigDisplay()
{
  u8 i;
  for (i = 0; i < 6; i++) {
    switch (i) { // 位选，选择点亮的数码管，
      case (0):
        LSA = 0;
        LSB = 0;
        LSC = 0;
        break; // 显示第0位
      case (1):
        LSA = 1;
        LSB = 0;
        LSC = 0;
        break; // 显示第1位
      case (2):
        LSA = 0;
        LSB = 1;
        LSC = 0;
        break;
      case (3):
        LSA = 1;
        LSB = 1;
        LSC = 0;
        break;
      case (4):
        LSA = 0;
        LSB = 0;
        LSC = 1;
        break;
      case (5):
        LSA = 1;
        LSB = 0;
        LSC = 1;
        break;

    }
    P0 = DisplayData[5 - i]; // 发送数据
    delay(100); // 间隔一段时间扫描
    P0 = 0x00; // 消隐
  }
}

// 初始化红外线接收
void IrInit()
{
  IT0 = 1; // 下降沿触发
  EX0 = 1; // 打开中断0允许
  EA = 1;  // 打开总中断

  IRIN = 1; // 初始化端口
}

void main()
{
  IrInit();
  while (1) {
    DisplayData[0] = smgduan[IrValue[0] / 16];
    DisplayData[1] = smgduan[IrValue[0] % 16];
    DisplayData[2] = 0x40; // '-' 显示码

    DisplayData[3] = smgduan[IrValue[2] / 16];
    DisplayData[4] = smgduan[IrValue[2] % 16];
    DisplayData[5] = smgduan[16];

    DigDisplay();
  }
}

// 读取红外数值的中断函数
void ReadIr() interrupt 0
{
  u8 j, k;
  u16 err;
  Time = 0;
  delay(700); // 7ms
  if (IRIN == 0) { // 确认是否真的接收到正确的信号

    err = 1000;             // 1000*10us=10ms,超过说明接收到错误的信号

    /*当两个条件都为真时循环，如果有一个条件为假的时候跳出循环，免得程序出错的时侯，程序死在这里*/
    while ((IRIN == 0) && (err > 0)) { // 等待前面9ms的低电平过去
      delay(1);
      err--;
    }
    if (IRIN == 1) {    // 如果正确等到9ms低电平
      err = 500;
      while ((IRIN == 1) && (err > 0)) { // 等待4.5ms的起始高电平过去
        delay(1);
        err--;
      }
      for (k = 0; k < 4; k++) { // 共有4组数据
        for (j = 0; j < 8; j++) { // 接收一组数据

          err = 60;
          while ((IRIN == 0) && (err > 0)) { // 等待信号前面的560us低电平过去
            delay(1);
            err--;
          }
          err = 500;
          while ((IRIN == 1) && (err > 0)) { // 计算高电平的时间长度。
            delay(10);   // 0.1ms
            Time++;
            err--;
            if (Time > 30) {
              return;
            }
          }
          IrValue[k] >>= 1; // k表示第几组数据
          if (Time >= 8) {    // 如果高电平出现大于565us，那么是1
            IrValue[k] |= 0x80;
          }
          Time = 0;   // 用完时间要重新赋值
        }
      }
    }
    if (IrValue[2] != ~IrValue[3]) {
      return;
    }
  }
}

