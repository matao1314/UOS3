/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "bsp.h"
static OS_TCB Usart_Task_TCB;
static OS_TCB Main_Task_TCB;
static OS_TCB Start_Task_TCB;
static OS_TCB Watch_Task_TCB;

/////////////////////////UCOSIII任务设置///////////////////////////////////
/* task priority */
#define START_TASK_PRIO         10 //开始任务的优先级设置为最低
#define USART_TASK_PRIO       	5 
#define MAIN_TASK_PRIO          4 
#define WATCH_TASK_PRIO       	3 
#define MUSIC_TASK_PRIO         2 
/* task stack size */
#define START_STK_SIZE  	      1024//注意栈溢出
#define USART_STK_SIZE      		256
#define MAIN_STK_SIZE  	  	    256
#define WATCH_STK_SIZE      		256
#define MUSIC_PLAY_STK_SIZE     256
//__align(8) static CPU_STK MUSIC_PLAY_TASK_STK[MUSIC_PLAY_STK_SIZE];
__align(8) static CPU_STK START_TASK_STK[START_STK_SIZE];
__align(8) static CPU_STK USART_TASK_STK[USART_STK_SIZE];
__align(8) static CPU_STK MAIN_TASK_STK[MAIN_STK_SIZE];
__align(8) static CPU_STK WATCH_TASK_STK[WATCH_STK_SIZE];

/* task function prototype*/
void start_task(void *pdata);	
void Usart_Task(void *pdata);
void Main_Task(void *pdata);
void watch_task(void *pdata);
void music_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////	 
void start_task(void *pdata)
{
  OS_ERR   err;
	CPU_SR   cpu_sr=0;
  OS_CRITICAL_ENTER();//进入临界区
/***********************"Main_Task"***********************************************/
	OSTaskCreate((OS_TCB     *)&Main_Task_TCB,
	            (CPU_CHAR   *)"Main_Task",
	            (OS_TASK_PTR)Main_Task,
	            (void       *)0,
	            (OS_PRIO    )MAIN_TASK_PRIO,
	            (CPU_STK    *)&MAIN_TASK_STK[0],
	            (CPU_STK_SIZE)MAIN_STK_SIZE / 10,
	            (CPU_STK_SIZE)MAIN_STK_SIZE,
	            (OS_MSG_QTY )0,
	            (OS_TICK    )0,
	            (void       *)0,
	            (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
	            (OS_ERR     *)&err);
/***********************Watch_Task**********************************************/
	OSTaskCreate((OS_TCB     *)&Watch_Task_TCB,
	            (CPU_CHAR   *)"Watch_Task",
	            (OS_TASK_PTR)watch_task,
	            (void       *)0,
	            (OS_PRIO    )WATCH_TASK_PRIO,
	            (CPU_STK    *)&WATCH_TASK_STK[0],
	            (CPU_STK_SIZE)WATCH_STK_SIZE / 10,
	            (CPU_STK_SIZE)WATCH_STK_SIZE,
	            (OS_MSG_QTY )0,
	            (OS_TICK    )0,
	            (void       *)0,
	            (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
	            (OS_ERR     *)&err);
/***********************"Usart_Task"***********************************************/
#if 0
	OSTaskCreate((OS_TCB     *)&Usart_Task_TCB,
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
	#endif
	OSTaskSuspend(&Start_Task_TCB,&err);//挂起Start任务
	OS_CRITICAL_EXIT();//退出临界区
}	

//Main Process
int main(void)
{	
    OS_ERR err;
    BSP_Init();//Init system
	printf("System OS Init !\r\n");	
    CPU_Init();
    OSInit(&err);/* Init uC/OS-III.*/
	printf("System Start Task Running!\r\n");	
    OSTaskCreate(   (OS_TCB     *)&Start_Task_TCB,/* Create the start task*/
                    (CPU_CHAR   *)"Task Start",
                    (OS_TASK_PTR)start_task,
                    (void       *)0,
                    (OS_PRIO    ) START_TASK_PRIO,
                    (CPU_STK    *)&START_TASK_STK[0],
                    (CPU_STK_SIZE)START_STK_SIZE/10,
                    (CPU_STK_SIZE)START_STK_SIZE,
                    (OS_MSG_QTY )0,
                    (OS_TICK    )0,
                    (void       *)0,
                    (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
                    (OS_ERR     *)&err);       
    OSStart(&err);/* Start multitasking (i.e. give control to uC/OS-III). */ 
}

void Main_Task(void *p_arg)
{

while(1){

	printf("Main_Task Running!\r\n");
	delay_ms(500);	 
	printf("Main_Task Over!\r\n");
}
}

//监视任务
void watch_task(void *pdata)
{
	pdata=pdata;//fix compile warning
	while(1){		
	printf("watch_task Running!\r\n");
		LED0=0;
		TEST=0;
		delay_ms(500);	 
		LED0=1;
		TEST=1;
		delay_ms(500);	 
	printf("watch_task Over!\r\n");
	}
}
//执行最不需要时效性的代码
void Usart_Task(void *pdata)
{	   
	CPU_SR cpu_sr=0;
	pdata=pdata;//fix compile warning
	while(1)
	{
	printf("Usart_Task Running!\r\n");
	//	LED0=0;
		delay_ms(500);	 
//		LED0=1;
//		delay_ms(500);	 
		//OS_CRITICAL_ENTER();//进入临界区(无法被中断打断) 
		//printf("insram:%d,exsram:%d\r\n",mem_perused(0),mem_perused(1));//打印内存占用率
		//OS_CRITICAL_EXIT();	//退出临界区(可以被中断打断)
	printf("Usart_Task Over!\r\n");
	}
}
