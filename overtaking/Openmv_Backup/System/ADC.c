#include "stm32f10x.h"                  // Device header
u16 ADC_convered[6]={0,0,0,0,0,0};
void ADC1_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1| RCC_APB2Periph_GPIOB, ENABLE );	//ʹ�� ADC1ͨ��ʱ��
	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//��ʼ������GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//��ʼ������GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
  DMA_InitTypeDef DMA_InitInstructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_DeInit(DMA1_Channel1);//��λ
	DMA_InitInstructure.DMA_PeripheralBaseAddr =(u32)(&(ADC1->DR));//��������Ļ�ַ��ȡadc���ݼĴ����ĵ�ַ
	DMA_InitInstructure.DMA_MemoryBaseAddr = (u32)ADC_convered;//��DMA�����ݴ�������
	DMA_InitInstructure.DMA_DIR = DMA_DIR_PeripheralSRC;//���赽DMA
	DMA_InitInstructure.DMA_BufferSize = 6;//6��ͨ��
	DMA_InitInstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//
	DMA_InitInstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitInstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitInstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitInstructure.DMA_Mode = DMA_Mode_Circular;//���ϵش��䣬�����ݾʹ���
	DMA_InitInstructure.DMA_Priority = DMA_Priority_High;//DMA���ȼ�
	DMA_InitInstructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitInstructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);//ʹ��DMA����
	
	
	
	
	
	ADC_InitTypeDef ADC_InitStructure; 
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڶ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 6;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
 
 
 
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2,1, ADC_SampleTime_239Cycles5 );	 
     //ADC1,ADC1ͨ��2,����ʱ��Ϊ239.5����
 		//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3,2, ADC_SampleTime_239Cycles5 );	 
      //ADC1,ADC1ͨ��3,����ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4,3, ADC_SampleTime_239Cycles5 );	 
      //ADC1,ADC1ͨ��4,����ʱ��Ϊ239.5����		
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5,4, ADC_SampleTime_239Cycles5 );	 
      //ADC1,ADC1ͨ��5,����ʱ��Ϊ239.5����		
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8,5, ADC_SampleTime_239Cycles5 );	 
      //ADC1,ADC1ͨ��8,����ʱ��Ϊ239.5����		
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9,6, ADC_SampleTime_239Cycles5 );	 
      //ADC1,ADC1ͨ��9,����ʱ��Ϊ239.5����	
    ADC_DMACmd(ADC1,ENABLE);	
    ADC_Cmd(ADC1,ENABLE);
 
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	//while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
 


	
	
	
	
}
