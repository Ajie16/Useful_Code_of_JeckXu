/*
	ԭ������������:							MjGame 		https://space.bilibili.com/38673747
	ͬGifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	��������ע��ɾ�������Ż��� ��������:	һֻ����Ե	https://space.bilibili.com/237304109
	����֮ǰ��ԭ�����汾����һͬ�ṩ,���������ַ��ȡ���������Ϣ,������������ԭ��ͬ��,��лԭ��
	
	
	��c�ļ����ڻ�ͼ�ĵײ����(��������)
	ȫ���������� ��ʼ�� ���� �������鵽��Ļ
	���� �� ��ת ���ͼ�ε���� ʱ��Ļ�׼����
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

//��ʼ��oled
void InitGraph(void)
{
	//��ʼ������ ����oled������
	DriverInit();
}
//����
void ClearScreen(void)
{
	ClearScreenBuffer(0);
}
//������Ļ ע��˴���ָˢ����Ļ�����������ʱ����
void UpdateScreen(void)
{
	UpdateScreenDisplay();
}

///////////////////////////////////////////////////////////////////////////////////////////////
//��ѡ��Ļ�����д��8λ����
void FillByte(int page,int x,unsigned  char byte)
{
	if(GetFillColor())
		WriteByteBuffer(page,x,ReadByteBuffer(page,x)|byte);
	else
		WriteByteBuffer(page,x,ReadByteBuffer(page,x)&(~byte));
}
//��ѡ��Ļ��������һ������
void FillRect(int x,int y,int width,int height)
{
	int i,j;
	int temp =(y+height-1)/8-y/8;	//��Ҫ���ľ�������Ļ����ռ������ ��Ļ����Ϊ8����
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
			//�������� �������
			FillByte(y/8,i,_BitTableS[(8-y%8)-1]<<(y%8));
			for(j=1;j<temp;j++)
			{
				FillByte(y/8+j,i,0xff);
			}
			FillByte(y/8+temp,i,_BitTableS[(height-1+y)%8]);
		}	
	}
}
//��һ���������Ϊx,y ����Ϊheight������ (��DrawFastHLine()���� ����������ʹ�ô��ʵ��)
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

//��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
//��Ȩ����������ΪCSDN������xtlisk����ԭ�����£���ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https://blog.csdn.net/xtlisk/article/details/51249371

//��x��y��x0��y0��תangle����
float mySqrt(float x)
{
	float a = x;
	unsigned int i = *(unsigned int *)&x;
	i = (i + 0x3f76cf62) >> 1;
	x = *(float *)&i;
	x = (x + a / x) * 0.5;
	return x;
}
//��ƽ��������
unsigned int sqrt_16(unsigned long M)  
{  
    unsigned int N, i;  
    unsigned long tmp, ttp;   // �����ѭ������  
    if (M == 0)               // �����������������ҲΪ0  
        return 0;  
    N = 0;  
    tmp = (M >> 30);          // ��ȡ���λ��B[m-1]  
    M <<= 2;  
    if (tmp > 1)              // ���λΪ1  
    {  
        N ++;                 // �����ǰλΪ1������ΪĬ�ϵ�0  
        tmp -= N;  
    }  
    for (i=15; i>0; i--)      // ��ʣ���15λ  
    {  
        N <<= 1;              // ����һλ  

        tmp <<= 2;  
        tmp += (M >> 30);     // ����  

        ttp = N;  
        ttp = (ttp<<1)+1;  

        M <<= 2;  
        if (tmp >= ttp)       // �������  
        {  
            tmp -= ttp;  
            N ++;  
        }  
    }  
    return N;  
} 

//��Ҫ�Ż�atant2 cos sin�㷨
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

//����:������ת�Ƕ�
void SetAngle(float angle)
{
	_RoateValue.angle=RADIAN(angle);
}
//����:������ת���� 1Ϊ��ʱ�룬0Ϊ˳ʱ��
void SetAnggleDir(int direction)
{
	_RoateValue.direct=direction;
}
//����:������ת���ĵ�
void SetRotateCenter(int x0,int y0)
{
	_RoateValue.center.x=x0;
	_RoateValue.center.y=y0;
}
//����:���ýǶȡ���ת������ת����
void SetRotateValue(int x,int y,float angle,int direct)
{
	SetRotateCenter(x,y);
	SetAnggleDir(direct);
	SetAngle(angle);
}
//����:��һ��������תһ���Ƕ�
//x,y:��Ҫ��ת������
//return����ת�������
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
//��ĳһ�㿪ʼ ��ȡ���Ϸ���ͬ��ɫ�����ص�ĸ���
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
//�����溯��ͬ�� ��ȡ���·���
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
//��һ���㿪ʼ���һ�����ͼ��
//�ײ�˺������������� ����������̫�� �ڴ治����
//����Ч�������޼�ʮ�������
void FloodFill(unsigned char x,unsigned char y,int oldcolor,int newcolor)
{		
	UpdateScreen();
	if(GetPointBuffer(x,y)==oldcolor)//��������ɫ����
	{
		SetPointBuffer(x,y,newcolor);//����������ɫ��Ϊ����ɫ
		//��ʼ����
		FloodFill(x-1,y,oldcolor,newcolor);//�޸��������Χ��4�������ɫ
		FloodFill(x+1,y,oldcolor,newcolor);//�������������ɢ ���귶Χ��������ɫ
		FloodFill(x,y+1,oldcolor,newcolor);
		FloodFill(x,y-1,oldcolor,newcolor);
	}
}
//����:���������һ�����ͼ��
//x,y:�ڷ��ͼ������һ������
//oldcolor:���ͼ���оɵ���ɫ
//newcolor:��������ɫ
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
//����:�̶�֡ˢ��
//OledTimeMs��OledTimeMsFunc()�б�1ms�жϳ������� ����0λ��
//�˺�������whileѭ���� ��������ʱˢ����Ļ
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
//Ӳ����ʱ����
void WaitTimeMs(unsigned int time)
{
	OledTimeMs=time;
	while(OledTimeMs);
}

