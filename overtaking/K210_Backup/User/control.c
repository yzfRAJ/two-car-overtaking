#include "stm32f10x.h"                  // Device header
#include "motor.h"
#include "sys.h"
#include "math.h"
#include "control.h"
#include "Trail.h"
#include "oled.h"
#include "encode.h"
#include "Key.h"
float  Position_KP=0,Position_KI=0,Position_KD=0;
extern u8 flag;
extern int ttt_roe;
int L_set=0,R_set=0;
//int last_roe;
extern int set_speed;
int speedL=0,speedR=0;
int MOTO1=0,MOTO2=0;// OUTPUT �ǿ��ƶ����PWM���ֵ; OUTPUT1 ��OUTPUT2 �ǿ���С���������ٶȵ�PWM���ֵ
int MOTOL=0,MOTOR=0;
float  Speed_Kp=0,Speed_Ki=0,Speed_Kd=0;//�ٶȻ�PID����
int PWM_out1=0;
int PID_sd=0;//С������PID��������PWM���ֵ

int PID_jc=0;//С�������ٶ�PID��������PWM���ֵ
int tim1 =0;
int tim2 =0;
int tim3 =0;
int time2=0;//0.3s
int time3=0;//0.51s
int time4=0;//0.09s
int flag_time=0;
extern int error;//����lk.c�����error�������ڱ��ļ���ʹ��error�ñ���  //��Ϊ���PID�������Ͳ���PID�������Ĵ�������ֵ

extern int a;//����lk.c�����a�������ڱ��ļ���ʹ��a�ñ���  //��Ϊ�����ٶ�PID�������Ĵ�������ֵ
float LPID_realize(float target_val,float actual_val);
float RPID_realize(float target_val,float actual_val);
uint8_t control_flag =0;
/********************************************************************************



*********************************************************************************/

//��ʱ��1�жϷ�����	 
//���Ŀ��ƺ���
//------------------------------------------------------------------------------------
void TIM1_UP_IRQHandler(void)
{ 
	
 	if( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET )		// �ж��Ƿ�ΪTIM1�ĸ����ж�
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update );  		// ���TIM1�����жϱ�־
		speedL= Read_EncoderL();
	  speedR= Read_EncoderR();
	  if(control_flag==0)
	  {
		tim1 ++;
        tim2 ++;
        tim3++;

		if(tim3==3)//��ʱ 0.09s
		{
			time4 ++;
			tim3=0  ;
		}


		if(tim2==10)//��ʱ 0.3s
		{
			time2 ++;
			tim2=0  ;
		}

      if(tim1==17)//��ʱ 0.51s
		{
		   time3 ++;
          flag_time++;
			tim1=0  ;
		}



		    PWM_out1=Position_PID (ttt_roe,0);	
			L_set=set_speed+PWM_out1;//250
			R_set=set_speed-PWM_out1;//250
			Xianfu_PWM1(300);
			MOTO1=LPID_realize(L_set,speedL);//����
			MOTO2=RPID_realize(R_set,speedR);//�ҵ��
			MOTOL =MOTO1;
			MOTOR =MOTO2;
			Xianfu_Pwm(1000);
			Set_Pwm(MOTOL,MOTOR);		 //���ص�����ϡ�
		}
	}
}











	/*********************
�ٶȻ�PI��Kp*Ek+Ki*Ek_S
*********************/


float LPID_realize(float target_val,float actual_val)
{
	
	static float err=0;          //ƫ��ֵ
	static float err_last=0;     //��һ��ƫ��ֵ
	static float Kp=17,Ki=1,Kd=0.8;     //���������֡�΢��ϵ��
	static float integral=0;     //����ֵ
	static float output_val=0;   //���ֵ
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	err = target_val - actual_val;
	
	/*������*/
	integral += err;

	/*PID�㷨ʵ��*/
	output_val = Kp * err + 
				       Ki * integral + 
				       Kd * (err - err_last);

	/*����*/
	err_last = err;

	/*���ص�ǰʵ��ֵ*/
	return output_val;
}


float RPID_realize(float target_val,float actual_val)
{
	
	static float err=0;          //ƫ��ֵ
	static float err_last=0;     //��һ��ƫ��ֵ
	static float Kp=14,Ki=0.6,Kd=0;     //���������֡�΢��ϵ��
	static float integral=0;     //����ֵ
	static float output_val=0;   //���ֵ
	
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	err = target_val - actual_val;
	
	/*������*/
	integral += err;

	/*PID�㷨ʵ��*/
	output_val = Kp * err + 
				      Ki* integral + 
				      Kd * (err - err_last);

	/*����*/
	err_last = err;

	/*���ص�ǰʵ��ֵ*/
	return output_val;
}





//------------------------------------------------------------------------------------------------------------------------------------------------------------
/**********************************************************************************************/
//------------------------------------------------------------------------------------------------------------------------------------------------------------
int Position_PID (int Encoder,int Target)   //����PID������//����Encoder=error��Target=0;
{ 	

	 static float Bias,Pwm=0,Integral_bias=0,Last_Bias=0;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=(Position_KP/10)*Bias+(Position_KI/10)*Integral_bias+(Position_KD/10)*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //����PWMֵ
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------
/*********************************************************************************************************/
//------------------------------------------------------------------------------------------------------------------------------------------------------------

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������ֵ
����  ֵ����
**************************************************************************/
void Xianfu_PWM1(int amplitude)
{	
    if(L_set<10) L_set=10;	
		if(L_set>amplitude)  L_set=amplitude;	
	  if(R_set<10) R_set=10;	
		if(R_set>amplitude)  R_set=amplitude;		
}
void Xianfu_Pwm(int amplitude)
{	
    if(MOTOL<0) MOTOL=0;	
		if(MOTOL>amplitude)  MOTOL=amplitude;	
	  if(MOTOR<0) MOTOR=0;	
		if(MOTOR>amplitude)  MOTOR=amplitude;		
}


void Set_Pwm(int Motor_X,int Motor_Y)//������ó���PWMֵ����
{

		     Motor_L(Motor_X);
	       Motor_R(Motor_Y);


}








