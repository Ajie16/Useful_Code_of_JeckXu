/*
	ԭ������������:							MjGame 		https://space.bilibili.com/38673747
	ͬGifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	��������ע��ɾ�������Ż��� ��������:	һֻ����Ե	https://space.bilibili.com/237304109
	����֮ǰ��ԭ�����汾����һͬ�ṩ,���������ַ��ȡ���������Ϣ,������������ԭ��ͬ��,��лԭ��
	
	��c�ļ���������oled
	�����ʼ��oled���� ˢ��oled
	ע��!!! 
	������ʾ����Ч�� OledTimeMsFunc()�����1ms�жϵ���1ms����һ��Ϊ���ṩʱ���׼ ԭ���Ƿ���δ�ʱ����
*/

#include "oled_config.h"
#include "oled_driver.h"
//#include "delay.h"
#include "../Delay/Delay.h"
#include "draw_api.h"

extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
extern unsigned char TempBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
unsigned int OledTimeMs=0;												//ʱ���׼

//��ʼ��ͼ�ο⣬�뽫Ӳ����ʼ����Ϣ�������
void DriverInit(void)
{
//	SPI_Configuration();	//��ʼ���ӿ�
	OLED_Init();			//��ʼ������oled
}

//��ScreenBuffer��Ļ�����������ʾ����Ļ��
void UpdateScreenBuffer(void)
{
	OLED_FILL(ScreenBuffer[0]);
}
//��TempBuffer��ʱ�����������ʾ����Ļ��
void UpdateTempBuffer(void)
{
	OLED_FILL(TempBuffer[0]);
}

//////////////////////////////////////////////////////////
//�뽫�˺�������1ms�ж��Ϊͼ���ṩʱ��
//ϵͳʱ���׼��Ҫ����FrameRateUpdateScreen()�й̶�֡��ˢ����Ļ
void OledTimeMsFunc(void)
{
	if(OledTimeMs != 0x00)
	{ 
		OledTimeMs--;
	}
}
//ͼ�ο���ͨ����ʱ���� ��Ҫ�û��Լ����� ������delay.c�е���
void DelayMs(uint32_t ms)
{
	delay_ms(ms);
}

