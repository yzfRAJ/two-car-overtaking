#ifndef __MOTOR_H
#define __MOTOR_H
#include "stdint.h"

/*
µÁª˙«˝∂Ø  ≈‰TB6612/L298N
PB 12 13  R
PB 14 15  L

*/

 void Motor_Init(void);
 void RMotor_Setspeed(int16_t Speed);
 void LMotor_Setspeed(int16_t Speed);
 void Back_Off(int16_t Speed);
 void Go_Forward(int16_t Speed);
 void Motor_R(int16_t Speed2);
 void Motor_L(int16_t Speed2);
 
 
 
 
#endif


