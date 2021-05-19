/*******************************************************************************************
* PID���ô���
* ����汾��V1.0
* �������ڣ�2020-9-7
* ����Ⱥ�ģ�773080352
*******************************************************************************************/
#include "pid.h"

/*****************************************************************************
* ��  ����void PID_Pos(PID_TYPE*PID,float target,float measure)
* ��  �ܣ�λ��ʽPID�㷨
* ��  ����PID: �㷨P I D�����Ľṹ��
*         target: Ŀ��ֵ
*         measure: ����ֵ
* ����ֵ����
* ��  ע: PID����������ú���
*****************************************************************************/
void PID_Pos(PID_TYPE*PID,float target,float measure)
{
	PID->Error  = target - measure;              //���
	PID->Differ = PID->Error - PID->PreError;    //΢����
	PID->Pout = PID->P * PID->Error;                        //��������
	PID->Iout = PID->Ilimit_flag * PID->I * PID->Integral;  //���ֿ���
	PID->Dout = PID->D * PID->Differ;                       //΢�ֿ���
	PID->OutPut =  PID->Pout + PID->Iout + PID->Dout;       //���� + ���� + ΢���ܿ���
	
	PID->Integral += PID->Error;                        //�������л���
	if(PID->Integral > PID->Irang)                      //�����޷�
		PID->Integral = PID->Irang;
	if(PID->Integral < -PID->Irang)                     //�����޷�
		PID->Integral = -PID->Irang;                    
	PID->PreError = PID->Error ;                            //ǰһ�����ֵ
}

/*****************************************************************************
* ��  ����void PidPrg_init(void)
* ��  �ܣ���ʼ��PID�ṹ�����һЩ��Աֵ
* ��  ������
* ����ֵ���� 
*****************************************************************************/
void PidPrg_init(void)
{
	
}


