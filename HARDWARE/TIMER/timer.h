#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//ͨ���ı�TIM2->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define LED0_PWM_VAL    TIM2->CCR2
//////////////////////LCD����PWMռ�ձ�����////////////
#define LCD_BLPWM_VAL   TIM5->CCR2 	//LCD PWM��������

void LED_PWM_Init(void);
void TIM3_Int_Init(void);
void LCD_PWM_Init(void);

#endif























