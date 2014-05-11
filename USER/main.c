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
static OS_TCB Music_Task_TCB;
/////////////////////////UCOSIII任务设置///////////////////////////////////
/* task priority */
#define START_TASK_PRIO         9 //开始任务的优先级设置为最低
#define USART_TASK_PRIO       	7 
#define WATCH_TASK_PRIO       	5 
#define MAIN_TASK_PRIO          4 
#define MUSIC_TASK_PRIO         3 
/* task stack size */
#define START_STK_SIZE  	      128//注意栈溢出
#define USART_STK_SIZE      		64
#define MAIN_STK_SIZE  	  	    512
#define WATCH_STK_SIZE      		128
#define MUSIC_STK_SIZE          512
__align(8) static CPU_STK START_TASK_STK[START_STK_SIZE];
__align(8) static CPU_STK USART_TASK_STK[USART_STK_SIZE];
__align(8) static CPU_STK MAIN_TASK_STK[MAIN_STK_SIZE];
__align(8) static CPU_STK WATCH_TASK_STK[WATCH_STK_SIZE];
__align(8) static CPU_STK MUSIC_TASK_STK[MUSIC_STK_SIZE];

/* task function prototype*/
void Start_Task(void *pdata);	
void Usart_Task(void *pdata);
void Main_Task(void *pdata);
void Watch_Task(void *pdata);
void music_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////	 
void Start_Task(void *pdata)
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
/***********************"Music_Task"***********************************************/
	OSTaskCreate((OS_TCB     *)&Music_Task_TCB,
	            (CPU_CHAR   *)"Music_Task",
	            (OS_TASK_PTR)music_task,
	            (void       *)0,
	            (OS_PRIO    )MUSIC_TASK_PRIO,
	            (CPU_STK    *)&MUSIC_TASK_STK[0],
	            (CPU_STK_SIZE)MUSIC_STK_SIZE / 10,
	            (CPU_STK_SIZE)MUSIC_STK_SIZE,
	            (OS_MSG_QTY )0,
	            (OS_TICK    )0,
	            (void       *)0,
	            (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
	            (OS_ERR     *)&err);							
/***********************Watch_Task**********************************************/
	OSTaskCreate((OS_TCB     *)&Watch_Task_TCB,
	            (CPU_CHAR   *)"Watch_Task",
	            (OS_TASK_PTR)Watch_Task,
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
	//OSTaskSuspend(&Start_Task_TCB,&err);//挂起Start任务
	OS_CRITICAL_EXIT();//退出临界区
	OSTaskDel((OS_TCB     *)&Start_Task_TCB, 
            (OS_ERR     *)&err);
}	

//Main Process
int main(void)
{	
    OS_ERR err;
    BSP_Init();//Init system
    CPU_Init();
    OSInit(&err);/* Init uC/OS-III.*/
    OSTaskCreate(   (OS_TCB     *)&Start_Task_TCB,/* Create the start task*/
                    (CPU_CHAR   *)"Task Start",
                    (OS_TASK_PTR)Start_Task,
                    (void       *)0,
                    (OS_PRIO     )START_TASK_PRIO,
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
   u8 selx;
	 u8 keyval; 
	 Draw_mainPage();	  
	while(1){
		 keyval = KEY_Scan(0);	 
		 selx = icon_press_chk();
	 	 switch(selx){
			case 0:picviewer_play();break;
			case 1:mp3_play();break;
			//case 2:calendar_play();break;
			default:delay_ms(1000/OSCfg_TickRate_Hz);break;
		 }	 	 		  
	 }
}

//监视任务
void Watch_Task(void *pdata)
{
	CPU_SR cpu_sr=0;
	pdata=pdata;//avoid compile warning
	while(1){
		//calendar_play();	
		delay_ms(500);	 
		
	}
}
//执行最不需要时效性的代码
void Usart_Task(void *pdata)
{	   
	CPU_SR cpu_sr=0;
	pdata=pdata;//avoid compile warning
	while(1){
		LED0=0;
		TEST=0;
		delay_ms(500);	 
		LED0=1;
		TEST=1;
		delay_ms(500);	 
		OS_CRITICAL_ENTER();//进入临界区(无法被中断打断) 
		printf("System Sram Use rate:%d%%\r\n",mem_perused(0));//打印内存占用率
		OS_CRITICAL_EXIT();	//退出临界区(可以被中断打断)
	}
}
