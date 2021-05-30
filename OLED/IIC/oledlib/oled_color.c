/*
	原作者哔哩哔哩:							MjGame 		https://space.bilibili.com/38673747
	同GifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	代码整理注释删减增加优化等 哔哩哔哩:	一只程序缘	https://space.bilibili.com/237304109
	整理之前的原代码随本代码一同提供,浏览以上网址获取更多相关信息,本代码以征得原作同意,感谢原作
	
	此c文件用于对颜色进行操作
	在这里主要是画线线条(一般为白)和填充(一般为白)的颜色
	(在oled.font中还有一个字体背景的颜色(一般为黑))
	在划线画图和打点时都会访问此文件函数获取打点的颜色
*/

#include "oled_color.h"

//如有需要还可以自己迭代字体颜色 文字背景颜色等
static Type_color _Draw=pix_white;
static Type_color _fill=pix_white;


void SetDrawColor(Type_color value)	//就是划线 线条的颜色
{
	_Draw=value;
}
Type_color GetDrawColor(void)
{
	return _Draw;
}

void SetFillcolor(Type_color value)	//就是填充 实心图形内的颜色
{
	_fill=value;
}
Type_color GetFillColor(void)
{
	return _fill;
}
