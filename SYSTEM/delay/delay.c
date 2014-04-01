#include "delay.h"
#include "os.h" 
static u8  fac_us=0;//us��ʱ������			   
//static u16 fac_ms=0;//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

//void SysTick_Handler(void)�ж���OS_CPU_SysTickHandler
			   
//��ʼ���ӳٺ���
//��ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init(u8 SYSCLK)
{
//	fac_us=SYSCLK/8;		//�����Ƿ�ʹ��ucos,fac_us����Ҫʹ��	
	SysTick->CTRL &=~(1 << 2);  			//systickʹ���ⲿʱ��;
	SysTick->CTRL |= 1 << 1;   				//����systick�ж�;
	SysTick->LOAD = 9000;	   			  	//����1ms�ж�;
	SysTick->CTRL |= 1 << 0;   				//����SYSTICK�ж�; 
}	
							    
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{
  OS_ERR 	d_err;//OS ERR
	u32 ticks;
	u32 told,tnow,tcnt;
	u32 reload=SysTick->LOAD;	//LOAD��ֵ	    	 
	ticks=nus*fac_us; 			//��Ҫ�Ľ�����	  		 
	tcnt=0;
	OSSchedLock((OS_ERR*)&d_err);//��ֹucos���ȣ���ֹ���us��ʱ
	told=SysTick->VAL;        	 //�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}
	OSSchedUnlock((OS_ERR*)&d_err);			//����ucos����
}

//��ʱnms
//nms:Ҫ��ʱ��ms��
void delay_ms(u16 nms)
{
  OS_ERR err;	
	if(OSRunning == OS_STATE_OS_RUNNING)//���os�Ѿ�������	    
	{		  
			 OSTimeDly(  (OS_TICK    )(nms), 
                   (OS_OPT     )OS_OPT_TIME_DLY, 
                   (OS_ERR    *)&err);
	}
}


			 



































