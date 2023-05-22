#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "usart.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "stdlib.h"
#include "oled.h"
#define DEBUG_USARTx  USART1
 u8 reo=0,flag=0;
int tt_roe;
int ttt_roe;
int last_roe;
char RX1_Packet[256]; 
uint8_t RX1Flag=0;
void UART_Init( USART_TypeDef * pUSARTx, uint32_t bound)
{
	
	 //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 if(pUSARTx==USART1)
	 {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	
}
	
	
	else  if(pUSARTx==USART2)
	 {
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA.3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3  

  //Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//子优先级4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2
	
}
	
	
	
	else  if(pUSARTx==USART3)
	 {
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10
   
  //USART3_RX	  GPIOB.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11

  //Usart3 NVIC 配置
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//子优先级5
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口3
	
}
	
}


//************************************************************************************//
void USART_printf( USART_TypeDef * pUSARTx,const char *format,...)//自定义串口printf函数
{
    uint32_t length;
    va_list args;
    uint32_t i;
    char TxBuffer[128] = {0};

    va_start(args, format);
    length = vsnprintf((char*)TxBuffer, sizeof(TxBuffer), (char*)format, args);
    va_end(args);
    for(i = 0; i < length; i++)
		{
		USART_SendData( pUSARTx, TxBuffer[i]);
		while (USART_GetFlagStatus( pUSARTx, USART_FLAG_TXE) == RESET);	//等待发送完毕	
		}  
}

//******************************************************************//

void Usart_SendByte(USART_TypeDef *pUSARTx,u8 data)//发送一个字节
{
 USART_SendData(pUSARTx,  data);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE)==RESET);
		
	
}	
/*****************  发送一个16位数 ***********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	
	temp_h = (ch&0XFF00)>>8;/* 取出高八位 */
	
	temp_l = ch&0XFF;/* 取出低八位 */
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

  void Usart_SendArray(USART_TypeDef *pUSARTx, u8 *array,u8 num)
{
	u8 i;
	for(i=0;i<num;i++)
	{
	Usart_SendByte ( pUSARTx ,array[i]);
	}
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);		
}



/*****************************仅给串口1使用****************/
/*********************如需修改请在头文件中修改DEBUG_USARTx*************/



///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


void USART1_IRQHandler(void)
{
	
 
  static  uint8_t  Rxstate=0;
	static  uint8_t  pRxPacket=0;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)   //RXNE 标志位为1 表示可以接收数据
	{
	uint8_t	RX_Data1=USART_ReceiveData(USART1);
		if (Rxstate ==0)
		{
			if ( (RX_Data1=='@')&&(RX1Flag==0) )
			{
				Rxstate=1;
				pRxPacket=0;
			}
			
		}
		
		else if (Rxstate ==1)
		{
			if(RX_Data1=='\r')
			{
				Rxstate =2;
				
			}
			else 
			{
			RX1_Packet [pRxPacket]=RX_Data1;
			pRxPacket++;
			}
		}
		
		else if (Rxstate ==2)
		{
			if (RX_Data1=='\n')
			{
				Rxstate =0;
				RX1Flag=1;
				RX1_Packet [pRxPacket]='\0';
			}
			
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);  //清除RXNE标志位
	}
}




void USART2_IRQHandler(void)			 
{
		u8 com_data; 
		u8 i;
		
		static u8 RxCounter1=0;
		static u16 RxBuffer1[7]={0};
		static u8 RxState = 0;	
		static u8 RxFlag1 = 0;

		if( USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  	   //接收中断  
		{
			
			
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //清除中断标志
				com_data = USART_ReceiveData(USART2);
			
				if(RxState==0&&com_data==0x2C)  //0x2c帧头
				{
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12帧头
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=7||com_data == 0x5B)       //RxBuffer1接受满了,接收数据结束
					{
						RxState=3;
						RxFlag1=1;
	//						Cx=(RxBuffer1[RxCounter1-12]<<8)+(RxBuffer1[RxCounter1-11]);
	//						Cy=(RxBuffer1[RxCounter1-10]<<8)+(RxBuffer1[RxCounter1-9]);
	//						Cw=(RxBuffer1[RxCounter1-8]<<8)+(RxBuffer1[RxCounter1-7]);
						reo=(RxBuffer1[RxCounter1-6]<<8)+(RxBuffer1[RxCounter1-5]);
						flag=(RxBuffer1[RxCounter1-4]<<8)+(RxBuffer1[RxCounter1-3]);
					}
				}
		
				else if(RxState==3)		//检测是否接受到结束标志
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//关闭DTSABLE中断
									if(RxFlag1)
									{
										tt_roe=reo;
										ttt_roe=tt_roe-100;
						       if(ttt_roe <-90 || ttt_roe >90)//异常值处理
		                     {
			                     ttt_roe= last_roe;
			
		                      }
	                    	else 
		                     {
		                      	last_roe=ttt_roe;
			
		                       }
										if(ttt_roe<0)
										{
										OLED_clearare(64,10,100,30);
										OLED_printf(64,10,"%d\n",ttt_roe);
										}
										else
										{											
											OLED_clearare(64,10,100,30);
											OLED_printf(64,10,"%.3d\n",ttt_roe);
										}
										OLED_ShowNum(64,36,flag,2,8,1);
									
										//数据编辑处
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
						}
						else   //接收错误
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //将存放数据数组清零
									}
						}
				} 
	
				else   //接收异常
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据数组清零
						}
				}

		}
}



void USART3_IRQHandler(void)
{
	uint8_t RX_Data3;
  uint8_t Flag;

	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)   //RXNE 标志位为1 表示可以接收数据
	{
		RX_Data3=USART_ReceiveData(USART3);
		Flag=1;
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);  //清除RXNE标志位
	}
}














