#ifndef __KEY__H
#define __KEY__H
#include "stdint.h"
#include "sys.h"

#define KEY_X10 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//读取按键 0倍数切换
#define KEY_ADD GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//读取按键 1加
#define KEY_SUB GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//读取按键 2减
#define KEY_MOD GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//读取按键 3模式切换
#define KEY_OK  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//读取按键 4确认

#define Read_line  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//巡线用

#define KEY_add 1 //+
#define KEY_sub 2 //- 
#define KEY_mod 3 //mod
#define KEY_ok  4 //ok
#define KEY_x10 5// 切换倍数

void Key_Init(void);//按键初始化

u8 KEY_Scan(u8 mode);//按键扫描 1连按 0不支持连按
	
void Read_flag_Line(void);//寻标志线


#endif
