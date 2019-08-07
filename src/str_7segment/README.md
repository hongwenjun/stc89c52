- 开源项目网址  http://git.io/CB51

### 3. 动态数码管显示 [源码](https://github.com/hongwenjun/stc89c52/tree/master/3-lcd_display)  :gift: [7段26字母 显示 Helloworld](https://github.com/hongwenjun/stc89c52/tree/master/src/str_7segment/)

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/hello_world.webp)

```c
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;  //控制38译码器的Y0输出低电平

u8 code smgduan[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,  // 0 1 2 3 4 5 6 7 8 9
    0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3D, 0x76, 0x8F, 0x0E,  // A b c d E F G H I J
    0x75, 0x38, 0xB7, 0x54, 0x5C, 0x73, 0x67, 0x31, 0xC9, 0x78,  // K L M n o P q r S t
    0x3E, 0x1C, 0xFE, 0xE4, 0x6E, 0xDA, 0x40, 0x48, 0x80, 0x00   // U v W X Y Z - = . Null
};

```

- 文件: * 7段数码管-26字母表.xls * 用来扩展自定义字母和符号

![](https://raw.githubusercontent.com/hongwenjun/stc89c52/master/img/str-7segment.png)


```c

/*******************************************************************************
* 函 数 名         : DigDisplay
* 函数功能         : 数码管动态扫描函数，循环扫描8个数码管显示
*******************************************************************************/
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

```
