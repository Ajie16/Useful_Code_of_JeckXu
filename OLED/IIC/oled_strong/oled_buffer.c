/*
	原作者哔哩哔哩:							MjGame 		https://space.bilibili.com/38673747
	同GifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	代码整理注释删减增加优化等 哔哩哔哩:	一只程序缘	https://space.bilibili.com/237304109
	整理之前的原代码随本代码一同提供,浏览以上网址获取更多相关信息,本代码以征得原作同意,感谢原作
	
	
	此c文件用于对屏幕数组进行操作
	数组包括屏幕缓冲和临时缓冲
	函数只会目前选择的缓冲进行操作
	目前选择的缓冲可通过函数设置上面两个缓冲之一
	
	然后就是提供读或写入取缓冲中的8位数据或1位数据的接口
	最后是更新缓冲数据到屏幕
*/

#include "oled_buffer.h"
#include "oled_config.h"
#include "oled_color.h"
#include <string.h>
//#include "usart.h"

//定义缓冲 屏幕缓冲区和临时缓冲区
unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN]={0};	//屏幕缓冲
unsigned char TempBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN]={0};	//临时操作缓冲
static _Bool _SelectedBuffer=SCREEN_BUFFER;						//当前选择的缓冲区

#define BUFFERSIZE  sizeof(ScreenBuffer)
extern void UpdateTempBuffer(void);
extern void UpdateScreenBuffer(void);

///////////////////////////////////////////////////////////////////
//设置选择 屏幕缓冲
void SetScreenBuffer(void)
{
	_SelectedBuffer=SCREEN_BUFFER;
}
//设置选择 临时缓冲
void SetTempBuffer(void)
{
	_SelectedBuffer=TEMP_BUFFER;
}
//获取程序目前选择的缓冲区
unsigned char GetSelectedBuffer(void)
{
	return _SelectedBuffer;
}
//功能:清除屏幕缓冲数据
void ClearScreenBuffer(unsigned char val)
{
	memset(ScreenBuffer,val,sizeof(ScreenBuffer));
}
//功能:清除临时缓冲数据
void ClearTempBuffer(void)
{
	memset(TempBuffer,0,sizeof(TempBuffer));
}

//对临时缓冲进行一些操作
//func:执行的功能可选择的参数如下
/*
	TEMPBUFF_COPY_TO_SCREEN, 		 将temp缓冲复制到屏幕缓冲
	TEMPBUFF_CLEAN,					 清楚掉temp缓冲数据
	TEMPBUFF_COVER_L,				 将temp缓冲的数据取反再覆盖掉屏幕上的数据
	TEMPBUFF_COVER_H				 将temp缓冲的数据覆盖掉屏幕上的数据 */
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
//读取选择的缓冲区的8位数据
unsigned char ReadByteBuffer(int page,int x)
{
	return _SelectedBuffer? ScreenBuffer[page][x] :TempBuffer[page][x];
}
//写入读取选择的缓冲区8位数据
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

//设置当前选择的缓冲区 的 某一个点的亮灭
void SetPointBuffer(int x,int y,int value)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //超出范围
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
//获取当前选择的缓冲区 的 某一点的颜色
unsigned char GetPointBuffer(int x,int y)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //超出范围
		return 0;
	if(_SelectedBuffer)
		return (ScreenBuffer[y/SCREEN_PAGE_NUM][x]>>(y%SCREEN_PAGE_NUM))&0x01;
	else
		return (TempBuffer[y/SCREEN_PAGE_NUM][x]>>(y%SCREEN_PAGE_NUM))&0x01;
}
//刷新屏幕显示
void UpdateScreenDisplay(void)
{
	UpdateScreenBuffer();
}




