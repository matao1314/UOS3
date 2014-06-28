#include "timer.h"
#include "led.h"
#include "usart.h"
//LED PB3  复用TIME2_CH2
//BL  PA1 TIME5_CH2
//TIM3 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void LED_PWM_Init(void)
{
    GPIO_InitTypeDef         GPIO_InitStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //使能GPIO外设和AFIO复用功能时钟使能
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);//Timer2部分重映射  TIM2_CH2->PB3                                                                       	 //用于TIM3的CH2输出的PWM通过该LED显示

    //设置该引脚为复用输出功能,输出TIM2 CH2的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = 900; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器

    TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIMx在ARR上的预装载寄存器
    TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
}

static u16 LCD_BL_time;
static u8  CloseScreenTime=0;
//TIM3中断
#if 0
void TIM3_IRQHandler(void)
{
    static u8 dir = 0;
    static u16 pwmval = 0;
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
			  //For Breath LED
        if(dir) {//增加OR减少
            pwmval++;
        } else {
            pwmval--;
        }
        if(pwmval > 900) {//改变计数方向
            dir = 0;
        }
        if(pwmval == 0) {
            dir = 1;
        }
        LED0_PWM_VAL = pwmval;//更新LED
				//For LCD BackLight
				LCD_BL_time++;
        if(CloseScreenTime<6){
				   if(LCD_BL_time>10000){					 
						 CloseScreenTime++;
					   LCD_BL_time=0;
					   LCD_BLPWM_VAL = 700;//LCD背光亮度减半
				   }			
			  }else{
					 LCD_BLPWM_VAL = 900;//关掉LCD背光
				}
				
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );
    }
}
#endif
//APB2=72MHz,APB1=36MHz
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
    TIM_TimeBaseStructure.TIM_Period = 900; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler = 100; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
    TIM_ITConfig( TIM3, TIM_IT_Update | TIM_IT_Trigger, ENABLE); //使能定时器更新触发中断
    TIM_Cmd(TIM3, ENABLE);  //使能TIM外设

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

//LCD 背光PWM输出初始化
//初始化背光参数为:PWM控制频率为80Khz
//通过LCD_BLPWM_VAL设置LCD背光亮度.
//0,最暗;250,最暗.
void LCD_PWM_Init(void)
{
    GPIO_InitTypeDef         GPIO_InitStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); //使能GPIO外设和AFIO复用功能时钟使能
    //设置该引脚为复用输出功能,输出TIM2 CH2的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = 900; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器

    TIM_ARRPreloadConfig(TIM5, ENABLE); //使能TIMx在ARR上的预装载寄存器
    TIM_Cmd(TIM5, ENABLE);  //使能TIMx外设
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
		LCD_BLPWM_VAL = 0;
		LCD_BL_time=0;
		CloseScreenTime=0;
    EXTI_ClearITPendingBit(EXTI_Line1);    
  }  
}
