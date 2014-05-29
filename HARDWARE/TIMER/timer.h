#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//通过改变TIM3->CCR2的值来改变占空比，从而控制LED0的亮度
#define LED0_PWM_VAL TIM3->CCR2    

//////////////////////LCD背光PWM占空比设置////////////////////////////////////////
#define LCD_BLPWM_VAL   TIM8->CCR2 	//LCD PWM背光设置

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void TIM6_Int_Init(u16 arr,u16 psc);
void LCD_PWM_Init(void);

#endif























