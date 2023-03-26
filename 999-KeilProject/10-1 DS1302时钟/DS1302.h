#ifndef __DS1302_H__
#define __DS1302_H__

//外部可调用时间数组，索引0~6分别为年、月、日、时、分、秒、星期
extern unsigned char DS1302_Time[];

void DS1302_Init(void);
void DS1302_WriteByte(unsigned char Command,Data);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_SetTime(void);
void DS1302_ReadTime(void);

#endif
