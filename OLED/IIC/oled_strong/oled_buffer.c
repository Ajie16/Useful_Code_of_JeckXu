/*
	ԭ������������:							MjGame 		https://space.bilibili.com/38673747
	ͬGifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	��������ע��ɾ�������Ż��� ��������:	һֻ����Ե	https://space.bilibili.com/237304109
	����֮ǰ��ԭ�����汾����һͬ�ṩ,���������ַ��ȡ���������Ϣ,������������ԭ��ͬ��,��лԭ��
	
	
	��c�ļ����ڶ���Ļ������в���
	���������Ļ�������ʱ����
	����ֻ��Ŀǰѡ��Ļ�����в���
	Ŀǰѡ��Ļ����ͨ����������������������֮һ
	
	Ȼ������ṩ����д��ȡ�����е�8λ���ݻ�1λ���ݵĽӿ�
	����Ǹ��»������ݵ���Ļ
*/

#include "oled_buffer.h"
#include "oled_config.h"
#include "oled_color.h"
#include <string.h>
//#include "usart.h"

//���建�� ��Ļ����������ʱ������
unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN]={0};	//��Ļ����
unsigned char TempBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN]={0};	//��ʱ��������
static _Bool _SelectedBuffer=SCREEN_BUFFER;						//��ǰѡ��Ļ�����

#define BUFFERSIZE  sizeof(ScreenBuffer)
extern void UpdateTempBuffer(void);
extern void UpdateScreenBuffer(void);

///////////////////////////////////////////////////////////////////
//����ѡ�� ��Ļ����
void SetScreenBuffer(void)
{
	_SelectedBuffer=SCREEN_BUFFER;
}
//����ѡ�� ��ʱ����
void SetTempBuffer(void)
{
	_SelectedBuffer=TEMP_BUFFER;
}
//��ȡ����Ŀǰѡ��Ļ�����
unsigned char GetSelectedBuffer(void)
{
	return _SelectedBuffer;
}
//����:�����Ļ��������
void ClearScreenBuffer(unsigned char val)
{
	memset(ScreenBuffer,val,sizeof(ScreenBuffer));
}
//����:�����ʱ��������
void ClearTempBuffer(void)
{
	memset(TempBuffer,0,sizeof(TempBuffer));
}

//����ʱ�������һЩ����
//func:ִ�еĹ��ܿ�ѡ��Ĳ�������
/*
	TEMPBUFF_COPY_TO_SCREEN, 		 ��temp���帴�Ƶ���Ļ����
	TEMPBUFF_CLEAN,					 �����temp��������
	TEMPBUFF_COVER_L,				 ��temp���������ȡ���ٸ��ǵ���Ļ�ϵ�����
	TEMPBUFF_COVER_H				 ��temp��������ݸ��ǵ���Ļ�ϵ����� */
void TempBufferFunc(int func)
{
	int i,j;
	switch (func)
	{
		case TEMPBUFF_COPY_TO_SCREEN:
			memcpy(ScreenBuffer,TempBuffer,BUFFERSIZE);
			break;
		case TEMPBUFF_CLEAN:
			ClearTempBuffer();
			break;
		case TEMPBUFF_COVER_H:
				for(i=0;i<8;i++)
					for(j=0;j<128;j++)
						ScreenBuffer[i][j] |=TempBuffer[i][j];
				break;
		case TEMPBUFF_COVER_L:
				for(i=0;i<8;i++)
					for(j=0;j<128;j++)
						ScreenBuffer[i][j] &=~TempBuffer[i][j];
				break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//��ȡѡ��Ļ�������8λ����
unsigned char ReadByteBuffer(int page,int x)
{
	return _SelectedBuffer? ScreenBuffer[page][x] :TempBuffer[page][x];
}
//д���ȡѡ��Ļ�����8λ����
void WriteByteBuffer(int page,int x,unsigned char byte)
{
	if(_SelectedBuffer)
	{
		ScreenBuffer[page][x] =byte;
	}
	else
	{
		TempBuffer[page][x] =byte;
	}
}

//���õ�ǰѡ��Ļ����� �� ĳһ���������
void SetPointBuffer(int x,int y,int value)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //������Χ
		return;
	if(_SelectedBuffer)
	{
		if(value)
			ScreenBuffer[y/SCREEN_PAGE_NUM][x] |= 1<<(y%SCREEN_PAGE_NUM);
		else
			ScreenBuffer[y/SCREEN_PAGE_NUM][x] &= ~(1<<(y%SCREEN_PAGE_NUM));	
	}
	else
	{
		if(value)
			TempBuffer[y/SCREEN_PAGE_NUM][x] |= 1<<(y%SCREEN_PAGE_NUM);
		else
			TempBuffer[y/SCREEN_PAGE_NUM][x] &= ~(1<<(y%SCREEN_PAGE_NUM));	
	}
}
//��ȡ��ǰѡ��Ļ����� �� ĳһ�����ɫ
unsigned char GetPointBuffer(int x,int y)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //������Χ
		return 0;
	if(_SelectedBuffer)
		return (ScreenBuffer[y/SCREEN_PAGE_NUM][x]>>(y%SCREEN_PAGE_NUM))&0x01;
	else
		return (TempBuffer[y/SCREEN_PAGE_NUM][x]>>(y%SCREEN_PAGE_NUM))&0x01;
}
//ˢ����Ļ��ʾ
void UpdateScreenDisplay(void)
{
	UpdateScreenBuffer();
}




