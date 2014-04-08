/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "bsp.h"

#include "common.h"//Common head file
static OS_TCB Usart_Task_TCB;
static OS_TCB Main_Task_TCB;
static OS_TCB AppTaskLEDB_TCB;
static OS_TCB AppTaskADC_TCB;
static OS_TCB Start_Task_TCB;
/////////////////////////UCOSIII任务设置///////////////////////////////////
/* task priority */
#define START_TASK_PRIO         10 //开始任务的优先级设置为最低
#define USART_TASK_PRIO       	7 
#define WATCH_TASK_PRIO       	3 
#define MUSIC_PLAY_TASK_PRIO    2 
#define MAIN_TASK_PRIO          6 
/* task stack size */
#define START_STK_SIZE  	      64
#define USART_STK_SIZE      		64
#define MAIN_STK_SIZE  	  	    512
#define WATCH_STK_SIZE      		128
#define MUSIC_PLAY_STK_SIZE     256
__align(8) static CPU_STK MUSIC_PLAY_TASK_STK[MUSIC_PLAY_STK_SIZE];
__align(8) static CPU_STK START_TASK_STK[START_STK_SIZE];
__align(8) static CPU_STK USART_TASK_STK[USART_STK_SIZE];
__align(8) static CPU_STK MAIN_TASK_STK[MAIN_STK_SIZE];
__align(8) static CPU_STK WATCH_TASK_STK[WATCH_STK_SIZE];

/* task function prototype*/
void start_task(void *pdata);	
void Usart_Task(void *pdata);
void main_task(void *pdata);
void watch_task(void *pdata);
void music_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////	 
static void Main_Task(void *p_arg)
{
	OS_ERR 		err;
	OSTaskCreate(   (OS_TCB     *)&Usart_Task_TCB,
	            (CPU_CHAR   *)"Usart_Task",
	            (OS_TASK_PTR)Usart_Task,
	            (void       *)0,
	            (OS_PRIO    )USART_TASK_PRIO,
	            (CPU_STK    *)&USART_TASK_STK[0],
	            (CPU_STK_SIZE)USART_STK_SIZE / 10,
	            (CPU_STK_SIZE)USART_STK_SIZE,
	            (OS_MSG_QTY )0,
	            (OS_TICK    )0,
	            (void       *)0,
	            (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
	            (OS_ERR     *)&err);
	
//    OSTaskCreate(   (OS_TCB     *)&task1TCB,
//                    (CPU_CHAR   *)"Task1",
//                    (OS_TASK_PTR)Task1,
//                    (void       *)0,
//                    (OS_PRIO    )9,
//                    (CPU_STK    *)&task1_stk[0],
//                    (CPU_STK_SIZE)100 / 10,
//                    (CPU_STK_SIZE)100,
//                    (OS_MSG_QTY )0,
//                    (OS_TICK    )0,
//                    (void       *)0,
//                    (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
//                    (OS_ERR     *)&err);
//   
//		   
//    OSSemCreate(    (OS_SEM     *)&taskSem, 
//                    (CPU_CHAR   *)"taskSem", 
//                    (OS_SEM_CTR )0, 
//                    (OS_ERR     *)err);
//    
//    OSTaskDel(      (OS_TCB     *)&taskStartTCB, 
//                    (OS_ERR     *)&err);
}
void start_task(void *pdata)
{}	

static CPU_INT32U AppCPU_ClkFreq_Hz;

CPU_INT32U BSP_CPU_ClkFreq(void)
{
  RCC_ClocksTypeDef  RCC_Clocks;  
  RCC_GetClocksFreq(&RCC_Clocks);  
  return((CPU_INT32U)RCC_Clocks.HCLK_Frequency);
}

//Main Process
int main(void)
{	
  OS_ERR err;

//  AppCPU_ClkFreq_Hz = BSP_CPU_ClkFreq();
//  cnts = AppCPU_ClkFreq_Hz/(CPU_INT32U)OSCfg_TickRate_Hz;
//  OS_CPU_SysTickInit(cnts);
	 	
    BSP_Init();//Init system
    CPU_Init();
    OSInit(&err);/* Init uC/OS-III.*/

    OSTaskCreate(   (OS_TCB     *)&Start_Task_TCB,/* Create the start task*/
                    (CPU_CHAR   *)"Task Start",
                    (OS_TASK_PTR)start_task,
                    (void       *)0,
                    (OS_PRIO    ) START_TASK_PRIO,
                    (CPU_STK    *)&START_TASK_STK[0],
                    (CPU_STK_SIZE)START_STK_SIZE/ 10,
                    (CPU_STK_SIZE)START_STK_SIZE,
                    (OS_MSG_QTY )0,
                    (OS_TICK    )0,
                    (void       *)0,
                    (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
                    (OS_ERR     *)&err);       
    OSStart(&err);/* Start multitasking (i.e. give control to uC/OS-III). */ 
}


//执行最不需要时效性的代码
void Usart_Task(void *pdata)
{	   
    CPU_SR cpu_sr=0;
	pdata=pdata;//fix compile warning
	while(1)
	{			  
		delay_ms(1000);	 
		OS_CRITICAL_ENTER();//进入临界区(无法被中断打断) 
		printf("insram:%d,exsram:%d\r\n",mem_perused(0),mem_perused(1));//打印内存占用率
		OS_CRITICAL_EXIT();	//退出临界区(可以被中断打断)
	}
}
