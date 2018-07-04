#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
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
extern  u16 Adc_Value[];							   
#define ADC_CCR_ADDRESS    ((uint32_t)0x40012308)
void Adc_Init(void); 				//ADCͨ����ʼ��
void ADC_DMA_Init(void);
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  
void Change_Channel_And_Display(u8 channel,double* adc_cal_value);
double filter(double* buf,double new_data,u8 n);//����ƽ���˲�
#endif 















