#include "timer.h"
#include "adc.h"
#include "dac.h"
#include "control.h"
#include "led.h"

//u16 AD_TIME = 0;



void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	static u8 change = 0;
/*	u16 GET=0;
	u8 j=0;
	u16 Temp_MAX = 0; u16 Temp_MIN = 0; u16 Temp_SUM= 0;*/
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		u16 GET=0;
		u8 j=0;
		u16 Temp_MAX = 0; u16 Temp_MIN = 0; u16 Temp_SUM= 0;
		while(TIM1->CNT<=(TIM1->CCR1>>2)){}//�˴�����200��Ϊ�˵ȴ���ƽ��ת�ȶ�����ȷ���Ƿ���Ҫ�Լ��Ƿ������ã���������
			/////////////////////////////////////////////////!!!!!!!!!!!!!!!!!!!
			//////////////////////////////////////////

		for(j=0;j<5;j++)//ͨ��3
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_3Cycles );	//ADC1,ADCͨ��,15������ 
			ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
			GET = ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
			if(j==0)Temp_MAX=Temp_MIN=GET;//��ȡ�״�ת�����
			if(GET>=Temp_MAX)Temp_MAX=GET;//�������ֵ
			if(GET<=Temp_MIN)Temp_MIN=GET;//������Сֵ
			Temp_SUM+=GET;//����ʱ�ܺ�
		}ADC_CH3_ = (Temp_SUM - Temp_MAX - Temp_MIN)/3;	//���ƽ��ֵ
		Temp_MAX=Temp_MIN=Temp_SUM=0;//�ٴγ�ʼ��
		
		for(j=0;j<5;j++)//ͨ��5
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_3Cycles );	//ADC1,ADCͨ��,15������
			ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
			GET = ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
			if(j==0)Temp_MAX=Temp_MIN=GET;//��ȡ�״�ת�����
			if(GET>=Temp_MAX)Temp_MAX=GET;//�������ֵ
			if(GET<=Temp_MIN)Temp_MIN=GET;//������Сֵ
			Temp_SUM+=GET;//����ʱ�ܺ�
		}ADC_CH5_ = (Temp_SUM - Temp_MAX - Temp_MIN)/3;	//���ƽ��ֵ
		Temp_MAX=Temp_MIN=Temp_SUM=0;//�ٴγ�ʼ��
	
		for(j=0;j<5;j++)//ͨ��6
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_3Cycles );	//ADC1,ADCͨ��,15������
			ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
			GET = ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
			if(j==0)Temp_MAX=Temp_MIN=GET;//��ȡ�״�ת�����
			if(GET>=Temp_MAX)Temp_MAX=GET;//�������ֵ
			if(GET<=Temp_MIN)Temp_MIN=GET;//������Сֵ
			Temp_SUM+=GET;//����ʱ�ܺ�
		}ADC_CH6_ = (Temp_SUM - Temp_MAX - Temp_MIN)/3;	//���ƽ��ֵ
	  Temp_MAX=Temp_MIN=Temp_SUM=0;//�ٴγ�ʼ��
		
		
		///////////////////
		//�˴�������Ƽ���
		///////////////////
		//����ú��޸�TIM1->CCR1
		///////////////////
		control.Error = control.Target - Vout;
		TIM1->CCR1 = Control_Output(&control,Vin);
		 
//		AD_TIME--;
//		if(AD_TIME) Time_Out(AD_TIME);
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
