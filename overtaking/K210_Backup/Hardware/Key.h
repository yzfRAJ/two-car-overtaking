#ifndef __KEY__H
#define __KEY__H
#include "stdint.h"
#include "sys.h"

#define KEY_X10 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//��ȡ���� 0�����л�
#define KEY_ADD GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//��ȡ���� 1��
#define KEY_SUB GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//��ȡ���� 2��
#define KEY_MOD GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//��ȡ���� 3ģʽ�л�
#define KEY_OK  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//��ȡ���� 4ȷ��

#define Read_line  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//Ѳ����

#define KEY_add 1 //+
#define KEY_sub 2 //- 
#define KEY_mod 3 //mod
#define KEY_ok  4 //ok
#define KEY_x10 5// �л�����

void Key_Init(void);//������ʼ��

u8 KEY_Scan(u8 mode);//����ɨ�� 1���� 0��֧������
	
void Read_flag_Line(void);//Ѱ��־��


#endif
