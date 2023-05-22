#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

//void Ultrasonic_Init(void);
void TIM3_Cap_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
 u16  MUltra_long(void);
 u16  LUltra_long(void);
 u16  RUltra_long(void);
#endif
