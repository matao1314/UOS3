#include "delay.h"
#include "os.h"
static u8  fac_us = 0; //us延时倍乘数
static u16 fac_ms = 0; //ms延时倍乘数,在ucos下,代表每个节拍的ms数

/*------------------------NOTICE-----------------------------------*/
/* 在初始化的时候，SYSTICK 不能开启中断，外部函数不能调用操作系统函数，
否则会引起hardfault error
*/


//初始化延迟函数
//当使用ucos的时候,此函数会初始化ucos的时钟节拍
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init(u8 SYSCLK)
{
    fac_us = SYSCLK / 8;		//不论是否使用ucos,fac_us都需要使用
    SysTick->CTRL &= ~(1 << 2); //systick使用外部时钟;
    //SysTick->CTRL |= 1 << 1;  //开启systick中断;
    SysTick->LOAD = fac_us * (1000000 / OSCfg_TickRate_Hz); //产生1ms中断;
    SysTick->CTRL |= 1 << 0;   	//开启SYSTICK中断;
    fac_ms = 1000 / OSCfg_TickRate_Hz; //代表ucos可以延时的最少单位
}

//延时nus
//nus为要延时的us数.
void delay_us(u32 nus)
{
    OS_ERR 	d_err;
    u32 ticks;
    u32 told, tnow, tcnt;
    u32 reload = SysTick->LOAD;	//LOAD的值
    ticks = nus * fac_us; 			//需要的节拍数
    tcnt = 0;
    OSSchedLock((OS_ERR *)&d_err); //阻止ucos调度，防止打断us延时
    told = SysTick->VAL;        	 //刚进入时的计数器值
    while(1) {
        tnow = SysTick->VAL;
        if(tnow != told) {
            if(tnow < told) {
                tcnt += told - tnow;    //这里注意一下SYSTICK是一个递减的计数器就可以了.
            } else {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if(tcnt >= ticks) {
                break;    //时间超过/等于要延迟的时间,则退出.
            }
        }
    }
    OSSchedUnlock((OS_ERR *)&d_err);//开启ucos调度
}

//延时nms
//nms:要延时的ms数
void delay_ms(u16 nms)
{
    OS_ERR err;
    if(OSRunning == OS_STATE_OS_RUNNING) { //如果os已经在跑了
        if(nms >= fac_ms) { //延时的时间大于ucos的最少时间周期
            OSTimeDly((OS_TICK)(nms / fac_ms),
                      (OS_OPT)OS_OPT_TIME_DLY,
                      (OS_ERR *)&err);
        }
        nms %= fac_ms;
    }
    delay_us((u32)(nms * 1000)); //普通方式延时
}




































