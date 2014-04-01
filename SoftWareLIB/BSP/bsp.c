#include "stm32f10x.h"
#include "bsp.h"
#include "lcd.h"
#include "usart.h"
#include "delay.h"	

#include "common.h"//Common head file

/*******************************************************************************
函 数 名：void IWDG_Init(void)
功能描述：看门狗初始化						
********************************************************************************/
void IWDG_Init(void)
{
//	IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
//	IWDG_SetPrescaler( IWDG_Prescaler_64);//最小
//	IWDG_SetReload( 0x138);//40KHz内部时钟 (1/40000 * 64 * 0x138 = 0.5s)
//	IWDG_WriteAccessCmd( IWDG_WriteAccess_Disable );
//	IWDG_Enable();
//	IWDG_ReloadCounter();
}
/*
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock/1000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
	//关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/*******************************************************************************
* Function Name :void InterruptOrder(void)
* Description   :中断向量，优先级
*******************************************************************************/
void NVIC_Cfg(void)
{
  #ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
  #else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
  #endif

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

/*******************************************************************************
* Function Name :void SystemConfig(void)
* Description   :系统时间戳 初始化
*******************************************************************************/
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit (void)
{

}
#endif

/*******************************************************************************
* Function Name :void SystemConfig(void)
* Description   :读时间戳 计数值
* Input         :读到的计数值
*******************************************************************************/
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    return (SysTick->VAL);
}
#endif

/*******************************************************************************
* Function Name :void SystemConfig(void)
* Description   :系统初始化
*******************************************************************************/
void BSP_Init(void)
{	
	SystemInit();//Clock72MHZ
  SysTick_Init();
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	NVIC_Cfg();	//中断优先级设置
  //delay_init(72);
  uart_init(72,115200);
	LED_Init();
}


SD_CardInfo   SDCardInfo;        //SD卡信息
SD_Error      SD_USER_Init(void);//SD卡初始化
//SD Card Init
SD_Error SD_USER_Init(void)
{
	SD_Error   Status = SD_OK;
	/* SD Init */
	Status =SD_Init();
	if (Status == SD_OK)
	{
		/* Read CSD/CID MSD registers */
		Status = SD_GetCardInfo( &SDCardInfo );//获得SD卡索引信息
	  printf("SDCardCapacity = %dMB\r\n", SDCardInfo.CardCapacity>>20);
	  printf( " \r\n CardBlockSize %d ", SDCardInfo.CardBlockSize );
	}
	if (Status == SD_OK){
	/* Select Card */
	Status = SD_SelectDeselect( (u32) (SDCardInfo.RCA << 16) );
	}
	if (Status == SD_OK){
	/* set bus wide */
	Status = SD_EnableWideBusOperation( SDIO_BusWide_1b );
	}
	/* Set Device Transfer Mode to DMA */
	if (Status == SD_OK){ 
	/* 任选一种都可以工作 */ 
	//Status = SD_SetDeviceMode( SD_DMA_MODE );
	Status = SD_SetDeviceMode( SD_POLLING_MODE );
	//Status = SD_SetDeviceMode( SD_INTERRUPT_MODE );	
	}
	return Status;
}


