- 开源项目网址  http://git.io/CB51

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

```c
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
```
