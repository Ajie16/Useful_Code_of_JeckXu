/*
	ԭ������������:							MjGame 		https://space.bilibili.com/38673747
	ͬGifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	��������ע��ɾ�������Ż��� ��������:	һֻ����Ե	https://space.bilibili.com/237304109
	����֮ǰ��ԭ�����汾����һͬ�ṩ,���������ַ��ȡ���������Ϣ,������������ԭ��ͬ��,��лԭ��
	
	��c�ļ����ڶ���ɫ���в���
	��������Ҫ�ǻ�������(һ��Ϊ��)�����(һ��Ϊ��)����ɫ
	(��oled.font�л���һ�����屳������ɫ(һ��Ϊ��))
	�ڻ��߻�ͼ�ʹ��ʱ������ʴ��ļ�������ȡ������ɫ
*/

#include "oled_color.h"

//������Ҫ�������Լ�����������ɫ ���ֱ�����ɫ��
static Type_color _Draw=pix_white;
static Type_color _fill=pix_white;


void SetDrawColor(Type_color value)	//���ǻ��� ��������ɫ
{
	_Draw=value;
}
Type_color GetDrawColor(void)
{
	return _Draw;
}

void SetFillcolor(Type_color value)	//������� ʵ��ͼ���ڵ���ɫ
{
	_fill=value;
}
Type_color GetFillColor(void)
{
	return _fill;
}
