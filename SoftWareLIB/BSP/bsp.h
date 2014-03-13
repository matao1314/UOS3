#ifndef _bsp_h_
#define _bsp_h_

#include "os.h" 

/********************************/
/*       œµÕ≥≈‰÷√∫Ø ˝           */
/********************************/
#define LED_0 0
#define LED_1 1
#define LED_2 2
#define LED_3 3
#define LED_4 4
#define LED_5 5


void Delay(volatile CPU_INT32U nCount);
void IWDG_Init(void);
void SysTickInit(void);
void BspInit(void);
void led_init(void);
void led_on(CPU_INT32U n);
void led_off(CPU_INT32U n);

#endif
