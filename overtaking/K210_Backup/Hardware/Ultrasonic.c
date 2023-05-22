 #include "stm32f10x.h"                  // Device header
	#include "Delay.h"
	#include "sys.h"
	#define SR042 PCout(13)
	#define SR04 PCout(14)
	#define SR041 PCout(15)
int time = 0;
int Distance = 0;
TIM_ICInitTypeDef  TIM3_ICInitStructure;
  void TIM3_Cap_Init(u16 arr,u16 psc)
	{	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_Out_PP;
  GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
	
		
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;  //PA6 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA6 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);	//PA6 ����
		
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;  //PA7 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA7 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);	
		
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA7 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA7 ����  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);	
	
	//��ʼ����ʱ��3 TIM3	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM3���벶�����
	  TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);	
	//��ʼ��TIM3���벶�����
	  TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
		TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
		TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);
		 TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);
   	TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3
   


}
	


  u8  TIM3CH1_CAPTURE_STA;		//���벶��״̬		    				
 u16	TIM3CH1_CAPTURE_VAL;	//���벶��ֵ	
 u8  TIM3CH2_CAPTURE_STA;		//���벶��״̬		    				
 u16	TIM3CH2_CAPTURE_VAL;	//���벶��ֵ	
u8  TIM3CH3_CAPTURE_STA;		//���벶��״̬		    				
 u16	TIM3CH3_CAPTURE_VAL;	//���벶��ֵ	
//��ʱ��3�жϷ������	 
   void TIM3_IRQHandler(void)
{ 

 	if((TIM3CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM3CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM3CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH1_CAPTURE_STA=0;			//���
				TIM3CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ	
//-----------------------------------------------------------------------------------------------------------------	
//------------------------------------------------------------------------------------------------------------	
		if((TIM3CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM3CH2_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM3CH2_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM3CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH2_CAPTURE_VAL=0XFFFF;
				}else TIM3CH2_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//����1���������¼�
		{	
			if(TIM3CH2_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM3CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM3CH2_CAPTURE_VAL=TIM_GetCapture2(TIM3);
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH2_CAPTURE_STA=0;			//���
				TIM3CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ	
//-----------------------------------------------------------------------------------------------------------------	
//-----------------------------------------------------------------------------------------------------------------	
		if((TIM3CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM3CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM3CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH3_CAPTURE_VAL=0XFFFF;
				}else TIM3CH3_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//����1���������¼�
		{	
			if(TIM3CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM3CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3);
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH3_CAPTURE_STA=0;			//���
				TIM3CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3|TIM_IT_Update); //����жϱ�־λ	
	
}

 
  u16  MUltra_long(void)//PC14,PA6
	{
		 TIM3_IRQHandler();
Delay_ms (2);		
		SR04=1;
		Delay_us(13);
		SR04=0;
		
		if(TIM3CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			time=TIM3CH1_CAPTURE_STA&0X3F;
			time*=65536;//���ʱ���ܺ�
			time+=TIM3CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			Distance=time*0.034/2;
			TIM3CH1_CAPTURE_STA=0;//������һ�β���
		}

     return Distance;

	}		

	 u16  LUltra_long(void)//PC15,PA7
	{
		 TIM3_IRQHandler();
    Delay_ms (2);		
		SR041=1;
		Delay_us(13);
		SR041=0;
		
		if(TIM3CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			time=TIM3CH2_CAPTURE_STA&0X3F;
			time*=65536;//���ʱ���ܺ�
			time+=TIM3CH2_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			Distance=time*0.034/2;
			TIM3CH2_CAPTURE_STA=0;//������һ�β���
		}

     return Distance;

	}		

 u16  RUltra_long(void)//PC13,PB0
	{
		 TIM3_IRQHandler();
 Delay_ms (2);		
		SR042=1;
		Delay_us(13);
		SR042=0;
		
		if(TIM3CH3_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			time=TIM3CH3_CAPTURE_STA&0X3F;
			time*=65536;//���ʱ���ܺ�
			time+=TIM3CH3_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			Distance=time*0.034/2;
			TIM3CH3_CAPTURE_STA=0;//������һ�β���
		}

     return Distance;

	}		
  







