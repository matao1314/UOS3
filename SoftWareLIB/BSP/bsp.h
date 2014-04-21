#ifndef _bsp_h_
#define _bsp_h_

#include "os.h"
#include "os_cpu.h" 
#include "usart.h"
#include "delay.h"

#include "led.h"
#include "key.h"
#include "lcd.h"
#include "spi.h"
#include "sdcard.h"
#include "diskio.h"
#include "usart.h"
#include "malloc.h"
#include "sdcard.h"
#include "text.h"
#include "fontupd.h"
#include "common.h"
#include "i2cee.h"
#include "fontupd.h"
#include "touch.h" 
#include "sd_fs_app.h"
#include "exfuns.h"
#include "vs10xx.h"

#include "guix.h"
#include "piclib.h"
#include "fattester.h"
#include "exfuns.h"

#include "appui.h"
#include "appcom.h"



/********************************/
/*       œµÕ≥≈‰÷√∫Ø ˝           */
/********************************/
void IWDG_Init(void);
void SysTick_Init(void);
void BSP_Init(void);
void NVIC_Cfg(void);
#endif
