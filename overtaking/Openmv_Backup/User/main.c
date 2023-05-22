/*
调车专用模板，在通用模板的基础上删除了MPU相关代码
保留MPU6050_Exit相关代码（外部触发中断用）
此程序使用F103RCT6属于大容量产品，如需使用C8需切换启动文件
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
extern  float  Position_KP,Position_KI,Position_KD;
extern u8 reo,flag;
extern int tt_flag;
extern int  ttt_roe;
extern float LPID_realize;
extern float RPID_realize;
extern int L_set,R_set;
extern uint8_t  topic_num;
extern  uint8_t RX1Flag;
extern char RX1_Packet[];
extern  int  line_num;
extern int time2;
extern int time3;
extern uint8_t control_flag;
extern uint8_t Interrupt_flag;
uint8_t slave_mod=0;
u8 temp1=1;
u8 start_over_flag=0;
//************************MPU6050相关参数*************
// float Pitch,Roll,Yaw;						//角度
// short gyrox,gyroy,gyroz;				//陀螺仪--角速度
// short aacx,aacy,aacz;	
//***************************************************
//////-----------------------------------------------------------
//////-----------------------------------------------------------

void  Mod_Select(void);
void Show_roe(void);//OLED显示角度
void enter_step(void);//进入车库
void out_step(void);//出车库
int main(void)
{ 

UART_Init(USART2,57600);
UART_Init(USART1,57600);
Motor_Init();//R PB 12 13   PA0 // L PB 14 15    PA1 
LEncoder_Init();
REncoder_Init();
Timer_Init();//定时器1
control_flag=1;
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,DISABLE);
Key_Init();
Find_line_init();

OLED_Init();
//MPU_Init();					//初始化MPU6050 PB10 PB11
//mpu_dmp_init(); 
//****************FLASH调参相关初始参数***********************	
//*************************************************************
p1=(uint32_t *)(0x08000000+1*1024*50);//大容量产品每页2KB
i1=(uint32_t *)(0x08000000+1*1024*51);
d1=(uint32_t *)(0x08000000+1*1024*52);
	
p2=(uint32_t *)(0x08000000+1*1024*53);//大容量产品每页2KB
i2=(uint32_t *)(0x08000000+1*1024*54);
d2=(uint32_t *)(0x08000000+1*1024*55);

p3=(uint32_t *)(0x08000000+1*1024*56);//大容量产品每页2KB
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
	 
	 
	 
	 
	if(Menu_page==1)//进入第一页，PID参数调整页
	{
		OLED_printf(40,1,"%s","OPENMV");
		OLED_printf(36,17,"%s","PID_SET");
		OLED_Refresh ();
		delay_ms(1000);
		OLED_Clear ();
   while (Menu_page==1)
     { 
	
		GUI_control_PID ();
		Show_roe();//显示偏差角
        OLED_Refresh ();
		if(KEY_Scan(1)==4)
		Menu_page=2;
			 
     }

	}		
	  else if (Menu_page==2)
	{
	  OLED_Clear ();
	  OLED_printf(20,17,"%s","Mode_Select");//进入第二页，题目选择页
	  OLED_Refresh ();
	  delay_ms(1000);
      OLED_Clear ();
		 while (Menu_page==2)
		 {
			 topic_select();
			 Show_roe();//显示偏差角
			 OLED_Refresh ();
			 if(KEY_Scan(1)==4)
			 Menu_page=3;
		 }

   }		
	else if(Menu_page==3)//进入开始运行页
	{
		
		OLED_Clear ();
	  OLED_printf(20,17,"%s","Ready!");
		delay_ms(500);
		OLED_Clear ();
/**************************************************************
                           主控制循环
**************************************************************/		
	while (Menu_page ==3) //主控制大循环
	{	
		 
		if(topic_num ==1)//运行第一题，第一部分（无主车通信部分）
		{
		Position_KP=*p1;
        Position_KI=*i1;
        Position_KD=*d1;	
		set_speed=120;
		Go_Forward(100);
	    delay_ms(250);
	    Go_Forward(200);
        delay_ms(250);
        Go_Forward(300);
        delay_ms(250);
	    Go_Forward(400);
        delay_ms(250);
		control_flag=0;
	while (topic_num==1)
	{
				
		Show_roe();//显示偏差角
	    OLED_Refresh ();
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
			   
	
            
	}
	 
 

/***********************************************************************
************************************************************************/
       
   else if(topic_num ==2)//运行第二部分（需主从通信）
		{

        
		
    while(topic_num ==2)
		{
			OLED_printf(0,17,"%s","Wait instruction!");
			OLED_Refresh ();
			Mod_Select();//接收主车信息
			
			if(slave_mod ==2)//运行题目二
			{ 
			Interrupt_flag=1;//初始屏蔽外部中断计数，屏蔽起点
			printf ("@OK2\r\n");
		    delay_ms(10);
			printf ("@OK2\r\n");
		    delay_ms(10);
			printf ("@OK2\r\n");
		    delay_ms(10);
			printf ("@OK2\r\n");
		    delay_ms(10);
			printf ("@OK2\r\n");
		    delay_ms(10);
			printf ("@OK2\r\n");
		    delay_ms(10);
			Position_KP=*p2;
            Position_KI=*i2;
            Position_KD=*d2;	
		    set_speed=120;
			Go_Forward(100);
			delay_ms(250);
			Go_Forward(200);
			delay_ms(250);
			Go_Forward(300);
			delay_ms(250);
			Go_Forward(400);
			delay_ms(2700);
			OLED_Clear ();
			control_flag=0;//打开PID运算
				
	while(slave_mod ==2)
	{				
		Show_roe();//显示偏差角
		OLED_Refresh ();
        if(start_over_flag==0&&time3>=2)//定时越过起点线后，开启外部中断
		{
          Interrupt_flag=0;//开启外部中断计数
		}
        
		if(line_num==3&&start_over_flag==0)//进入超车区，准备超车
		{
			Interrupt_flag=1;//暂时屏蔽外部中断计数
            time2=0;
			while (start_over_flag==0)//寻一会儿迹后执行入库程序
			{
				if(time2>=6) //约1.8s
				{
                control_flag=1;//关闭PID计算
				enter_step();//执行入库程序
                control_flag=0;//打开PID计算
                start_over_flag=1;
				}
			}
        }
		else if (line_num==3&&start_over_flag==1)
		{
			Interrupt_flag=1;//暂时屏蔽外部中断计数
			time2=0;
			while (start_over_flag==1)//寻一会儿迹后执行出库程序
			{
				if(time2>=3)//约0.9s
				{
				control_flag=1;//关闭PID计算
				out_step();//执行出库程序
				Go_Forward(0);
				delay_ms(100);
				Go_Forward(400);
                delay_ms(700);
				control_flag=0;//打开PID计算	
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
				start_over_flag=2;
				time3=0;
				line_num=0;
				
				}
			}
			
		}
	//************************完成一次超车******************************//			
    //***************************END***********************************//
while(start_over_flag==2)
{
   if(start_over_flag==2&&time3>=4)//定时越过起点线后，开启外部中断
	{
          Interrupt_flag=0;//开启外部中断计数
	}

	if(line_num==3&&start_over_flag==2)//进入超车区，准备停车
	{

        Interrupt_flag=1;//暂时屏蔽外部中断计数
		time2=0;
		while (start_over_flag==2)//寻一会儿迹后停车
		{       
			Mod_Select();
			if(time2>=10)//约2.7s
			{	Mod_Select();
				if(slave_mod==Over_MOD)//接收到已超车指令  启动
				{ 
				    Go_Forward(100);
					delay_ms(250);
					Go_Forward(200);
					delay_ms(250);
					start_over_flag=3;
                    time3=0;
					line_num=0;	
					control_flag=0;
				
				}
				else if (slave_mod!=Over_MOD)//未接收到已超车指令，原地等待
				{
					control_flag=1;
					Go_Forward(0);

				}
					
			}
		}
	}
}	
	//************************完成第二次超车******************************//			
    //***************************END***********************************//	
while(start_over_flag==3||start_over_flag==4)
{
     if(start_over_flag==3&&time3>=8)//定时越过起点线后，开启外部中断
	{
          Interrupt_flag = 0;//开启外部中断计数
				  time3=0;
	}       
	if(line_num==3&&start_over_flag==3)//进入超车区，准备超车
	{
			Interrupt_flag=1;//暂时屏蔽外部中断计数
            time2=0;
			while (start_over_flag==3)//寻一会儿迹后执行入库程序
			{
				if(time2>=6) //约1.8s
				{
                control_flag=1;//关闭PID计算
				enter_step();//执行入库程序
                control_flag=0;//打开PID计算
                start_over_flag=4;
				}
			}
    }
	else if (line_num==3&&start_over_flag==4)
	{
				Interrupt_flag=1;//暂时屏蔽外部中断计数
				time2=0;
				while (start_over_flag==4)//寻一会儿迹后执行出库程序
				{
					if(time2>=3)//约0.9s
					{
					control_flag=1;//关闭PID计算
					out_step();//执行出库程序
					Go_Forward(0);
					delay_ms(100);
					Go_Forward(400);
                    delay_ms(500);
					control_flag=0;//打开PID计算
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
					start_over_flag=5;
					time3=0;
					slave_mod=0;
					line_num=0;
					}
				}
			
	}
}
//************************完成第三次超车******************************//			
//***************************END***********************************//	
while(start_over_flag==5)
{
    if(start_over_flag==5&&time3>=4)//定时越过起点线后，开启外部中断
		{
          Interrupt_flag=0;//开启外部中断计数
		}

	if(line_num==3&&start_over_flag==5)//进入超车区，准备停车
	{

        Interrupt_flag=1;//暂时屏蔽外部中断计数
		time2=0;
		Mod_Select();
		while (start_over_flag==5)//寻一会儿迹后停车
		{
			Mod_Select();
			if(time2>=10)
			{	
				if(slave_mod==Over_MOD)//接收到已超车指令  启动
				{ 
				    control_flag=1;
					control_flag=0;
					start_over_flag=6;
                    time3=0;
					line_num=0;
					slave_mod=0;
					Interrupt_flag=0;//开启外部中断
				}
				else if (slave_mod!=Over_MOD)//未接收到已超车指令，原地等待
				{
					control_flag=1;
					Go_Forward(0);

				}
					
			}
		}
	}
}	
//************************完成第四次超车******************************//			
//***************************END***********************************//	
while (start_over_flag==6)
{
	Mod_Select();
	 if(slave_mod==End_MOD)
	{
       control_flag=1;
       Go_Forward(0);
	}

}

	//**********************************题目二循环END***********************************//				
    }
			}
/**********************************************************************
************************************************************************/				
				else if(slave_mod ==3)//运行题目三
				{
                OLED_Clear();
				Position_KP=*p3;
                Position_KI=*i3;
                Position_KD=*d3;	
		        set_speed=140;
				Go_Forward(100);
				delay_ms(250);
				Go_Forward(200);
				delay_ms(250);
				Go_Forward(300);
				delay_ms(250);
				Go_Forward(400);
				delay_ms(250);
				OLED_Clear ();
				control_flag=0;//打开PID运算
				
	while(slave_mod ==3)
	{
		Show_roe();//显示偏差角
	    OLED_Refresh ();
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
					
				}

				
			}			
//----------------------------------part2_end--------------------------			
		}


		}
 
//------------------------------------end-------------------------------- 
   } 
	 
	 
	 }


 }

/********************************************************
                         双车通信
**********************************************************/
void  Mod_Select(void)
{
		
if (RX1Flag==1)
{
	if (strcmp (RX1_Packet,"Start1")==0)
	{
		printf ("%s\n","OK1");
		
  	slave_mod =   Start_MOD1;	
	}
	
		else if (strcmp (RX1_Packet,"Start2")==0)
	{
		printf ("@OK2\r\n");
		delay_ms(20);
		printf ("@OK2\r\n");
		delay_ms(20);
		printf ("@OK2\r\n");
		delay_ms(20);
		printf ("@OK2\r\n");
		delay_ms(20);
		printf ("@OK2\r\n");
		delay_ms(20);
		printf ("@OK2\r\n");
		delay_ms(20);
		slave_mod =  Start_MOD2;	
		
	}
	
		else if (strcmp (RX1_Packet,"Start3")==0)
	{
		printf ("%s\n","OK3");
		
		slave_mod =  Start_MOD3;	
		
	}
	
	else if (strcmp (RX1_Packet,"Cnd")==0)
	{
		printf ("%s\n","OK4");
		
		slave_mod =  Over_MOD ;
		
	}
	
	else if (strcmp (RX1_Packet,"End")==0)
	{
		printf ("%s\n","OK5");
		
		slave_mod =End_MOD;
	}
	
	else
	{
		
		printf ("%s\n","ERROR");
		slave_mod = 0;
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


void enter_step(void)//进入车库
{
    Go_Forward(0);//入库程序
	delay_ms(100);                          
    Motor_R(700);
	Motor_L(100);
    delay_ms(650);
	Go_Forward(300);
	delay_ms(400);
	Go_Forward(0);
	delay_ms(100);
    Motor_R(100);
	Motor_L(700);
	delay_ms(650);
}

void out_step(void)//出车库
{
Go_Forward(0);//出库程序
delay_ms(100);                          
Motor_R(100);
Motor_L(700);
delay_ms(450);
Go_Forward(300);
delay_ms(650);
Go_Forward(0);
delay_ms(100);
Motor_R(700);
Motor_L(100);
delay_ms(650);
}

