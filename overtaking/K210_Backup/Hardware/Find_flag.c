#include "stm32f10x.h"                  // Device header
#include "control.h"
int  line_num=0;
 extern int flag_time;
uint8_t Interrupt_flag=0;
void Find_line_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA4
	
	
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
 EXTI_InitTypeDef EXIT_Initstructure;
 EXIT_Initstructure.EXTI_Line=EXTI_Line4 ;
 EXIT_Initstructure.EXTI_LineCmd=ENABLE;
 EXIT_Initstructure.EXTI_Mode=EXTI_Mode_Interrupt;
 EXIT_Initstructure.EXTI_Trigger=EXTI_Trigger_Falling;//���ô�����ʽΪ�ش���
 EXTI_Init(&EXIT_Initstructure);
	
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����жϷ���
 NVIC_InitTypeDef NVIC_Initstructure;
 NVIC_Initstructure.NVIC_IRQChannel=EXTI4_IRQn;
 NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
 NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�Ϊ2
 NVIC_Initstructure.NVIC_IRQChannelSubPriority=2;//��Ӧ���ȼ�Ϊ2
 NVIC_Init(& NVIC_Initstructure);
	
}

 void EXTI4_IRQHandler(void)
{

	
		if(flag_time>=2 && Interrupt_flag==0 )
		{
		  line_num++;
		}

			flag_time=0;
	// line_num++;
	
	
 EXTI_ClearITPendingBit(EXTI_Line4);//����жϱ�־λ
}




