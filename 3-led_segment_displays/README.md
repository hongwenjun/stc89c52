- 开源项目网址  http://git.io/CB51

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


