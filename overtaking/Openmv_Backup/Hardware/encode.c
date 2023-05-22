#include "stm32f10x.h"                  // Device header
void LEncoder_Init(void)
{
  	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  	TIM_ICInitTypeDef TIM_ICInitStructure;  
  	GPIO_InitTypeDef GPIO_InitStructure;
	
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器3的时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PA端口时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  	
 	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置 PA6 PA7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA
  	
  	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
 	  TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//边沿计数模式 
  	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  //初始化定时器3
	
  	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3(TIM_ICPolarity_Rising或者TIM_ICPolarity_Falling效果相同，都是4倍频)
	
  	TIM_ICStructInit(&TIM_ICInitStructure); //把TIM_ICInitStruct 中的每一个参数按缺省值填入
  	TIM_ICInitStructure.TIM_ICFilter = 10;  //设置滤波器长度
  	TIM_ICInit(TIM3, &TIM_ICInitStructure);//根据 TIM_ICInitStruct 的参数初始化外设	TIMx
 
  	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
  	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//使能定时器中断
  	TIM_SetCounter(TIM3,0);
  	TIM_Cmd(TIM3, ENABLE); //使能定时器
}

float Read_EncoderL(void)
{
	int Encoder_TIM = 0;  
	float Speed = 0.0;  
	Encoder_TIM= (short)TIM3 -> CNT;   
	TIM3 -> CNT=0;
	return -Encoder_TIM;
}



void REncoder_Init(void)
{
  	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  	TIM_ICInitTypeDef TIM_ICInitStructure;  
  	GPIO_InitTypeDef GPIO_InitStructure;
	
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器3的时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  	
   	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置 PB6 PB7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  	
  	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
 	  TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//边沿计数模式 
  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  //初始化定时器4
	
  	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3(TIM_ICPolarity_Rising或者TIM_ICPolarity_Falling效果相同，都是4倍频)
	
  	TIM_ICStructInit(&TIM_ICInitStructure); //把TIM_ICInitStruct 中的每一个参数按缺省值填入
  	TIM_ICInitStructure.TIM_ICFilter = 10;  //设置滤波器长度
  	TIM_ICInit(TIM4, &TIM_ICInitStructure);//根据 TIM_ICInitStruct 的参数初始化外设	TIMx
 
  	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
  	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//使能定时器中断
  	TIM_SetCounter(TIM4,0);
  	TIM_Cmd(TIM4, ENABLE); //使能定时器
}

float Read_EncoderR(void)
{
	int Encoder_TIM = 0;  
	float Speed = 0.0;  
	Encoder_TIM= (short)TIM4 -> CNT;   
	TIM4 -> CNT=0;
	return -Encoder_TIM;
}

