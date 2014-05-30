#include "timer.h"
#include "led.h"
#include "usart.h"
//LED PB3  ����TIME2_CH2
//BL  PD13 TIME5_CH2

//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef         GPIO_InitStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIO�����AFIO���ù���ʱ��ʹ��
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM2, ENABLE);//Timer3������ӳ��  TIM2_CH2->PB3                                                                       	 //����TIM3��CH2�����PWMͨ����LED��ʾ

    //���ø�����Ϊ�����������,���TIM2 CH2��PWM���岨��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���

    TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
}

//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig( TIM3, TIM_IT_Update | TIM_IT_Trigger, ENABLE); //ʹ�ܶ�ʱ��6���´����ж�

    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//LCD ����PWM�����ʼ��
//��ʼ���������Ϊ:PWM����Ƶ��Ϊ80Khz
//ͨ��LCD_BLPWM_VAL����LCD��������.
//0,�;250,�.
void LCD_PWM_Init(void)
{
    //�˲������ֶ��޸�IO������
    RCC->APB2ENR |= 1 << 13; 	//TIM8ʱ��ʹ��
    RCC->APB2ENR |= 1 << 3;    	//ʹ��PORTBʱ��

    GPIOD->CRH &= 0XFF0FFFFF;	//PD13���
    GPIOD->CRH |= 0X00B00000;	//���ù������
    GPIOD->ODR |= 1 << 5;		//PD13����

    TIM5->ARR = 110;		//�趨�������Զ���װֵΪ110.Ƶ��Ϊ654Khz
    TIM5->PSC = 0;			//Ԥ��Ƶ������Ƶ

    TIM5->CCMR1 |= 7 << 12; 	//CH2 PWM2ģʽ
    TIM5->CCMR1 |= 1 << 11; 	//CH2Ԥװ��ʹ��

    TIM5->CCER |= 1 << 6;   	//OC2�������ʹ��
    TIM5->CCER |= 1 << 7;   	//OC2N�͵�ƽ��Ч
    TIM5->BDTR |= 1 << 15;   	//MOE�����ʹ��

    TIM5->CR1 = 0x0080;   	//ARPEʹ��
    TIM5->CR1 |= 0x01;    	//ʹ�ܶ�ʱ��8
}

