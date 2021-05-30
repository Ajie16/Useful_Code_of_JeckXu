#ifndef __OLED_DRIVER_H
#define	__OLED_DRIVER_H

//#include "stm32f10x.h"
#include "main.h"
#include "oled_config.h"
#include "oled_basic.h"

extern I2C_HandleTypeDef hi2c1;
#define Scr12864_HI2C hi2c1

#define OLED_ADDRESS 0x78
#define OLED_WriteCom_Addr	0x00	
#define OLED_WriteData_Addr	0x40	

//#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_4)	//CLK
//#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_4)

//#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)	//DIN
//#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

//#define OLED_RST_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)		//RES
//#define OLED_RST_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)

//#define OLED_DC_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)		//DC
//#define OLED_DC_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)
// 		     
//#define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_8)		//CS
//#define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_8)

//#define OLED_CMD  0	//Ð´ÃüÁî
//#define OLED_DATA 1	//Ð´Êý¾Ý

//void I2C_Configuration(void);
//void I2C_WriteByte(uint8_t addr,uint8_t data);
//void SPI_Configuration(void);
//void SPI_WriterByte(unsigned char dat);
//void WriteCmd(unsigned char cmd);
//void WriteDat(unsigned char Dat);
void OLED_Init(void);
void OLED_CLS(void);
//void OLED_ON(void);
//void OLED_OFF(void);
void OLED_FILL(unsigned char BMP[]);

#endif

