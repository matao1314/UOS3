/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "bsp.h"

#include "common.h"//Common head file

static OS_TCB taskStartTCB;
static CPU_STK taskStartStk[STARTUP_TASK_STK_SIZE]; 		//启动任务的程序空间

static OS_TCB task1TCB;

static CPU_STK task1_stk[TASK1_STK_SIZE];

static volatile OS_SEM taskSem;


static void Task1(void *p_arg)
{
    OS_ERR err;
    LCD_Init(); 

    while (1)
    {
        LED0=1;
				TSET=1;
				LCD_Clear(RED);
			//	printf("Task11111111111111 Runing\r\n");
        OSTimeDly(  (OS_TICK    )1, 
                    (OS_OPT     )OS_OPT_TIME_DLY, 
                    (OS_ERR     *)&err);  
delay_ms(1000);
				LCD_Clear(GREEN);
     
				LED0=0;
				TSET=0;
        OSTimeDly(  (OS_TICK    )1, 
                    (OS_OPT     )OS_OPT_TIME_DLY, 
                    (OS_ERR     *)&err);
delay_ms(1000);
//        OSSemPost(  (OS_SEM     *)&taskSem, 
//                    (OS_OPT     )OS_OPT_POST_ALL, 
//                    (OS_ERR     *)&err);
    }
}



static void TaskStart(void)
{
    OS_ERR 		err;
    SysTickInit();
    OSTaskCreate(   (OS_TCB     *)&task1TCB,
                    (CPU_CHAR   *)"Task1",
                    (OS_TASK_PTR)Task1,
                    (void       *)0,
                    (OS_PRIO    )TASK1_PRIO,
                    (CPU_STK    *)&task1_stk[0],
                    (CPU_STK_SIZE)TASK1_STK_SIZE / 10,
                    (CPU_STK_SIZE)TASK1_STK_SIZE,
                    (OS_MSG_QTY )0,
                    (OS_TICK    )0,
                    (void       *)0,
                    (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
                    (OS_ERR     *)&err);
   
		   
    OSSemCreate(    (OS_SEM     *)&taskSem, 
                    (CPU_CHAR   *)"taskSem", 
                    (OS_SEM_CTR )0, 
                    (OS_ERR     *)err);
    
    OSTaskDel(      (OS_TCB     *)&taskStartTCB, 
                    (OS_ERR     *)&err);
}


void KernelMain(void)
{
    OS_ERR err;

    CPU_Init();
    OSInit(         (OS_ERR	    *)&err);

    OSTaskCreate(   (OS_TCB     *)&taskStartTCB,
                    (CPU_CHAR   *)"Task Start",
                    (OS_TASK_PTR)TaskStart,
                    (void       *)0,
                    (OS_PRIO    ) STARTUP_TASK_PRIO,
                    (CPU_STK    *)&taskStartStk[0],
                    (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE / 10,
                    (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,
                    (OS_MSG_QTY )0,
                    (OS_TICK    )0,
                    (void       *)0,
                    (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
                    (OS_ERR     *)&err);    
    
    OSStart(        (OS_ERR	    *)&err);
}

//Main Process
int main()
{	 	
	BspInit();//Init system
  KernelMain();	
	return 0;
}
