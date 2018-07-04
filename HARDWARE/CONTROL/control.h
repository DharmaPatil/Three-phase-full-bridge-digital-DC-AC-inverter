#ifndef CONTROL_H_
#define CONTROL_H_

#define Error_Buf_Size 2
#define Output_Buf_Size 2

// ���������е�ʱ���� 
typedef unsigned short u16;
typedef unsigned char u8;


// ����������С�뻺������С��ͬ���Է��㴦��
// ��ʵ�ʻ��������Լ�Сһ���������Ծ����ܼ�С�������ݴ���
typedef struct _Control_struct
{
	float Control_Tabel_Error[Error_Buf_Size+1];
	float Control_Tabel_Output[Output_Buf_Size];
	u16 Error_Buf[Error_Buf_Size];
	u16 Output_Buf[Output_Buf_Size];
	u16 Target;
	u16 Error;
	float feedforward_factor;
} Control_struct;

extern Control_struct control;

void Time_Out(u8 TIME);

// ���ܣ����Ƴ�ʼ��
// ������
//			control			:	����ʼ���Ŀ��ƽṹ�� 
//			Target_Voltage	:	Ŀ���ѹ��VΪ��λ��
//			Tabel_Error		:	��������������ϵ��
//			Tabel_Output 	:	���������������ϵ��
//			Rin_ratio		:	�����ѹ�ȵ��� (RiU+RiD)/RiD
//			Rout_ratio		:	�����ѹ�ȵ��� (RoU+RoD)/RoD
void Control_Init(Control_struct* control,float Target_Voltage,float* Tabel_Error,float* Tabel_Output);


// ���ܣ������������
// ������
//			control			:	���ƽṹ�� 
u16 Control_Output(Control_struct* control,u16 feedforward);
// ���Կ���Ƕ�������������ж��� 

#endif
