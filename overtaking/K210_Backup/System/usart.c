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
	
	 //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 if(pUSARTx==USART1)
	 {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
	
}
	
	
	else  if(pUSARTx==USART2)
	 {
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA.3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3  

  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//�����ȼ�4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2
	
}
	
	
	
	else  if(pUSARTx==USART3)
	 {
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10
   
  //USART3_RX	  GPIOB.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11

  //Usart3 NVIC ����
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//�����ȼ�5
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); //��ʼ������3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3
	
}
	
}


//************************************************************************************//
void USART_printf( USART_TypeDef * pUSARTx,const char *format,...)//�Զ��崮��printf����
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
		while (USART_GetFlagStatus( pUSARTx, USART_FLAG_TXE) == RESET);	//�ȴ��������	
		}  
}

//******************************************************************//

void Usart_SendByte(USART_TypeDef *pUSARTx,u8 data)//����һ���ֽ�
{
 USART_SendData(pUSARTx,  data);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE)==RESET);
		
	
}	
/*****************  ����һ��16λ�� ***********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	
	temp_h = (ch&0XFF00)>>8;/* ȡ���߰�λ */
	
	temp_l = ch&0XFF;/* ȡ���Ͱ�λ */
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
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



/*****************************��������1ʹ��****************/
/*********************�����޸�����ͷ�ļ����޸�DEBUG_USARTx*************/



///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


void USART1_IRQHandler(void)
{
	
 
  static  uint8_t  Rxstate=0;
	static  uint8_t  pRxPacket=0;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)   //RXNE ��־λΪ1 ��ʾ���Խ�������
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
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);  //���RXNE��־λ
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

		if( USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  	   //�����ж�  
		{
			
			
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //����жϱ�־
				com_data = USART_ReceiveData(USART2);
			
				if(RxState==0&&com_data==0x2C)  //0x2c֡ͷ
				{
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12֡ͷ
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=7||com_data == 0x5B)       //RxBuffer1��������,�������ݽ���
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
		
				else if(RxState==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//�ر�DTSABLE�ж�
									if(RxFlag1)
									{
										tt_roe=reo;
										ttt_roe=tt_roe-100;
						       if(ttt_roe <-90 || ttt_roe >90)//�쳣ֵ����
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
									
										//���ݱ༭��
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
						}
						else   //���մ���
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
						}
				} 
	
				else   //�����쳣
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
				}

		}
}



void USART3_IRQHandler(void)
{
	uint8_t RX_Data3;
  uint8_t Flag;

	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)   //RXNE ��־λΪ1 ��ʾ���Խ�������
	{
		RX_Data3=USART_ReceiveData(USART3);
		Flag=1;
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);  //���RXNE��־λ
	}
}














