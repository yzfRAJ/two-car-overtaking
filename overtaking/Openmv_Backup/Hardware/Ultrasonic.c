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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;  //PA6 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA6 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);	//PA6 下拉
		
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;  //PA7 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA7 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);	
		
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA7 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA7 输入  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);	
	
	//初始化定时器3 TIM3	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM3输入捕获参数
	  TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);	
	//初始化TIM3输入捕获参数
	  TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
		TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
		TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);
		 TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);
   	TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3
   


}
	


  u8  TIM3CH1_CAPTURE_STA;		//输入捕获状态		    				
 u16	TIM3CH1_CAPTURE_VAL;	//输入捕获值	
 u8  TIM3CH2_CAPTURE_STA;		//输入捕获状态		    				
 u16	TIM3CH2_CAPTURE_VAL;	//输入捕获值	
u8  TIM3CH3_CAPTURE_STA;		//输入捕获状态		    				
 u16	TIM3CH3_CAPTURE_VAL;	//输入捕获值	
//定时器3中断服务程序	 
   void TIM3_IRQHandler(void)
{ 

 	if((TIM3CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM3CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM3CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH1_CAPTURE_STA=0;			//清空
				TIM3CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位	
//-----------------------------------------------------------------------------------------------------------------	
//------------------------------------------------------------------------------------------------------------	
		if((TIM3CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM3CH2_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM3CH2_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM3CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH2_CAPTURE_VAL=0XFFFF;
				}else TIM3CH2_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
		{	
			if(TIM3CH2_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM3CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM3CH2_CAPTURE_VAL=TIM_GetCapture2(TIM3);
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH2_CAPTURE_STA=0;			//清空
				TIM3CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位	
//-----------------------------------------------------------------------------------------------------------------	
//-----------------------------------------------------------------------------------------------------------------	
		if((TIM3CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM3CH3_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM3CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH3_CAPTURE_VAL=0XFFFF;
				}else TIM3CH3_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
		{	
			if(TIM3CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM3CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3);
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH3_CAPTURE_STA=0;			//清空
				TIM3CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3|TIM_IT_Update); //清除中断标志位	
	
}

 
  u16  MUltra_long(void)//PC14,PA6
	{
		 TIM3_IRQHandler();
Delay_ms (2);		
		SR04=1;
		Delay_us(13);
		SR04=0;
		
		if(TIM3CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			time=TIM3CH1_CAPTURE_STA&0X3F;
			time*=65536;//溢出时间总和
			time+=TIM3CH1_CAPTURE_VAL;//得到总的高电平时间
			Distance=time*0.034/2;
			TIM3CH1_CAPTURE_STA=0;//开启下一次捕获
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
		
		if(TIM3CH2_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			time=TIM3CH2_CAPTURE_STA&0X3F;
			time*=65536;//溢出时间总和
			time+=TIM3CH2_CAPTURE_VAL;//得到总的高电平时间
			Distance=time*0.034/2;
			TIM3CH2_CAPTURE_STA=0;//开启下一次捕获
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
		
		if(TIM3CH3_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			time=TIM3CH3_CAPTURE_STA&0X3F;
			time*=65536;//溢出时间总和
			time+=TIM3CH3_CAPTURE_VAL;//得到总的高电平时间
			Distance=time*0.034/2;
			TIM3CH3_CAPTURE_STA=0;//开启下一次捕获
		}

     return Distance;

	}		
  







