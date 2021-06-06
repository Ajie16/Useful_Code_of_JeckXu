#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx_hal.h"
#define USE_HAL_TIME //OR USE_FREERTOS_TIME

#ifdef USE_HAL_TIME
#define delay_ms(ms) HAL_Delay(ms)
#endif
#ifdef USE_FREERTOS_TIME
#define delay_ms(ms) os_delay(ms)
#endif


	
#endif
