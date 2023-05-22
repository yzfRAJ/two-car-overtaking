#ifndef __PWM_H
#define __PWM_H
#include "stdint.h"

/*
PWM ��� PA0  PA1
    Ƶ�� 72M/(PSC+1)/(ARR+1)=72M/72/1000
    ռ�ձ� CCR/(ARR+1)  ����1000

*/


void PWM_Init(void);
void Servo_PWM_Init(void);//PA8
void PWM_SetCompare1(uint16_t Compare);//PA0
void PWM_SetCompare2(uint16_t Compare);//PA1
void PWM_SetCompare3(uint16_t Compare); //PA8   

#endif
