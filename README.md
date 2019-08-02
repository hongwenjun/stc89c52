# stc89c52  :+1: 我的征途是星辰大海！

## 基础实验例程 :gift: [大杂烩源码](https://github.com/hongwenjun/stc89c52/tree/master/src)

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
        if (key_id == 2) {
            Play(Music_Girl, 0, 3, 360);
            Delay1ms(500);

            key_id = 0;
        }

        // K3 按键点歌   同一首歌
        if (key_id == 3) {
            Play(Music_Same, 0, 3, 360);
            Delay1ms(500);
            key_id = 0;
        }

        // K4  beep 声音
        if (key_id == 4) {
            while (x--) {
                beep = ~beep;
                delay(100);
            }
            key_id = 0;
            x = 200 ;
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