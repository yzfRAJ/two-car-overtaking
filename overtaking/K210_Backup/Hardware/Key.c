#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "key.h"
#include "control.h"
extern int flag_time;
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_IPU;//上拉输入
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	// GPIO_Initstructure.GPIO_Mode= GPIO_Mode_IPU;//上拉输入
	// GPIO_Initstructure.GPIO_Pin=GPIO_Pin_4;
	// GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	// GPIO_Init(GPIOA,&GPIO_Initstructure);
	
}

u8 KEY_Scan(u8 mode)//按键扫描 1连按 0不支持连按
{
static u8 key_up=1;//按键按松开标志
if(mode)key_up=1; //支持连按 
if(key_up&&(KEY_ADD==0||KEY_SUB==0||KEY_MOD==0||KEY_OK ==0||KEY_X10==0))//上拉输入未按时高电平按下为低
{
delay_ms(50);//去抖动
key_up=0;
if(KEY_X10==0)   return KEY_x10; 
else if(KEY_ADD==0)return KEY_add;
else if(KEY_SUB==0)return KEY_sub;
else if(KEY_MOD==0)return KEY_mod; 
else if(KEY_OK==0)return KEY_ok; 

	
}
else if(KEY_OK==1&&KEY_SUB==1&&KEY_ADD==1&&KEY_MOD==1 )key_up=1;

return 0;// 无按键按下
}


// void Read_flag_Line(void)
// {
// 	static uint8_t line_flag =0;
	
// 	if(Read_line==1&&line_flag==0)//寻到黑线
// 	{
// 		line_flag=1;
	
// 	}
	
// 	else if (Read_line==0&&line_flag==1)//寻到过黑线，寻到白底视为一次黑线
// 	{
// 		line_flag=0;
// 		if(flag_time>=3)
// 		{
// 		  line_num++;
// 		}

// 			flag_time=0;
// 	}
	
	
// }

