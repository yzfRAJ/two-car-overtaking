/*
����ר��ģ�壬��ͨ��ģ��Ļ�����ɾ����MPU��ش���
����MPU6050_Exit��ش��루�ⲿ�����ж��ã�
�˳���ʹ��F103RCT6���ڴ�������Ʒ������ʹ��C8���л������ļ�
*/
#include <stm32f10x.h>
#include <math.h>
#include <stdint.h>
#include "sys.h"
#include "Delay.h"
#include "Timer.h"
#include "control.h"
#include "Motor.h"
#include "key.h"
#include "usart.h"
#include "GUI_control.h"
#include "OLED.h"
#include "PWM.h"
#include "encode.h"
#include "ADC.h"
#include "Find_flag.h"
//#include "mpu6050.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h" 

#define Start_MOD1  1
#define Start_MOD2  2
#define Start_MOD3  3
#define Over_MOD    4
#define End_MOD     5

extern uint32_t *p1,*p2,*p3;
extern uint32_t *i1,*i2,*i3;
extern uint32_t *d1,*d2,*d3;
extern uint32_t P1,P2,P3;
extern uint32_t I1,I2,I3;
extern	uint32_t D1,D2,D3;
extern int speedL;
extern int speedR;
u8 Start_flag=0;
int set_speed;
extern float  Speed_Kp,Speed_Ki,Speed_Kd;
extern int PWM_out1;
extern int MOTO2,MOTO1;
extern int MOTOL ,MOTOR;
extern int PWM_out1;
extern  float Position_KP,Position_KI,Position_KD;
extern u8 reo,flag;
int t_reo ,t_flag;
extern float LPID_realize;
extern float RPID_realize;
extern int L_set,R_set;
extern int ttt_roe;
extern uint8_t  topic_num;
extern  uint8_t RX1Flag;
extern  int  line_num;
extern  int time2;
extern  int time3;
extern  int time4;
extern int flag_time;
extern char RX1_Packet[];
extern uint8_t control_flag;
extern uint8_t Interrupt_flag;
uint8_t turn_flag=0;
uint8_t circle_num=1;
//************************MPU6050��ز���*************
// float Pitch,Roll,Yaw;						//�Ƕ�
// short gyrox,gyroy,gyroz;				//������--���ٶ�
// short aacx,aacy,aacz;	
//***************************************************
//////-----------------------------------------------------------
//////-----------------------------------------------------------
void Show_roe(void);
uint8_t Mod_Select(void);
uint8_t Step=0;
void enter_step(void);//���복��
void out_step(void);//������
void K210_turn(void);//K210����λ�ù̶�ת��
int main(void)
{ 

UART_Init(USART2,57600);
UART_Init(USART1,57600);
Motor_Init();//R PB 12 13   PA0 // L PB 14 15    PA1 
LEncoder_Init();
REncoder_Init();
Timer_Init();//��ʱ��1
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,DISABLE);
 control_flag=1;
Key_Init();
OLED_Init();
Find_line_init();//ʹ��Ѱ��־λ�ж�
//MPU_Init();					//��ʼ��MPU6050 PB10 PB11
//mpu_dmp_init(); 
	
//****************FLASH������س�ʼ����***********************	
//*************************************************************
p1=(uint32_t *)(0x08000000+1*1024*50);//��������Ʒÿҳ2KB
i1=(uint32_t *)(0x08000000+1*1024*51);
d1=(uint32_t *)(0x08000000+1*1024*52);
	
p2=(uint32_t *)(0x08000000+1*1024*53);//��������Ʒÿҳ2KB
i2=(uint32_t *)(0x08000000+1*1024*54);
d2=(uint32_t *)(0x08000000+1*1024*55);

p3=(uint32_t *)(0x08000000+1*1024*56);//��������Ʒÿҳ2KB
i3=(uint32_t *)(0x08000000+1*1024*57);
d3=(uint32_t *)(0x08000000+1*1024*58);

P1=*p1;
P2=*p2;
P3=*p3;
I1=*i1;
I2=*i2;
I3=*i3;
D1=*d1;
D2=*d2;
D3=*d3;


Position_KP=*p1;
Position_KI=*i1;
Position_KD=*d1;
//**************************************************************	


uint8_t Menu_page=1;
extern u16 ADC_convered[6];
 
  while(1)
 { 
	

	 if(Menu_page==1)//�����һҳ��PID��������ҳ
	{
		OLED_printf(40,1,"%s"," K210 ");
		OLED_printf(36,17,"%s","PID_SET");
		OLED_Refresh ();
		delay_ms(1000);
		OLED_Clear ();
   while (Menu_page==1)
     { 
	
		GUI_control_PID ();
		Show_roe();//��ʾƫ���;
        OLED_Refresh ();
			  if(KEY_Scan(1)==4)
					Menu_page=2;
			 
     }

	}		
	
	  else if (Menu_page==2)//����ڶ�ҳ����Ŀѡ��ҳ
	{
		 OLED_Clear ();
	  OLED_printf(20,17,"%s","Mode_Select");
	  OLED_Refresh ();
		delay_ms(1000);
    OLED_Clear ();
		 while (Menu_page==2)
		 {
			 topic_select();
			 	if(ttt_roe<0)
			{
			OLED_clearare(100,48,128,64);
			OLED_printf(100,48,"%d\n",ttt_roe);
			}
			else
			{											
				OLED_clearare(100,48,128,64);
				OLED_printf(100,48,"%.3d\n",ttt_roe);
			}
			OLED_ShowNum(70,48,flag,2,16,1);
			 OLED_Refresh ();
			 if(KEY_Scan(1)==4)
			 Menu_page=3;
		 }

   }		
	
	else if(Menu_page==3)//���뿪ʼ����ҳ
	{
		
		OLED_Clear ();
	  OLED_printf(20,17,"%s","Ready!");	
		delay_ms(500);
		OLED_Clear ();
/*******************************************************************************
		                       �����ƺ���
********************************************************************************/
	while (Menu_page==3)	//���غ�����ѭ��
	{
			
	
   if(topic_num==1)//���е�һ��,����һȦ
	 { 
        set_speed=120;
	    Position_KP=*p1;
        Position_KI=*i1;
        Position_KD=*d1;
        Go_Forward(100);//����
	    delay_ms(250);
	    Go_Forward(200);
        delay_ms(250);
        Go_Forward(300);
        delay_ms(250);
	    Go_Forward(400);
        delay_ms(250);

		//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	
		 control_flag=0;
		 while(topic_num==1)
		 {
			USART_printf(USART1 ,"%d,%d\n",speedL , speedR);//DEBUG_USARTxUSART1 
			USART_printf(USART1 ,"%d,%d\n",L_set , R_set);//DEBUG_USARTxUSART1 
		 Show_roe();//��ʾƫ���
	     OLED_Refresh ();
		
			
				time2 =0;
			if(line_num ==3&&turn_flag==0)
			{
				control_flag=1;
				Go_Forward(0);
				delay_ms(100);
				Go_Forward(400);
				delay_ms(400);
				Motor_L(300);
				Motor_R(500);
				delay_ms(1000);
				turn_flag=1;
				control_flag=0;
			}
			
			if(line_num >=4)
			{
				time2 =0;
				while(line_num >=5)
				{


					
					control_flag=1;
					Go_Forward (0);
	
					
					
					
				}
				
			}
		  

		}
//---------------------------1END---------------------------------------	 
	 }	
/**************************************************************
***************************************************************/	 
			if(topic_num==2)//���еڶ���
	 {
		OLED_Clear ();
		 while(strcmp (RX1_Packet,"OK2")!=0)
		 {
			 OLED_printf(0,0,"Loading");
			 printf ("@Start2\r\n");//��ӳ�����ָ��,��η���ȷ������
			 OLED_Refresh ();
   		     delay_ms (50);
		 }
		  	OLED_Clear ();
			set_speed=120;
			Position_KP=*p2;
			Position_KI=*i2;
			Position_KD=*d2;
            Go_Forward(100);//����
			delay_ms(250);
			Go_Forward(200);
			delay_ms(250);
			Go_Forward(300);
			delay_ms(250);
			Go_Forward(400);
			delay_ms(250);
		    control_flag=0   ;
		while(topic_num==2)//�ڶ���ѭ��
		{
			Show_roe();//��ʾƫ���
			OLED_Refresh ();				
		  if(Step==0&&time3>=2)//��ʱԽ������ߺ󣬿����ⲿ�ж�
		{
          Interrupt_flag=0;//�����ⲿ�жϼ���
		}	

		if(line_num==3&&Step==0)//��⵽������־��   ��һȦ ������
			{
				
				Interrupt_flag=1;//�ر��ж�Ѱ��
				control_flag=1;//�ر�PID����
				K210_turn();
				time2 =0;//��ʱ������
				time4 =0;
				control_flag=0;//����PID����
				while (Step==0)//Ѱһ�������ͣ��
				{
							
					if(time4>=17)//Լ1.5stime2>=6
					{

						if(Mod_Select()==Over_MOD)//���յ��ѳ���ָ��  ����
						{ 
						    control_flag=1;
							Go_Forward(100);//����
							delay_ms(250);
							Go_Forward(200);
							delay_ms(250);
							Go_Forward(300);
						    control_flag=0;
						    Step=1;
							time3=0;
							line_num=0;
						}
						else if (Mod_Select()!=Over_MOD)//δ���յ��ѳ���ָ�ԭ�صȴ�
						{
						    control_flag=1;
						    Go_Forward(0);

						}
					}
				}
			}
//******************************��ɵ�һ�γ���***************************************//
//************************************END********************************************//		
while(Step==1||Step==2)
{
			if(Step==1&&time3>=8)//��ʱԽ������ߺ󣬿����ⲿ�ж�    �ڶ�Ȧ ����
			{
				Interrupt_flag=0;//�����ⲿ�жϼ���
			}	

				if(line_num==3&&Step==1)//��⵽������־��
				{
					Interrupt_flag=1;//�ر��ⲿ����
					
					control_flag=1;//�ر�PID����
					K210_turn();
					control_flag=0;//��PID����
					time2=0;
					time4=0;
					while (Step==1)//Ѱһ�ἣ�󣬳���
					{

						if(time4>=7) //time2>=3Լ0.9s
						{
						control_flag=1;//�ر�PID����
						enter_step();//ִ��������
						control_flag=0;//��PID����
						Step=2;
						}
					}
				}
					else if(line_num==3&&Step==2)//��⵽������־��
                        {
							Interrupt_flag=1;//��ʱ�����ⲿ�жϼ���
				            time2=0;
							time4=0;
							while (Step==2)
							{
								if(time4>=7)//time2>=2
								{
								control_flag=1;//�ر�PID����
								out_step();//ִ�г������
								Go_Forward(0);
								delay_ms(100);
								Go_Forward(400);
								delay_ms(500);
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);
								control_flag=0;//��PID����
								Step=3;
								time3=0;
								line_num=0;
								}
							}
						}
}
//******************************��ɵڶ��γ���***************************************//
//************************************END********************************************//	
while(Step==3)
{							
		if(Step==3&&time3>=4)//��ʱԽ������ߺ󣬿����ⲿ�ж�   ����Ȧ ������
		{
          Interrupt_flag=0;//�����ⲿ�жϼ���
		}	

		if(line_num==3&&Step==3)//��⵽������־��
			{
				
				Interrupt_flag=1;//�ر��ж�Ѱ��
				control_flag=1;//�ر�PID����
				K210_turn();
				time2 =0;//��ʱ������
				time4 =0;
				control_flag=0;//����PID����
				while (Step==3)//Ѱһ�������ͣ��
				{
							
					if(time4>=17)//Լ1.2s  1.6s
					{

						if(Mod_Select()==Over_MOD)//���յ��ѳ���ָ��  ����
						{ 
						    control_flag=1;
						    control_flag=0;
						    Step=4;
							time3=0;
							line_num=0;

						}
						else if (Mod_Select()!=Over_MOD)//δ���յ��ѳ���ָ�ԭ�صȴ�
						{
						    control_flag=1;
						    Go_Forward(0);

						}
					}
				}
			}
}
//******************************��ɵ����γ���***************************************//
//************************************END********************************************//	
while(Step==4||Step==5)	
{
	if(Step==4&&time3>=8)//��ʱԽ������ߺ󣬿����ⲿ�ж�    ����Ȧ ����
			{
				Interrupt_flag=0;//�����ⲿ�жϼ���
			}	

				if(line_num==3&&Step==4)//��⵽������־��
				{
					Interrupt_flag=1;//�ر��ⲿ����
					time2=0;
					control_flag=1;//�ر�PID����
					K210_turn();
					control_flag=0;//��PID����
					while (Step==4)//Ѱһ�ἣ�󣬳���
					{

						if(time2>=3) //Լ1.8s
						{
						control_flag=1;//�ر�PID����
						enter_step();//ִ��������
						control_flag=0;//��PID����
						Step=5;
						}
					}
				}
					else if(line_num==3&&Step==5)//��⵽������־��
                        {
							Interrupt_flag=1;//��ʱ�����ⲿ�жϼ���
				            time2=0;
							while (Step==5)
							{
								if(time2>=2)
								{
								control_flag=1;//�ر�PID����
								out_step();//ִ�г������
								Go_Forward(0);
								delay_ms(100);
								Interrupt_flag=0;
								Go_Forward(400);
								delay_ms(500);
								Step=6;
								time3=0;
								line_num=0;
								control_flag=0;//��PID����
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);
								printf("@Cnd\r\n");
								delay_ms(10);								
								}
							}
						}
}
//******************************��ɵ��Ĵγ���***************************************//
//************************************END********************************************//		
while (Step==6)
{
	printf("yzfdasb");
   while(time3>=3)
	{
		printf("ccfnb");
	
        Interrupt_flag=1;//�ر��ⲿ�ж�
        control_flag=1;
		Go_Forward(0);
		while(1)
		{
         printf("@End\r\n");//����ָ��
		}


	}

}


//*********************************************************************************//				
			}			
		}						
//-----------------------2END-------------------------------//			
		}
		 
		 
		 
	 }
			
			
//---------------------------------end--------------------------------			
	}
} 
  


uint8_t Mod_Select(void)
{
if (RX1Flag==1)
{
	if (strcmp (RX1_Packet,"Start1")==0)
	{
		printf ("%s\n","OK1");
		
  	return Start_MOD1;	
	}
	
		else if (strcmp (RX1_Packet,"Start2")==0)
	{
		printf ("%s\n","OK2");
		
		return Start_MOD2;	
		
	}
	
		else if (strcmp (RX1_Packet,"Start3")==0)
	{
		printf ("%s\n","OK3");
		
		return Start_MOD3;	
		
	}
	
	else if (strcmp (RX1_Packet,"Cnd")==0)
	{
		printf ("%s\n","OK4");
		
		return Over_MOD ;
		
	}
	
	else if (strcmp (RX1_Packet,"End")==0)
	{
		printf ("%s\n","OK5");
		
		return End_MOD;
	}
	
	else
	{
		
		printf ("%s\n","ERROR");
	}
	RX1Flag=0;
}



}	






void Show_roe(void)
{

    if(ttt_roe<0)
	{
		OLED_clearare(100,48,128,64);
		OLED_printf(100,48,"%d\n",ttt_roe);
	}
	else
		{											
			OLED_clearare(100,48,128,64);
			OLED_printf(100,48,"%.3d\n",ttt_roe);
		}
			OLED_ShowNum(70,48,flag,2,16,1);




}

void enter_step(void)//���복��
{
    Go_Forward(0);//������
	delay_ms(100);                          
    Motor_R(700);
	Motor_L(100);
    delay_ms(450);
	Go_Forward(300);
	delay_ms(800);
	Go_Forward(0);
	delay_ms(100);
    Motor_R(100);
	Motor_L(700);
	delay_ms(500);
}

void out_step(void)//������
{
Go_Forward(0);//�������
delay_ms(100);                          
Motor_R(100);
Motor_L(700);
delay_ms(390);
Go_Forward(300);
delay_ms(700);
Go_Forward(0);
delay_ms(100);
Motor_R(700);
Motor_L(100);
delay_ms(550);
}

void K210_turn(void)
{
Go_Forward(0);
delay_ms(100);
Go_Forward(400);
delay_ms(400);
Motor_L(200);
Motor_R(500);
delay_ms(700);
Go_Forward(400);
delay_ms(400);
}
