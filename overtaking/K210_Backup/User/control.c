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
int MOTO1=0,MOTO2=0;// OUTPUT 是控制舵机的PWM输出值; OUTPUT1 和OUTPUT2 是控制小车左右轮速度的PWM输出值
int MOTOL=0,MOTOR=0;
float  Speed_Kp=0,Speed_Ki=0,Speed_Kd=0;//速度环PID参数
int PWM_out1=0;
int PID_sd=0;//小车差速PID控制器的PWM输出值

int PID_jc=0;//小车基础速度PID控制器的PWM输出值
int tim1 =0;
int tim2 =0;
int tim3 =0;
int time2=0;//0.3s
int time3=0;//0.51s
int time4=0;//0.09s
int flag_time=0;
extern int error;//引用lk.c定义的error，才能在本文件内使用error该变量  //作为舵机PID控制器和差速PID控制器的传参输入值

extern int a;//引用lk.c定义的a，才能在本文件内使用a该变量  //作为基础速度PID控制器的传参输入值
float LPID_realize(float target_val,float actual_val);
float RPID_realize(float target_val,float actual_val);
uint8_t control_flag =0;
/********************************************************************************



*********************************************************************************/

//定时器1中断服务函数	 
//核心控制函数
//------------------------------------------------------------------------------------
void TIM1_UP_IRQHandler(void)
{ 
	
 	if( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET )		// 判断是否为TIM1的更新中断
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update );  		// 清除TIM1更新中断标志
		speedL= Read_EncoderL();
	  speedR= Read_EncoderR();
	  if(control_flag==0)
	  {
		tim1 ++;
        tim2 ++;
        tim3++;

		if(tim3==3)//计时 0.09s
		{
			time4 ++;
			tim3=0  ;
		}


		if(tim2==10)//计时 0.3s
		{
			time2 ++;
			tim2=0  ;
		}

      if(tim1==17)//计时 0.51s
		{
		   time3 ++;
          flag_time++;
			tim1=0  ;
		}



		    PWM_out1=Position_PID (ttt_roe,0);	
			L_set=set_speed+PWM_out1;//250
			R_set=set_speed-PWM_out1;//250
			Xianfu_PWM1(300);
			MOTO1=LPID_realize(L_set,speedL);//左电机
			MOTO2=RPID_realize(R_set,speedR);//右电机
			MOTOL =MOTO1;
			MOTOR =MOTO2;
			Xianfu_Pwm(1000);
			Set_Pwm(MOTOL,MOTOR);		 //加载到电机上。
		}
	}
}











	/*********************
速度环PI：Kp*Ek+Ki*Ek_S
*********************/


float LPID_realize(float target_val,float actual_val)
{
	
	static float err=0;          //偏差值
	static float err_last=0;     //上一个偏差值
	static float Kp=17,Ki=1,Kd=0.8;     //比例、积分、微分系数
	static float integral=0;     //积分值
	static float output_val=0;   //输出值
	/*计算目标值与实际值的误差*/
	err = target_val - actual_val;
	
	/*积分项*/
	integral += err;

	/*PID算法实现*/
	output_val = Kp * err + 
				       Ki * integral + 
				       Kd * (err - err_last);

	/*误差传递*/
	err_last = err;

	/*返回当前实际值*/
	return output_val;
}


float RPID_realize(float target_val,float actual_val)
{
	
	static float err=0;          //偏差值
	static float err_last=0;     //上一个偏差值
	static float Kp=14,Ki=0.6,Kd=0;     //比例、积分、微分系数
	static float integral=0;     //积分值
	static float output_val=0;   //输出值
	
	/*计算目标值与实际值的误差*/
	err = target_val - actual_val;
	
	/*积分项*/
	integral += err;

	/*PID算法实现*/
	output_val = Kp * err + 
				      Ki* integral + 
				      Kd * (err - err_last);

	/*误差传递*/
	err_last = err;

	/*返回当前实际值*/
	return output_val;
}





//------------------------------------------------------------------------------------------------------------------------------------------------------------
/**********************************************************************************************/
//------------------------------------------------------------------------------------------------------------------------------------------------------------
int Position_PID (int Encoder,int Target)   //差速PID控制器//这里Encoder=error，Target=0;
{ 	

	 static float Bias,Pwm=0,Integral_bias=0,Last_Bias=0;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=(Position_KP/10)*Bias+(Position_KI/10)*Integral_bias+(Position_KD/10)*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //返回PWM值
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------
/*********************************************************************************************************/
//------------------------------------------------------------------------------------------------------------------------------------------------------------

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：幅值
返回  值：无
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


void Set_Pwm(int Motor_X,int Motor_Y)//将计算得出的PWM值载入
{

		     Motor_L(Motor_X);
	       Motor_R(Motor_Y);


}








