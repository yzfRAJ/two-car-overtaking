#ifndef __USART__H
#define __USART__H

#include "stm32f10x.h"                  // Device header
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "stdlib.h"

#define DEBUG_USARTx  USART1

void UART_Init( USART_TypeDef * pUSARTx, uint32_t bound);

void USART_printf( USART_TypeDef * pUSARTx,const char *format,...);//DEBUG_USARTxUSART1

void Usart_SendByte(USART_TypeDef *pUSARTx,u8 data);//发送一个字节

void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

void Usart_SendArray(USART_TypeDef *pUSARTx, u8 *array,u8 num);

int fputc(int ch, FILE *f);

int fgetc(FILE *f);
#endif
