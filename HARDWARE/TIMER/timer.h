#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//ͨ���ı�TIM2->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define LED0_PWM_VAL    TIM2->CCR2
//////////////////////LCD����PWMռ�ձ�����////////////
#define LCD_BLPWM_VAL   TIM5->CCR2 	//LCD PWM��������

void TIM2_PWM_Init(u16 arr, u16 psc);
void TIM3_Int_Init(u16 arr, u16 psc);
void LCD_PWM_Init(void);

#endif























