/*
	原作者哔哩哔哩:							MjGame 		https://space.bilibili.com/38673747
	同GifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	代码整理注释删减增加优化等 哔哩哔哩:	一只程序缘	https://space.bilibili.com/237304109
	整理之前的原代码随本代码一同提供,浏览以上网址获取更多相关信息,本代码以征得原作同意,感谢原作
	
	此c文件用于配置oled
	例如初始化oled引脚 刷新oled
	注意!!! 
	如需演示动画效果 OledTimeMsFunc()需放入1ms中断等中1ms调用一次为库提供时间基准 原作是放入滴答定时器中
*/

#include "oled_config.h"
#include "oled_driver.h"
//#include "delay.h"
#include "../Delay/Delay.h"
#include "draw_api.h"

extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
extern unsigned char TempBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
unsigned int OledTimeMs=0;												//时间基准

//初始化图形库，请将硬件初始化信息放入此中
void DriverInit(void)
{
//	SPI_Configuration();	//初始化接口
	OLED_Init();			//初始化配置oled
}

//将ScreenBuffer屏幕缓存的内容显示到屏幕上
void UpdateScreenBuffer(void)
{
	OLED_FILL(ScreenBuffer[0]);
}
//将TempBuffer临时缓存的内容显示到屏幕上
void UpdateTempBuffer(void)
{
	OLED_FILL(TempBuffer[0]);
}

//////////////////////////////////////////////////////////
//请将此函数放入1ms中断里，为图形提供时基
//系统时间基准主要用于FrameRateUpdateScreen()中固定帧率刷新屏幕
void OledTimeMsFunc(void)
{
	if(OledTimeMs != 0x00)
	{ 
		OledTimeMs--;
	}
}
//图形库普通的延时函数 需要用户自己配置 这里在delay.c中调用
void DelayMs(uint32_t ms)
{
	delay_ms(ms);
}

