#ifndef OLED_CONFIG_H
#define OLED_CONFIG_H
#include "oled_basic.h"


//定义屏幕基本状况
//保持了可拓展性 如果换用其他类型屏
//因注意其他配套c文件中用了这些宏定义的部分

#define   	OLED_12864						//屏幕类型
#define 	SCREEN_PAGE_NUM			(8)		//总行数 (大行)
#define  	SCREEN_PAGEDATA_NUM   	(128)	//每大行的列数
#define  	SCREEN_ROW 				(64)	//总行数
#define 	SCREEN_COLUMN 			(128)	//总列数

void OledTimeMsFunc(void);

#endif

