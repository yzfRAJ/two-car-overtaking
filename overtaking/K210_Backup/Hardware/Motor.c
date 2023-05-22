#include "stm32f10x.h"                  // Device header
#include "PWM.h"
/*
电机驱动适配TB6612/L298N
PB 12 13  R  PA0
PB 14 15  L  PA1

*/
 void Motor_Init(void)
 {
	 
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //使能B端口时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOB
 	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	 
  PWM_Init();
	 
	 
 }
 
 void  RMotor_Setspeed(int16_t Speed)
 {
	 if(Speed>=0)
   {
		 
		 GPIO_SetBits (GPIOB,GPIO_Pin_13);
		 GPIO_ResetBits (GPIOB,GPIO_Pin_12);
		 PWM_SetCompare1(Speed);
	}
   else
	 {
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits (GPIOB,GPIO_Pin_12);
		PWM_SetCompare1(-Speed);
	 }
	 
 }
  
 void  LMotor_Setspeed(int16_t Speed)
 {
	 if(Speed>=0)
   {
		 
		 GPIO_SetBits (GPIOB,GPIO_Pin_14);
		 GPIO_ResetBits (GPIOB,GPIO_Pin_15);
		 PWM_SetCompare2(Speed);
	}
   else
	 {
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		 GPIO_SetBits (GPIOB,GPIO_Pin_15);
		 PWM_SetCompare2(-Speed);
	 }
	 
 }
 
 
 void Go_Forward(int16_t Speed)
 {
	 LMotor_Setspeed(Speed);
	 RMotor_Setspeed(Speed);
 }     
 
 void Back_Off(int16_t Speed)
 {
	 LMotor_Setspeed(-Speed);
	 RMotor_Setspeed(-Speed);
 }

 
 void Motor_R(int16_t Speed2)
 {
	 RMotor_Setspeed(Speed2); 
 }

 
  void Motor_L(int16_t Speed2)
 {
	 LMotor_Setspeed(Speed2); 
 }
