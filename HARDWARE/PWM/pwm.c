#include "pwm.h"
#include "led.h"
#include "usart.h"

//TIM14 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	u32 arrr=arr;
	u32 ppsc=psc;
	//�ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;              //gpio
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   //tim
	TIM_OCInitTypeDef  TIM_OCInitStructure;    				//oc
	TIM_BDTRInitTypeDef TIM_BDTRInitStruct;   			  //bdtr
	//ʱ��ʹ�ܣ���ʱ��ʱ�ӣ�IO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTAʱ��	
	//IO�ڸ��ÿ���
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); //GPIOA8����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOA8����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_TIM1); //GPIOB13����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM1); //GPIOB13����Ϊ��ʱ��1	
	//IO������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;           //GPIOA8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼTIM1_CH1
	GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9);										 //�õ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;           //GPIOB13 
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��TIM1_CHIN
	GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14);									 //�õ�
	
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=PWM_Period-1;   //�Զ���װ��ֵ����������
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;             //��λ���ڵ�MOE=1��ͨ��Ϊ�������ʱ��
	//TIM_OSSRState_Disable������ʱ��������ʱ����ֹOC/OCN���(OC/OCNʹ������ź�=0)��
	//TIM_OSSRState_Enable������ʱ��������ʱ��һ��CCxE=1��CCxNE=1�� OC/OCN�����������е�ƽ��Ȼ��OC/OCNʹ������ź�=1
	TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;            //��ʱ��������ʱ����ֹOC/OCN���(OC/OCNʹ������ź�=0)��
	TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;                //�����Ĵ���ȫ�رա��Ĵ�����д����
	TIM_BDTRInitStruct.TIM_DeadTime  = 0x7f&PWM_Dead_Time;               //72mhz 13.89ns*44*=0.6us
	TIM_BDTRInitStruct.TIM_Break = TIM_Break_Disable;                    //TIM1ɲ������ʧ��
	TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_Low;       //TIM1ɲ�����Ը�
	TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable; //MOEֻ�ܱ�����á�1��
	TIM_BDTRConfig(TIM1,&TIM_BDTRInitStruct);                            //����ɲ�����ԣ���ȥʱ�䣬����ƽ��OSSI,OSSR״̬��

	//��ʼ��TIM1 Channe1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�������ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //TIM_OCPolarity������Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High; //TIM_OCPolarity����������Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //TIM1_OCIdleStateѡ�����״̬�µķǹ���״̬(MOE=0ʱ����TIM1����ȽϿ���״̬��
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //MOE = 0ʱ���û������������ȽϿ���״̬
	TIM_OCInitStructure.TIM_Pulse = TIM1->CCR1;//��ȷ��
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_Pulse = TIM1->CCR2;//��ȷ��
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC1
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//����MOEλΪ1���ϵ�󲻹ر�
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
					  
}  
void TIM8_PWM_Init(u32 arr,u32 psc)
{		 					 
	u32 arrr=arr;
	u32 ppsc=psc;
	//�ṹ��
	GPIO_InitTypeDef 					GPIO_InitStructure;             //gpio
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;   				//tim
	TIM_OCInitTypeDef 				TIM_OCInitStructure;    				//oc
	TIM_BDTRInitTypeDef 			TIM_BDTRInitStruct;   			  	//bdtr
	//ʱ��ʹ�ܣ���ʱ��ʱ�ӣ�IO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	//TIM8ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTB|Cʱ��	
	//IO�ڸ��ÿ���
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); //GPIOC7����Ϊ��ʱ��8
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM8); //GPIOB14����Ϊ��ʱ��8	
	//IO������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼTIM1_CH1
	GPIO_ResetBits(GPIOC , GPIO_Pin_7);										 //�õ�
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOB14
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��TIM1_CHIN
	GPIO_ResetBits(GPIOB , GPIO_Pin_14);									 //�õ�
	
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=PWM_Period_TIM8-1;   //�Զ���װ��ֵ����������
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//��ʼ����ʱ��8
	
	TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;             //��λ���ڵ�MOE=1��ͨ��Ϊ�������ʱ��
	//TIM_OSSRState_Disable������ʱ��������ʱ����ֹOC/OCN���(OC/OCNʹ������ź�=0)��
	//TIM_OSSRState_Enable������ʱ��������ʱ��һ��CCxE=1��CCxNE=1�� OC/OCN�����������е�ƽ��Ȼ��OC/OCNʹ������ź�=1
	TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;            //��ʱ��������ʱ����ֹOC/OCN���(OC/OCNʹ������ź�=0)��
	TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;                //�����Ĵ���ȫ�رա��Ĵ�����д����
	TIM_BDTRInitStruct.TIM_DeadTime  = 0x7f&PWM_Dead_Time_TIM8;               //72mhz 13.89ns*44*=0.6us
	TIM_BDTRInitStruct.TIM_Break = TIM_Break_Disable;                    //TIM1ɲ������ʧ��
	TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_Low;       //TIM1ɲ�����Ը�
	TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable; //MOEֻ�ܱ�����á�1��
	TIM_BDTRConfig(TIM8,&TIM_BDTRInitStruct);                            //����ɲ�����ԣ���ȥʱ�䣬����ƽ��OSSI,OSSR״̬��
	
	//��ʼ��TIM8 Channe2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�������ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //TIM_OCPolarity������Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High; //TIM_OCPolarity����������Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //TIM1_OCIdleStateѡ�����״̬�µķǹ���״̬(MOE=0ʱ����TIM1����ȽϿ���״̬��
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //MOE = 0ʱ���û������������ȽϿ���״̬	
	TIM_OCInitStructure.TIM_Pulse = TIM8->CCR2;//��ȷ��
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC1
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM1
	TIM_CtrlPWMOutputs(TIM8,ENABLE);//����MOEλΪ1���ϵ�󲻹ر�
  TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPEʹ�� 
					  
}

