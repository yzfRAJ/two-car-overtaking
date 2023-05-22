#ifndef __CONTROL_H
#define __CONTROL_H


void EXTI9_5_IRQHandler(void);
void Xianfu_Pwm(int amplitude);
void Xianfu_PWM1(int amplitude);
void Set_Pwm(int Motor_X,int Motor_Y);
int Position_P (int Encoder,int Target);
int Position_PID (int Encoder,int Target);

#endif

