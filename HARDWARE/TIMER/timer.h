#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#define Vout ADC_CH3_
#define Vin ADC_CH5_
#define Iout ADC_CH6_
extern u16 ADC_CH3_;//ȫ�ֱ������ADCͨ��3��ֵ���������ж��л�ȡ
extern u16 ADC_CH5_;//ȫ�ֱ������ADCͨ��5��ֵ���������ж��л�ȡ
extern u16 ADC_CH6_;//ȫ�ֱ������ADCͨ��6��ֵ���������ж��л�ȡ
extern u16 AD_TIME;
void TIM3_Int_Init(u16 arr,u16 psc);
#endif
