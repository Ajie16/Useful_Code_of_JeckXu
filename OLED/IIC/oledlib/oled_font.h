#ifndef OLED_FONT_H
#define OLED_FONT_H

typedef enum 
{
	TEXT_BK_NULL=0,
	TEXT_BK_NOT_NULL,
}Type_textbk;

struct Cn16CharTypeDef                	// ������ģ���ݽṹ 
{
	unsigned char  Index[2];            // ������������,һ������ռ�����ֽ�	
	unsigned char  Msk[32];             // ����������(16*16��32������) 
};


extern const unsigned char font5x7[];
extern const unsigned char F8X16[];
extern struct Cn16CharTypeDef const CN16CHAR[];

unsigned char GetFontSize(void);
void SetFontSize(unsigned char value);
#endif

