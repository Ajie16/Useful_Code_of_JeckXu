#ifndef OLED_CONFIG_H
#define OLED_CONFIG_H
#include "oled_basic.h"


//������Ļ����״��
//�����˿���չ�� �����������������
//��ע����������c�ļ���������Щ�궨��Ĳ���

#define   	OLED_12864						//��Ļ����
#define 	SCREEN_PAGE_NUM			(8)		//������ (����)
#define  	SCREEN_PAGEDATA_NUM   	(128)	//ÿ���е�����
#define  	SCREEN_ROW 				(64)	//������
#define 	SCREEN_COLUMN 			(128)	//������

void OledTimeMsFunc(void);

#endif

