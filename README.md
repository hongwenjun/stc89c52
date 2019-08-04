# stc89c52  :+1: 我的征途是星辰大海！

## 基础实验例程 :gift: [源码 SDCC编译](https://github.com/hongwenjun/stc89c52/tree/master/src) :smile: [源码 Keil C51编译](https://github.com/hongwenjun/stc89c52/tree/master/4keil/)

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

### 3. 动态数码管显示 [源码](https://github.com/hongwenjun/stc89c52/tree/master/3-lcd_display)
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

### :100: HC6800-ES V2.0光盘资料(180515)
```
V2.0链接: 链接：https://pan.baidu.com/s/1nJyHVv4effJ5y5ffUJFMoQ
提取码：quux
```
### 百度盘下载很慢怎么办?  https://pandownload.com/
- 使用第三方客户端 手机扫描登陆，可以全速下载，我的20M网络，可以满速2.6M/s下载

### :+1: 普中51单片机开发版 stc89c52芯片实验板DIY套件

![](https://img.alicdn.com/imgextra/i2/222939413/TB2xOgJd67nBKNjSZLeXXbxCFXa_!!222939413.jpg)
