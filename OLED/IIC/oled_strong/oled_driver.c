/*
	原作者哔哩哔哩:							MjGame 		https://space.bilibili.com/38673747
	同GifHub:								maoyongjie 	https://github.com/hello-myj/stm32_oled/
	代码整理注释删减增加优化等 哔哩哔哩:	一只程序缘	https://space.bilibili.com/237304109
	整理之前的原代码随本代码一同提供,浏览以上网址获取更多相关信息,本代码以征得原作同意,感谢原作
	
	图形库原理:其实就是对一个数组进行操作,数组操作完成之后,直接将整个
	数组刷新到屏幕上
	因此此c文件用于配置oled底层 用于单片机与oled的直接且唯一通信
	
	移植此图形库主要改变以下内容
	SPI_Configuration()	配置通信引脚
	WriteCmd()			写命令
	WriteDat()			写数据
	OledTimeMsFunc()	oled_config中的函数 为系统提供时基
	此例程仅为SPI通信方式 需要更改其他通信方式改好底层上面3个函数大概就行
*/

#include "oled_driver.h"
//#include "delay.h"
#include "../Delay/Delay.h"
#include "draw_api.h"

extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];

uint8_t OLED_Init_CMD[/*29 + 3*/] =
{
	0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8,
	0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1,
	0xDA, 0x12, 0xDB, 0x30, 0x8D, 0x14, 0xAF, 0x20, 0x00
};

//void SPI_Configuration(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 		//使能A端口时钟
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 		//推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//速度50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_4);	

//	OLED_RST_Set();
//	DelayMs(100);
//	OLED_RST_Clr();
//	DelayMs(200);
//	OLED_RST_Set();
//}

//void OLED_WR_Byte(u8 dat,u8 cmd)
//{	
//	u8 i;			  
//	if(cmd)
//	  OLED_DC_Set();
//	else 
//	  OLED_DC_Clr();		  
//	OLED_CS_Clr();
//	for(i=0;i<8;i++)
//	{			  
//		OLED_SCLK_Clr();
//		if(dat&0x80)
//		   OLED_SDIN_Set();
//		else 
//		   OLED_SDIN_Clr();
//		OLED_SCLK_Set();
//		dat<<=1;   
//	}				 		  
//	OLED_CS_Set();
//	OLED_DC_Set();   	  
//} 

//void WriteCmd(unsigned char cmd)
//{
//	OLED_WR_Byte(cmd,0);
//}

//void WriteDat(unsigned char dat)
//{
//	OLED_WR_Byte(dat,1);
//}

void OLED_FILL(unsigned char BMP[])
{
//	unsigned char i,j;
//	unsigned char *p;
//	p=BMP;

//	for(i=0;i<8;i++)
//	{
//		WriteCmd(0xb0+i);		//page0-page1
//		WriteCmd(0x00);			//low column start address
//		WriteCmd(0x10);	

//		for(j=0;j<128;j++)
//		{
//			WriteDat(*p++);
//		}
//	}
	HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteData_Addr, I2C_MEMADD_SIZE_8BIT, BMP, 1024);
}


void OLED_Init(void)
{
//	WriteCmd(0xAE); //display off
//	WriteCmd(0x20);	//Set Memory Addressing Mode	
//	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
//	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
//	WriteCmd(0xc8);	//Set COM Output Scan Direction
//	WriteCmd(0x00); //---set low column address
//	WriteCmd(0x10); //---set high column address
//	WriteCmd(0x40); //--set start line address
//	WriteCmd(0x81); //--set contrast control register
//	WriteCmd(0xff); //亮度调节 0x00~0xff
//	WriteCmd(0xa1); //--set segment re-map 0 to 127
//	WriteCmd(0xa6); //--set normal display
//	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
//	WriteCmd(0x3F); //
//	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
//	WriteCmd(0xd3); //-set display offset
//	WriteCmd(0x00); //-not offset
//	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
//	WriteCmd(0xf0); //--set divide ratio
//	WriteCmd(0xd9); //--set pre-charge period
//	WriteCmd(0x22); //
//	WriteCmd(0xda); //--set com pins hardware configuration
//	WriteCmd(0x12);
//	WriteCmd(0xdb); //--set vcomh
//	WriteCmd(0x20); //0x20,0.77xVcc
//	WriteCmd(0x8d); //--set DC-DC enable
//	WriteCmd(0x14); //
//	WriteCmd(0xaf); //--turn on oled panel

//	WriteCmd(0x20); 
//	WriteCmd(0x00);

	HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteCom_Addr, I2C_MEMADD_SIZE_8BIT, OLED_Init_CMD, 29);

	OLED_CLS();
}


void OLED_CLS(void)//清屏 全部发送0x00
{
	unsigned char m,n;
	for(m=0;m<SCREEN_PAGE_NUM;m++)
	{
//		WriteCmd(0xb0+m);		//page0-page1
//		WriteCmd(0x00);			//low  column start address
//		WriteCmd(0x10);			//high column start address

		for(n=0;n<SCREEN_COLUMN;n++)
		{
//			WriteDat(0x00);
			ScreenBuffer[m][n] = 0;
		}
	}

	HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteData_Addr, I2C_MEMADD_SIZE_8BIT, ScreenBuffer[0], 1024);
}

//void OLED_ON(void)
//{
////	WriteCmd(0X8D);  //设置电荷泵
////	WriteCmd(0X14);  //开启电荷泵
////	WriteCmd(0XAF);  //OLED唤醒

//	OLED_Init_CMD[29] = 0X8D;
//	OLED_Init_CMD[30] = 0X14;
//	OLED_Init_CMD[31] = 0XAF;

//	HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteData_Addr, I2C_MEMADD_SIZE_8BIT, &OLED_Init_CMD[29], 3);
//}

//void OLED_OFF(void)
//{
////	WriteCmd(0X8D);  //设置电荷泵
////	WriteCmd(0X10);  //关闭电荷泵
////	WriteCmd(0XAE);  //OLED休眠

//	OLED_Init_CMD[29] = 0X8D;
//	OLED_Init_CMD[30] = 0X10;
//	OLED_Init_CMD[31] = 0XAE;

//	HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteData_Addr, I2C_MEMADD_SIZE_8BIT, &OLED_Init_CMD[29], 3);
//}



