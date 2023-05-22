#include "stm32f10x.h"                  // Device header
#include "motor.h"
#include "delay.h"
#include "oled.h"
u8 S_Trail_Input = 0 ;		// ����Ѱ��ģ��ķ���ֵ
extern int sensor[8];//����������main��������飬�����ڱ��ļ���ʹ��sensor[x]�ñ���
extern int Prestopconfig;//����������main�����Prestopconfig�������ڱ��ļ���ʹ��Prestopconfig�ñ���

int error=0;//С����λ��ƫ���� ���(error),λ��ƫ��Խ�����Խ��ƫ��ԽС�����ԽС

int a=0;//С�������ٶȵı�־������aԽСʱ�������ٶ�Խ��
int stopconfig=0; //����յ��ߵı�־����  //����⵽�յ���ʱ���ñ�������ֵ��ı�
int Prestopconfig=0;//����һ���������ŵ�lk.c�ļ�read_sensor������ʶ���յ��ߵ������
 extern u8 L_R;//0F 1L 2R
 extern u8 shuzi ;
int Flag =0;
int Flag1=0;
int Flag2=0;
int Flag3=0;
int Flag4=0;
int TFlag =0;
int Cross_Num=0;
int sensor[8]={0,0,0,0,0,0,0,0};
 void Trail_Init(void)
 { GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOB��ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù��ܵ�ʱ��
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_11|GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);//PA4,PA5,PA6,PA7�ܽŵĳ�ʼ��
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������ģʽ
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0,PB1,PB3,PB4,PB5�ܽŵĳ�ʼ��
	  
	
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//�ر�STM32f103c8t6��JTAGD���ܣ�ʹPB3��PB4������ͨ��IO�ܽ�//���뿪�����ù��ܵ�ʱ�Ӳ��ܹرոù���
 }
 
 void read_line(void)
{
	/*��λ�ô�����˳�����ҵĴ��������ص������ź����δ�������sensor[0��8]��*/
				sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);//����Ĵ�����
				sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
				sensor[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);
				sensor[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);//����Ĵ�����
				sensor[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
				sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
				sensor[6]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);//���ҵĴ�����
			  sensor[7]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);// ҩƷ��
//				sensor[8]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
}
/****************************************************************************************************************************
*****************************************************************************************************************************/
				

