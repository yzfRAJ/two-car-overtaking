#include "stm32f10x.h"                  // Device header

/*
PWM ��� PA0  PA1
    Ƶ�� 72M/(PSC+1)/(ARR+1)=72M/72/1000
    ռ�ձ� CCR/(ARR+1)  ����1000

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


void Servo_PWM_Init(void)//�����PWM PA8
{
	
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;  //ʱ��� �ṹ�����
	GPIO_InitTypeDef GPIO_InitStruct;								//GPIO��ʼ�� �ṹ�����
	TIM_OCInitTypeDef TIM_OCInitStruct;							//ͨ����ʼ�� �ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //ʹ��TIM1��ʱ��ʱ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//ʹ��GPIOAʱ����
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;  //�����TIM1 ����PWM�������޹�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ�ʱģʽ
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;    //���㵽20000 ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;  //���Ƶ��72MHZ  ���ﶨ�� Ԥ��Ƶ72 PSC
																							 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);//��ʼ������ �øո����õĲ��� ���뵽��Ӧ�Ĵ�������
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //GPIO���ø����������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11; //TIM1ͬʱ������·PWM�� �ڹܽ�a11 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //GPIO�ٶ�50MHZ
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);  //��ʼ������ �øո����õĲ��� ���뵽��Ӧ�Ĵ�������
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; //PWM1ģʽ
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//������Ը�
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//�ò���/�ȽϼĴ���ʹ��
	TIM_OCInitStruct.TIM_Pulse = 0;  //��ʼ��ռ�ձ�0   ռ�ձȿ�������TIM_Period�������� ������Χ�ھͺ��� CCR
	
	TIM_OC4Init(TIM1,&TIM_OCInitStruct); //��ʼ������ �øո����õĲ��� ���뵽��Ӧ�Ĵ�������
	TIM_Cmd(TIM1,ENABLE);    //ʹ�ܶ�ʱ��TIM1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);  //ȷ����TIM1����PWM
	TIM_OC4PreloadConfig(TIM1,ENABLE);  //�ò���/�Ƚ�1�Ĵ��� Ԥװ�ع���ʹ�� ͬʱ����CC1ͨ��Ϊ���
	TIM_ARRPreloadConfig(TIM1,ENABLE);  //�Զ���װ��Ԥװ������

}

void PWM_SetCompare3(uint16_t Compare) //PA11  
{
	TIM_SetCompare4(TIM1,Compare);	
}
