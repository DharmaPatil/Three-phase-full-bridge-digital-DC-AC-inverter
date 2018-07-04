#include "adc.h"
#include "delay.h"		
#include "lcd.h"
#include "stdio.h"
#include "oled.h"
#define Filter_Buf_N 10
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//��·ADC��ÿ·3��ͨ��														   
//void  Adc_Init(void)
//{    
// 
//  GPIO_InitTypeDef  		GPIO_InitStructure;
//	ADC_CommonInitTypeDef ADC_CommonInitStructure;
//	ADC_InitTypeDef       ADC_InitStructure;
//	DMA_InitTypeDef 			DMA_InitStructure;
//	
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ�� 
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//ʹ��ADC1ʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
//	
//		
////	DMA_DeInit(DMA2_Stream0);//�ٷ��ļ���û�У�����Ӧ��û�ж���ϵ
//	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC_CCR_ADDRESS;//(u32)&ADC1->DR;//DMA�����ַ
//  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&Adc_Value;//DMA �洢��0��ַ
//  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢��ģʽ
//  DMA_InitStructure.DMA_BufferSize = 6;//���ݴ�����
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:8λ
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:8λ
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ʹ��ѭ��ģʽ / DMA_Mode_Normal
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�ߵ����ȼ�
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//  DMA_Init(DMA2_Stream0, &DMA_InitStructure);//��ʼ��DMA Stream
//	
//  DMA_Cmd(DMA2_Stream0, ENABLE); 	
//	
////��ʼ��IO��
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_6 | GPIO_Pin_7 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_DOWN;//���� GPIO_PuPd_NOPULL
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2  | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_0;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_DOWN;//����
//  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ�� 	
// 
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	//ADC1��λ
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
// 
// 
//  ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_RegSimult;//������ͬʱת��ģʽ
//  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
//  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;//ADC_DMAAccessMode_Disabled;// //DMAʹ��
//  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2; //APB 84MHz,ADC 21MHz
//  ADC_CommonInit(&ADC_CommonInitStructure);
//	
//  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
//  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ	
//  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
//  ADC_InitStructure.ADC_NbrOfConversion = 3;//3��ת���ڹ��������� 
//  ADC_Init(ADC1, &ADC_InitStructure);
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_3Cycles ); 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_3Cycles ); 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_3Cycles ); 

//	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
//  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ	
//  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
//  ADC_InitStructure.ADC_NbrOfConversion = 3;//3��ת���ڹ��������� 
//  ADC_Init(ADC2, &ADC_InitStructure);
//	ADC_RegularChannelConfig(ADC2, ADC_Channel_10, 1, ADC_SampleTime_3Cycles ); 
//	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 2, ADC_SampleTime_3Cycles ); 
//	ADC_RegularChannelConfig(ADC2, ADC_Channel_12, 3, ADC_SampleTime_3Cycles ); 

//	//ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
//	//ADC_Cmd(ADC1, ENABLE);//����ADת����	 
//	//ADC_DMACmd(ADC1, ENABLE);
//	
//	ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
//	
//  ADC_Cmd(ADC1, ENABLE);
//  ADC_Cmd(ADC2, ENABLE);
//	
//	ADC_SoftwareStartConv(ADC1);

//}

//��·ADC��ÿ·2��ͨ��
void  Adc_Init(void)
{    
 
  GPIO_InitTypeDef  		GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	DMA_InitTypeDef 			DMA_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ�� 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//ʹ��ADC1ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
		
//	DMA_DeInit(DMA2_Stream0);//�ٷ��ļ���û�У�����Ӧ��û�ж���ϵ
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC_CCR_ADDRESS;//(u32)&ADC1->DR;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&Adc_Value;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢��ģʽ
  DMA_InitStructure.DMA_BufferSize = 6;//���ݴ�����
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ʹ��ѭ��ģʽ / DMA_Mode_Normal
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�ߵ����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);//��ʼ��DMA Stream
	
  DMA_Cmd(DMA2_Stream0, ENABLE); 	
	
//��ʼ��IO��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5  | GPIO_Pin_3 | GPIO_Pin_6  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_DOWN;//���� GPIO_PuPd_NOPULL
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2  | GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ�� 	
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	//ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
 
 
  ADC_CommonInitStructure.ADC_Mode = ADC_TripleMode_RegSimult;//������ͬʱת��ģʽ
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;//ADC_DMAAccessMode_Disabled;// //DMAʹ��
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4; //APB 84MHz,ADC 21MHz
  ADC_CommonInit(&ADC_CommonInitStructure);
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 2;//2��ת���ڹ��������� 
  ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_15Cycles ); 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_15Cycles ); 

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 2;//2��ת���ڹ��������� 
  ADC_Init(ADC2, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_6, 1, ADC_SampleTime_15Cycles ); 
	ADC_RegularChannelConfig(ADC2, ADC_Channel_10, 2, ADC_SampleTime_15Cycles ); 

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 2;//2��ת���ڹ��������� 
  ADC_Init(ADC3, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 1, ADC_SampleTime_15Cycles ); 
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2, ADC_SampleTime_15Cycles ); 

	//ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
	//ADC_Cmd(ADC1, ENABLE);//����ADת����	 
	//ADC_DMACmd(ADC1, ENABLE);
	
	ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
	
  ADC_Cmd(ADC1, ENABLE);
  ADC_Cmd(ADC2, ENABLE);
  ADC_Cmd(ADC3, ENABLE);	
	
	ADC_SoftwareStartConv(ADC1);
	ADC_SoftwareStartConv(ADC3);
}	

//���ADCֵ
//ch:ͨ��ֵ 0~16
//����ֵ:ת�����
u16 Get_Adc(u8 ch)   
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ

// @brief : ����ƽ���˲�
// @param :
//	buf			: ���ݻ�����
//	new_data:	��ӵ����ݻ�������������
//	n				: ���ݻ���������
// @ret		: �˲���ó��ļ�����
double filter(double* buf,double new_data,u8 n)
{
	u8 i;
	double sum = 0;
	double max = buf[0];
	double min = buf[0];
	for(i = 0;i < n-1;i++)
	{
			buf[i] = buf[i+1];
			sum += buf[i];
		if(buf[i]>max) max = buf[i];
		if(buf[i]<min) min = buf[i];
	}
	buf[i] = new_data;
	sum += buf[i];
	if(buf[i]>max) max = buf[i];
	if(buf[i]<min) min = buf[i];
	return (sum-max-min)/(n-2);
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_us(20);
	}
	return temp_val/times;
} 
	 
void Change_Channel_And_Display(u8 channel,double* adc_cal_value)
{
		static double filter_buf[4][Filter_Buf_N];
		u16 adcx=0;
		char str_buf[30];
		//float temp=0;
		double temp=0;	
		switch(channel)
		{
			case 6://Select channel ONE and display its voltage
			{	adcx=Get_Adc_Average(ADC_Channel_6,10);		//�õ�ADCת��ֵ	  
				temp=(float)adcx*(3.3/4096);			        //�õ�ADC��ѹֵ
				adc_cal_value[0] = temp=filter(filter_buf[0],20*(temp+0.197)/2.45,Filter_Buf_N);
				sprintf(str_buf,"Vi VOL:%2.2fV",temp);
				LCD_ShowString(30,190,200,16,16,(u8*)str_buf);//CH0
			}
			case 3://Select channel TWO and display its voltage
			{	adcx=Get_Adc_Average(ADC_Channel_3,10);		//�õ�ADCת��ֵ	  
				temp=(float)adcx*(3.3/4096);			        //�õ�ADC��ѹֵ
				adc_cal_value[1] = temp=filter(filter_buf[1],30*(temp+0.197)/2.428,Filter_Buf_N);
				sprintf(str_buf,"Vo VOL:%2.2fV",temp);
				LCD_ShowString(30,210,200,16,16,(u8*)str_buf);//CH0
			}
			case 11://Select channel FIVE and display its current
			{	adcx=Get_Adc_Average(ADC_Channel_11,10);		//�õ�ADCת��ֵ	  
				temp=(float)adcx*(3.3/4096);			        //�õ�ADC��ѹֵ
				adc_cal_value[2] = temp=filter(filter_buf[2],(2.42-temp)/0.184,Filter_Buf_N);
				sprintf(str_buf,"Io VOL:%2.2fA",temp);
				LCD_ShowString(30,230,200,16,16,(u8*)str_buf);//CH0
			}
			case 5://Select channel SIX and display its voltage
			{	adcx=Get_Adc_Average(ADC_Channel_5,10);		//�õ�ADCת��ֵ	  
				temp=(float)adcx*(3.3/4096);			        //�õ�ADC��ѹֵ
				adc_cal_value[3] = temp=filter(filter_buf[3],(2.41-temp)/0.184,Filter_Buf_N);
				sprintf(str_buf,"Ii VOL:%2.2fA",temp);
				LCD_ShowString(30,250,200,16,16,(u8*)str_buf);//CH0
			
			}
	}
}

void ADC_DMA_Init()
{
		
}





