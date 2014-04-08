#ifndef _bsp_h_
#define _bsp_h_

#include "os.h" 

#include "led.h"
#include "lcd.h"
#include "sdcard.h"
#include "diskio.h"
#include "sd_fs_app.h"
#include "usart.h"
#include "malloc.h"
#include "sdcard.h"
#include "spi.h"
#include "text.h"
#include "fontupd.h"

#include "vs10xx.h"
#include "i2cee.h"
#include "fontupd.h"
#include "text.h"
#include "touch.h" 
#include "sd_fs_app.h"
#include "exfuns.h"
#include "vs10xx.h"
/********************************/
/*       œµÕ≥≈‰÷√∫Ø ˝           */
/********************************/
void IWDG_Init(void);
void SysTick_Init(void);
void BSP_Init(void);
void NVIC_Cfg(void);
#endif
