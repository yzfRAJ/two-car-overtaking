#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "key.h"


void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_IPU;//��������
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	
	
}

u8 KEY_Scan(u8 mode)//����ɨ�� 1���� 0��֧������
{
static u8 key_up=1;//�������ɿ���־
if(mode)key_up=1; //֧������ 
if(key_up&&(KEY_ADD==0||KEY_SUB==0||KEY_MOD==0||KEY_OK ==0||KEY_X10==0))//��������δ��ʱ�ߵ�ƽ����Ϊ��
{
delay_ms(50);//ȥ����
key_up=0;
if(KEY_X10==0)   return KEY_x10; 
else if(KEY_ADD==0)return KEY_add;
else if(KEY_SUB==0)return KEY_sub;
else if(KEY_MOD==0)return KEY_mod; 
else if(KEY_OK==0)return KEY_ok; 

	
}
else if(KEY_OK==1&&KEY_SUB==1&&KEY_ADD==1&&KEY_MOD==1 )key_up=1;

return 0;// �ް�������
}


