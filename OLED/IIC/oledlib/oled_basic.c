/*
	原作者哔哩哔哩:							MjGame 		https://space.bilibili.com/38673747
	同GifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	代码整理注释删减增加优化等 哔哩哔哩:	一只程序缘	https://space.bilibili.com/237304109
	整理之前的原代码随本代码一同提供,浏览以上网址获取更多相关信息,本代码以征得原作同意,感谢原作
	
	
	此c文件用于画图的底层操作(基础操作)
	全屏操作包括 初始化 清屏 更新数组到屏幕
	画线 点 旋转 封闭图形的填充 时间的基准更新
*/

#include "oled_basic.h"
#include "oled_config.h"
#include "oled_buffer.h"
#include "oled_color.h"
#include "math.h"

TypeRoate _RoateValue={{0,0},0,1};
static unsigned char _BitTableS[8]={0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};
static void Rotate(int x0,int y0,int*x,int*y,double angle,int direction);
extern void DriverInit(void);
extern unsigned int OledTimeMs;

//初始化oled
void InitGraph(void)
{
	//初始化引脚 配置oled并清屏
	DriverInit();
}
//清屏
void ClearScreen(void)
{
	ClearScreenBuffer(0);
}
//更新屏幕 注意此处特指刷新屏幕数组而不是临时数组
void UpdateScreen(void)
{
	UpdateScreenDisplay();
}

///////////////////////////////////////////////////////////////////////////////////////////////
//给选择的缓冲区写入8位数据
void FillByte(int page,int x,unsigned  char byte)
{
	if(GetFillColor())
		WriteByteBuffer(page,x,ReadByteBuffer(page,x)|byte);
	else
		WriteByteBuffer(page,x,ReadByteBuffer(page,x)&(~byte));
}
//给选择的缓冲区填充一个矩形
void FillRect(int x,int y,int width,int height)
{
	int i,j;
	int temp =(y+height-1)/8-y/8;	//需要填充的矩形在屏幕中所占的行数 屏幕被分为8大行
	if(x>SCREEN_COLUMN ||y>SCREEN_ROW)   
			return;
	for(i=x; i<x+width&&i<128; i++)
	{
		if( temp==0 )
		{
			FillByte(y/8,i,_BitTableS[height-1]<<(y%8));
		}
		else
		{
			//从左往右 竖向填充
			FillByte(y/8,i,_BitTableS[(8-y%8)-1]<<(y%8));
			for(j=1;j<temp;j++)
			{
				FillByte(y/8+j,i,0xff);
			}
			FillByte(y/8+temp,i,_BitTableS[(height-1+y)%8]);
		}	
	}
}
//画一条起点坐标为x,y 长度为height的竖线 (与DrawFastHLine()类似 不过后者是使用打点实现)
void FillVerticalLine(int x,int y,int height,int value)
{
	int temp =(y+height-1)/8-y/8,j;

	if( temp==0 )
	{
		FillByte(y/8,x,_BitTableS[height-1]<<(y%8));
	}
	else
	{
		FillByte(y/8,x,_BitTableS[(8-y%8)-1]<<(y%8));
		for(j=1;j<temp;j++)
		{
			FillByte(y/8+j,x,0xff);
		}
		FillByte(y/8+temp,x,_BitTableS[(height-1+y)%8]);
	}	
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————
//版权声明：本文为CSDN博主「xtlisk」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/xtlisk/article/details/51249371

//点x，y绕x0，y0旋转angle弧度
float mySqrt(float x)
{
	float a = x;
	unsigned int i = *(unsigned int *)&x;
	i = (i + 0x3f76cf62) >> 1;
	x = *(float *)&i;
	x = (x + a / x) * 0.5;
	return x;
}
//开平方根函数
unsigned int sqrt_16(unsigned long M)  
{  
    unsigned int N, i;  
    unsigned long tmp, ttp;   // 结果、循环计数  
    if (M == 0)               // 被开方数，开方结果也为0  
        return 0;  
    N = 0;  
    tmp = (M >> 30);          // 获取最高位：B[m-1]  
    M <<= 2;  
    if (tmp > 1)              // 最高位为1  
    {  
        N ++;                 // 结果当前位为1，否则为默认的0  
        tmp -= N;  
    }  
    for (i=15; i>0; i--)      // 求剩余的15位  
    {  
        N <<= 1;              // 左移一位  

        tmp <<= 2;  
        tmp += (M >> 30);     // 假设  

        ttp = N;  
        ttp = (ttp<<1)+1;  

        M <<= 2;  
        if (tmp >= ttp)       // 假设成立  
        {  
            tmp -= ttp;  
            N ++;  
        }  
    }  
    return N;  
} 

//需要优化atant2 cos sin算法
static void Rotate(int x0,int y0,int*x,int*y,double angle,int direction)
{
	int temp=(*y-y0)*(*y-y0)+(*x-x0)*(*x-x0);
	double r=mySqrt(temp);
	double a0=atan2(*x-x0,*y-y0);
	if(direction)
	{
		*x=x0+r*cos(a0+angle);
		*y=y0+r*sin(a0+angle);
	}
	else
	{
		*x=x0+r*cos(a0-angle);
		*y=y0+r*sin(a0-angle);	
	}
}

//功能:设置旋转角度
void SetAngle(float angle)
{
	_RoateValue.angle=RADIAN(angle);
}
//功能:设置旋转方向 1为逆时针，0为顺时针
void SetAnggleDir(int direction)
{
	_RoateValue.direct=direction;
}
//功能:设置旋转中心点
void SetRotateCenter(int x0,int y0)
{
	_RoateValue.center.x=x0;
	_RoateValue.center.y=y0;
}
//功能:设置角度、旋转方向、旋转中心
void SetRotateValue(int x,int y,float angle,int direct)
{
	SetRotateCenter(x,y);
	SetAnggleDir(direct);
	SetAngle(angle);
}
//功能:将一个坐标旋转一定角度
//x,y:需要旋转的坐标
//return：旋转后的坐标
TypeXY GetRotateXY(int x,int y)
{
	TypeXY temp;
	int m=x,n=y;

	Rotate(_RoateValue.center.x,_RoateValue.center.y,&m,&n, _RoateValue.angle ,_RoateValue.direct);
	temp.x=m;
	temp.y=n;
	return temp;
}

/////////////////////////////////////////////////////////////////////////////////////
//由某一点开始 获取向上方向同颜色的像素点的个数
unsigned char GetLengthUp(unsigned char x,unsigned char y,unsigned char value)
{
	if(GetPointBuffer(x,y)==value)
	{
		if(y==0)
			return 0;
		return 1+GetLengthUp(x,y-1,value);
	}
	return 0;
}
//和上面函数同理 获取向下方向
unsigned char GetLengthDown(unsigned char x,unsigned char y,unsigned char value)
{
	if(GetPointBuffer(x,y)==value)
	{
		if(y==63)
			return 0;
		return 1+GetLengthUp(x,y+1,value);
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//由一个点开始填充一个封闭图形
//亲测此函数可能有问题 可能是套娃太多 内存不够用
//测试效果是套娃几十个点后花屏
void FloodFill(unsigned char x,unsigned char y,int oldcolor,int newcolor)
{		
	UpdateScreen();
	if(GetPointBuffer(x,y)==oldcolor)//这个点的颜色不对
	{
		SetPointBuffer(x,y,newcolor);//把这个点的颜色改为新颜色
		//开始套娃
		FloodFill(x-1,y,oldcolor,newcolor);//修改这个点周围的4个点的颜色
		FloodFill(x+1,y,oldcolor,newcolor);//用这个方法逐渐扩散 填完范围内所有颜色
		FloodFill(x,y+1,oldcolor,newcolor);
		FloodFill(x,y-1,oldcolor,newcolor);
	}
}
//功能:可用于填充一个封闭图形
//x,y:在封闭图形任意一点坐标
//oldcolor:封闭图形中旧的颜色
//newcolor:填充的新颜色
void FloodFill2(unsigned char x,unsigned char y,int oldcolor,int newcolor)
{
	unsigned char h1=0,h2=0;
	short tempx=x;	
	while(GetPointBuffer(tempx,y)==oldcolor && tempx<128)
	{		
		h1=GetLengthDown(tempx,y,oldcolor);
		h2=GetLengthUp(tempx,y,oldcolor);
		FillVerticalLine(tempx,y-h2,h1+h2,newcolor);
		tempx++;
	}
	tempx=x-1;
	while(GetPointBuffer(tempx,y)==oldcolor&&tempx>0)
	{
		h1=GetLengthDown(tempx,y,oldcolor);
		h2=GetLengthUp(tempx,y,oldcolor);
		FillVerticalLine(tempx,y-h2,h1+h2,newcolor);
		tempx--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
unsigned char pgm_read_byte(const unsigned char * addr)
{
	return *addr;
}
unsigned int oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}	
//功能:固定帧刷新
//OledTimeMs在OledTimeMsFunc()中被1ms中断持续调用 减到0位置
//此函数放在while循环中 符合条件时刷新屏幕
unsigned char FrameRateUpdateScreen(int value)
{
	if(OledTimeMs==0)
	{
		UpdateScreen();
		ClearScreen();
		OledTimeMs=1000/value;
		return 1;
	}
	return 0;
}
//硬核延时函数
void WaitTimeMs(unsigned int time)
{
	OledTimeMs=time;
	while(OledTimeMs);
}

