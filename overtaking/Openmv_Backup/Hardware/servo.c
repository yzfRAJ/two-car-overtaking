#include "stm32f10x.h"                  // Device header
#include "PWM.h"
void Servo_Init(void)
{


Servo_PWM_Init();


}

void Servo_SetAngle270(float Angle)//最大 270度
{
	
	PWM_SetCompare3(Angle/270*2000+500);
	
	
	
}


void Servo_SetAngle180(float Angle)//常用 最大180度
{
	
	PWM_SetCompare3(Angle/180*2000+500);
	
	
	
}


