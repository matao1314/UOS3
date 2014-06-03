#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//通过改变TIM2->CCR2的值来改变占空比，从而控制LED0的亮度
#define LED0_PWM_VAL    TIM2->CCR2
//////////////////////LCD背光PWM占空比设置////////////
#define LCD_BLPWM_VAL   TIM5->CCR2 	//LCD PWM背光设置

void LED_PWM_Init(void);
void TIM3_Int_Init(void);
void LCD_PWM_Init(void);

#endif























