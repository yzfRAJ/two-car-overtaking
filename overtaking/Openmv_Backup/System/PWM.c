#include "stm32f10x.h"                  // Device header

/*
PWM 输出 PA0  PA1
    频率 72M/(PSC+1)/(ARR+1)=72M/72/1000
    占空比 CCR/(ARR+1)  满幅1000

*/
void PWM_Init(void)
{

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_AF_PP;
  GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);

	TIM_InternalClockConfig (TIM2);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructure;
	TIM_TimeBaseInitstructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstructure.TIM_CounterMode=TIM_CounterMode_Up  ;
	TIM_TimeBaseInitstructure.TIM_Period=1000-1;//ARR
	TIM_TimeBaseInitstructure.TIM_Prescaler=72-1;//PSC
	TIM_TimeBaseInitstructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstructure);

	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;	//CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
//	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;	//CCR
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}	

void PWM_SetCompare1(uint16_t Compare) //PA0
{
	TIM_SetCompare1(TIM2,Compare);
	
}

void PWM_SetCompare2(uint16_t Compare) //PA1   
{
	TIM_SetCompare2(TIM2,Compare);
	
}


void Servo_PWM_Init(void)//舵机用PWM PA8
{
	
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;  //时间基 结构体变量
	GPIO_InitTypeDef GPIO_InitStruct;								//GPIO初始化 结构体变量
	TIM_OCInitTypeDef TIM_OCInitStruct;							//通道初始化 结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //使能TIM1定时器时钟线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能GPIOA时钟线
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;  //这里跟TIM1 产生PWM波功能无关
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //向上计时模式
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;    //计算到20000 ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;  //最高频率72MHZ  这里定义 预分频72 PSC
																							 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);//初始化函数 让刚刚配置的参数 输入到对应寄存器里面
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //GPIO采用复用推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11; //TIM1同时产生两路PWM波 在管脚a11 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //GPIO速度50MHZ
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);  //初始化函数 让刚刚配置的参数 输入到对应寄存器里面
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; //PWM1模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性高
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//让捕获/比较寄存器使能
	TIM_OCInitStruct.TIM_Pulse = 0;  //初始化占空比0   占空比可以依照TIM_Period进行配置 在它范围内就好了 CCR
	
	TIM_OC4Init(TIM1,&TIM_OCInitStruct); //初始化函数 让刚刚配置的参数 输入到对应寄存器里面
	TIM_Cmd(TIM1,ENABLE);    //使能定时器TIM1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);  //确定让TIM1输入PWM
	TIM_OC4PreloadConfig(TIM1,ENABLE);  //让捕获/比较1寄存器 预装载功能使能 同时配置CC1通道为输出
	TIM_ARRPreloadConfig(TIM1,ENABLE);  //自动重装载预装载允许

}

void PWM_SetCompare3(uint16_t Compare) //PA11  
{
	TIM_SetCompare4(TIM1,Compare);	
}
