#include "stm32f10x.h"                  // Device header
#include "motor.h"
#include "delay.h"
#include "oled.h"
u8 S_Trail_Input = 0 ;		// 三个寻迹模块的返回值
extern int sensor[8];//引用主函数main定义的数组，才能在本文件内使用sensor[x]该变量
extern int Prestopconfig;//引用主函数main定义的Prestopconfig，才能在本文件内使用Prestopconfig该变量

int error=0;//小车的位置偏移量 误差(error),位置偏移越大，误差越大，偏移越小，误差越小

int a=0;//小车基础速度的标志变量，a越小时，基础速度越大
int stopconfig=0; //检测终点线的标志变量  //当检测到终点线时，该变量的数值会改变
int Prestopconfig=0;//定义一个变量，放到lk.c文件read_sensor函数里识别终点线的语句中
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
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB的时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能的时钟
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO管脚模式配置为浮空输入，这样就能获取传感器传回来的数字信号(高低电平)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_11|GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);//PA4,PA5,PA6,PA7管脚的初始化
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入模式
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0,PB1,PB3,PB4,PB5管脚的初始化
	  
	
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭STM32f103c8t6的JTAGD功能，使PB3和PB4用作普通的IO管脚//必须开启复用功能的时钟才能关闭该功能
 }
 
 void read_line(void)
{
	/*将位置从最左按顺序到最右的传感器返回的数字信号依次存入数组sensor[0至8]里*/
				sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);//最左的传感器
				sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
				sensor[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);
				sensor[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);//中央的传感器
				sensor[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
				sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
				sensor[6]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);//最右的传感器
			  sensor[7]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);// 药品盒
//				sensor[8]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
}
/****************************************************************************************************************************
*****************************************************************************************************************************/
				

