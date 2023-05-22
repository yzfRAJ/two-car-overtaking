#ifndef __BSP_ADC_H
#define __BSP_ADC_H


#include "stm32f10x.h"
//
#define ADC_GPIO_APBxClock_FUN         RCC_APB2PeriphClockCmd
#define ADC_GPIO_CLK                   RCC_APB2Periph_GPIOA
#define ADC_PORT                       GPIOA
#define ADC_PIN                        GPIO_Pin_1
//
#define ADC_DMA_CLK                RCC_AHBPeriph_DMA1
#define ADC_CHANNEL                    ADC_Channel_1
//
//#define ADC_IRQ                        ADC1_2_IRQn
//#define ADC_IRQHandler                 ADC1_2_IRQHandler
//
#define ADC_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define ADC_x                          ADC1
#define ADC_CLK                        RCC_APB2Periph_ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1

void ADCx_Init(void);

#endif /*__BSP_ADC_H */


