#ifndef DRAW_API_H
#define DRAW_API_H
#include "oled_config.h"
#include "oled_driver.h"
#include "oled_draw.h"
#include "oled_basic.h"
#include "oled_color.h"
#include "oled_buffer.h"
#include "oled_font.h"
#include "oled_bmp.h"
#include "oled_debug.h"

//***********************************************************************
//*		 为了做这个绘制图形库，我参考了很多其他的算法,花了大量时间去做移植
//*优化，其中参考最多的是github中的arduboy游戏机，大部分图形是移植它的，
//*现在是最初的初稿版本,还有很多地方需要优化改进。我想要将这个图形库做大，
//*后续会加入更多有趣的东西，和模块，代码都是用最简单的方式编写的，都是开源的。
//*后续也会加上注释说明，让更多人以单片机和oled屏来入门硬件编程，如果你
//使用了该库，请标明出处。b站关注oximeterg，可获取该库的最新版本和消息。
//注意：绘制填充或实心的图形，影响刷新效率（待优化中）
//*oled屏图形库0.0.0.1        							作者：maoyongjie     
//https://github.com/hello-myj/stm32_oled/
//************************************************************************

//-------------------------------------------------------------------------
/**************************************************************************/
														//坐标说明
/*														 x(0~127)
												 ------------------>
												|
												|
												|y(0~63)
												|
												|
												v
*/
//--------------------------------------------------------------------------
/**************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////
//功能:初始化图形库
void InitGraph(void);
//功能:将屏幕数据更新到设备上
void UpdateScreen(void);
//功能:清屏
void ClearScreen(void);
//请将此函数放入1ms中断里，为图形提供时基
void OledTimeMsFunc(void);
//图形库test.c的延时函数
void DelayMs(uint32_t ms);


//功能:设置字体的背景模式 0为透明，1为正常。
void SetTextBkMode(unsigned char value);
//功能:获取字体的背景模式 0为透明，1为正常。
unsigned char GetTextBkMode(void);

//功能:设置绘制的颜色  pix_black:黑色、pix_white:白色
extern void SetDrawColor(Type_color value);
//功能:获取当前设置的绘制颜色  pix_black:黑色、pix_white:白色
extern Type_color GetDrawColor(void);
//功能:设置填充的颜色  pix_black:黑色、pix_white:白色
extern void SetFillcolor(Type_color value);
//功能:获取当前设置的填充颜色  pix_black:黑色、pix_white:白色
extern Type_color GetFillColor(void);



/////////////////////////////////////////////////////////////////////////////////////////////////////
//以下函数为oled.draw中直接供用户调用的函数

//功能：绘制一个点
extern void DrawPixel(int x,int y);
//功能：获取一个像素点的颜色
extern Type_color GetPixel(int x,int y);

//功能:绘制一条任意线
extern void DrawLine(int x1,int y1,int x2,int y2);
//功能:快速绘制一条水平线 w为长度
extern void DrawFastHLine(int x, int y, unsigned char w);
//功能:快速绘制一条垂直线
extern void DrawFastVLine(int x, int y, unsigned char h);
//功能:连续画线 折线 num为折点个数
void DrawPolyLineTo(const TypeXY *points,int num);

//功能:使用对角点绘制矩形
extern void DrawRect1(int left,int top,int right,int bottom);
//功能:使用对角点填充矩形
extern void DrawFillRect1(int left,int top,int right,int bottom);
//功能:使用顶点 宽高绘制矩形
extern void DrawRect2(int left,int top,int width,int height);
//功能:使用顶点 宽高填充矩形
extern void DrawFillRect2(int left,int top,int width,int height);

//功能:绘制一个圆
extern void DrawCircle( int usX_Center, int usY_Center, int usRadius);
//功能:绘制一个实心圆
extern void DrawFillCircle( int usX_Center, int usY_Center, int usRadius);
//功能:4份之一圆要画哪一份或哪几份
extern void DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername);
//功能://填充2个四分之一圆和中间的矩形 (专用函数 见函数注释)
extern void DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta);

//功能:绘制一个圆弧(需优化)
extern void DrawArc(int x,int y,unsigned char r,int angle_start,int angle_end);
//功能:填充一个圆弧(待补充)
extern void DrawFillArc(int x,int y,unsigned char r,int angle_start,int angle_end);

//功能:绘制一个圆角矩形
extern void DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r);
//功能:绘制一个填充圆角矩形
extern void DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r);

//功能:绘制一个椭圆
extern void DrawEllipse(int x0,int y0,int a,int b);
//功能:绘制一个填充椭圆
extern void DrawFillEllipse(int x0,int y0,int a,int b);
//功能:绘制一个矩形内切椭圆
extern void DrawEllipseRect( int x0, int y0, int x1, int y1);

//功能:绘制一个三角形
extern void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
//功能:绘制一个填充三角形
extern void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);

//功能:绘制一张图片 bitmap为图片数据（可通过取模获取）
extern void DrawBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h);


//功能:设置字体大小  0 1 2 3
extern void SetFontSize(unsigned char value);
//功能:获取字体大小
extern unsigned char GetFontSize(void);
//功能:设置填充字符时的背景颜色
extern void SetTextBkMode(Type_textbk value);
//功能:获取填充字符时的背景颜色
extern Type_textbk GetTextBkMode(void);
//功能:绘制一个字符 特殊地:当size=0时 x为0-7大行 y为0-127列
extern void DrawChar(int x, int y, unsigned char c);
//功能:绘制字符串 特殊地:当size=0时 x为0-7大行 y为0-127列
extern void DrawString(int x, int y,char *str);
//功能:绘制数字 len为数字长度 特殊地:当size=0时 x为0-7大行 y为0-127列
extern void DrawNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len);
//显示汉字
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char *cn);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//以下函数为oled.basic中直接供用户调用的函数


//功能:可用于填充一个封闭图形(可能在填充圆弧中非常适合使用)
extern void FloodFill2(unsigned char x,unsigned char y,int oldcolor,int newcolor);
//功能:移动绘制坐标
extern void MoveTo(int x,int y);
//功能:线性绘制,并将绘制坐标移动到下一个坐标(在绘制折线中被调用)
extern void LineTo(int x,int y);
//功能:获取当前点绘制点的y坐标
extern int GetY(void);
//功能:获取当前点绘制点的X坐标
extern int GetX(void);
//功能:获取当前点绘制点的X、Y坐标
extern TypeXY GetXY(void);

//功能:设置旋转中心点
extern void SetRotateCenter(int x0,int y0);
//功能:设置旋转角度
extern void SetAngle(float angle);
//功能:设置旋转方向
extern void SetAnggleDir(int direction);
//功能:设置角度、旋转方向、旋转中心
extern void SetRotateValue(int x,int y,float angle,int direct);
//功能:将一个坐标旋转一定角度
extern TypeXY GetRotateXY(int x,int y);




//屏幕数据缓冲
extern void SetScreenBuffer(void);
//功能:设置新的缓冲作为屏幕数据，
extern void SetTempBuffer(void);
//功能:获取当前的缓冲buffer的系数 返回缓冲系数SCREEN_BUFFER或TEMP_BUFFER
extern unsigned char GetSelectedBuffer(void);
//功能:清除掉默认的屏幕缓冲数据
extern void ClearScreenBuffer(unsigned char val);
//功能:清除掉临时的屏幕缓冲数据
extern void ClearTempBuffer(void);
//功能:临时缓冲的功能
extern void TempBufferFunc(int func);
//功能:固定帧刷新
extern unsigned char FrameRateUpdateScreen(int value);
//功能:用以打印调试bug，功能和printf一致，不用使用ClearScreen方法也可打印出数据
extern int OledPrintf(const char *str,...);

#endif

