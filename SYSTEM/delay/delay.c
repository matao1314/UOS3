#include "delay.h"
#include "sys.h"
#include "os.h" 

////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
//V1.2�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!

//V1.3�޸�˵��
//�����˶�UCOSII��ʱ��֧��.
//���ʹ��ucosII,delay_init���Զ�����SYSTICK��ֵ,ʹ֮��ucos��TICKS_PER_SEC��Ӧ.
//delay_ms��delay_usҲ���������ucos�ĸ���.
//delay_us������ucos��ʹ��,����׼ȷ�Ⱥܸ�,����Ҫ����û��ռ�ö���Ķ�ʱ��.
//delay_ms��ucos��,���Ե���OSTimeDly����,��δ����ucosʱ,������delay_usʵ��,�Ӷ�׼ȷ��ʱ
//����������ʼ������,��������ucos֮��delay_ms������ʱ�ĳ���,ѡ��OSTimeDlyʵ�ֻ���delay_usʵ��.

//V1.4�޸�˵�� 20110929
//�޸���ʹ��ucos,����ucosδ������ʱ��,delay_ms���ж��޷���Ӧ��bug.
//V1.5�޸�˵�� 20120902
//��delay_us����ucos��������ֹ����ucos���delay_us��ִ�У����ܵ��µ���ʱ��׼��
////////////////////////////////////////////////////////////////////////////////// 	 

static u8  fac_us=0;//us��ʱ������			   
static u16 fac_ms=0;//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
//systick�жϷ�����,ʹ��ucosʱ�õ�
void SysTick_Handler(void)
{				   
	OSIntEnter();		//�����ж�
  OSTimeTick();       //����ucos��ʱ�ӷ������               
  OSIntExit();        //���������л����ж�
}
#endif
			   
//��ʼ���ӳٺ���
//��ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init(u8 SYSCLK)
{
#if 0
//#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	u32 reload;
//#endif
 	SysTick->CTRL&=~(1<<2);	//SYSTICKʹ���ⲿʱ��Դ	 
	fac_us=SYSCLK/8;		//�����Ƿ�ʹ��ucos,fac_us����Ҫʹ��
	    
//#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	reload=SYSCLK/8;		//ÿ���ӵļ������� ��λΪK	   
	//reload*=1000000/OS_TICKS_PER_SEC;//����OS_TICKS_PER_SEC�趨���ʱ��
							//reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����	
	//fac_ms=1000/OS_TICKS_PER_SEC;//����ucos������ʱ�����ٵ�λ	   
	SysTick->CTRL|=1<<1;   	//����SYSTICK�ж�
	SysTick->LOAD=reload; 	//ÿ1/OS_TICKS_PER_SEC���ж�һ��	
	SysTick->CTRL|=1<<0;   	//����SYSTICK    
//#else
//	fac_ms=(u16)fac_us*1000;//��ucos��,����ÿ��ms��Ҫ��systickʱ����   
#endif
}								    

//#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{    OS_ERR err;	

#if 0		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	//LOAD��ֵ	    	 
	ticks=nus*fac_us; 			//��Ҫ�Ľ�����	  		 
	tcnt=0;
//	OSSchedLock();				//��ֹucos���ȣ���ֹ���us��ʱ
	told=SysTick->VAL;        	//�ս���ʱ�ļ�����ֵ
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
	#endif
//	OSSchedUnlock();			//����ucos���� 									    
}
//��ʱnms
//nms:Ҫ��ʱ��ms��
void delay_ms(u16 nms)
{
#if 0
    OS_ERR err;	
//	if(OSRunning==TRUE)//���os�Ѿ�������	    
	{		  
		if(nms>=fac_ms)//��ʱ��ʱ�����ucos������ʱ������ 
		{
//   			OSTimeDly(nms/fac_ms);//ucos��ʱ
			 OSTimeDly(  (OS_TICK    )200, 
                   (OS_OPT     )OS_OPT_TIME_DLY, 
                   (OS_ERR     *)&err);
		}
		nms%=fac_ms;			//ucos�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delay_us((u32)(nms*1000));	//��ͨ��ʽ��ʱ 
	#endif
}


			 



































