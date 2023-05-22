#include "bsp_adc.h"
__IO u16 ADC_ConvertedValue;


static void  ADCx_GPIO_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}
 static void ADCx_Mode_Config(void)
 {
	 DMA_InitTypeDef DMA_InitStructure;
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC_x->DR ) );
	
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������СΪ1���������Ĵ�СӦ�õ��ڴ洢���Ĵ�С
	DMA_InitStructure.DMA_BufferSize = 1;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	 
  ADC_InitTypeDef ADC_InitStruct;
	 
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	ADC_InitStruct.ADC_Mode =ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode =DISABLE ;
	ADC_InitStruct.ADC_ContinuousConvMode =ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel=1;
	 
	ADC_Init(ADC_x, &ADC_InitStruct);

	 RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	 ADC_RegularChannelConfig(ADC_x,ADC_CHANNEL,1, ADC_SampleTime_55Cycles5);
	 
//	 ADC_ITConfig(ADC_x, ADC_IT_EOC, ENABLE);
// ʹ��ADC DMA ����
	ADC_DMACmd(ADC_x, ENABLE);
	 ADC_Cmd(ADC_x,ENABLE);
	 
	 ADC_StartCalibration (ADC_x);
	 while(ADC_GetCalibrationStatus(ADC_x));
	 
	 ADC_SoftwareStartConvCmd(ADC_x,ENABLE);
	 
 }	 
//static void  ADCx_NVIC_Config(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVIC_InitStructure.NVIC_IRQChannel=ADC_IRQ;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
	void ADCx_Init(void)
	{
//		ADCx_NVIC_Config();
		ADCx_GPIO_Config();
		ADCx_Mode_Config();
	}
	
	
	
	
	
	
	
	
	

	





	
