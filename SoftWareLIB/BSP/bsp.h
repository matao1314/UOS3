#ifndef _bsp_h_
#define _bsp_h_

#include "os.h" 

/********************************/
/*       œµÕ≥≈‰÷√∫Ø ˝           */
/********************************/
void IWDG_Init(void);
void SysTick_Init(void);
void BSP_Init(void);
void NVIC_Cfg(void);
#endif
