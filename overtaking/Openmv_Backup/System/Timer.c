#include "stm32f10x.h"                  // Device header

void Timer_Init(void)//定时器1 定时中断
{
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	TIM_InternalClockConfig (TIM1);

  	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructure;
	TIM_TimeBaseInitstructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstructure.TIM_CounterMode=TIM_CounterMode_Up  ;
	TIM_TimeBaseInitstructure.TIM_Period=300-1;//arr
	TIM_TimeBaseInitstructure.TIM_Prescaler=7200-1;//psc  72M/(PSC+1)/（ARR+1）  T=1/f 30ms 
	TIM_TimeBaseInitstructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitstructure);

	TIM_ClearFlag (TIM1,TIM_FLAG_Update );
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 	 NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=TIM1_UP_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstructure);
	
	TIM_Cmd(TIM1,ENABLE);
	
}





	
	


