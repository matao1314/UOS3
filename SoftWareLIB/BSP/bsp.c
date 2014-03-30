#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_iwdg.h"
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
	IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
	IWDG_SetPrescaler( IWDG_Prescaler_64);//最小
	IWDG_SetReload( 0x138);//40KHz内部时钟 (1/40000 * 64 * 0x138 = 0.5s)
	IWDG_WriteAccessCmd( IWDG_WriteAccess_Disable );
	IWDG_Enable();
	IWDG_ReloadCounter();
}

/*******************************************************************************
* Function Name :void SysTickInit(void)
* Description   :系统定时器时间配置
* Other         :时基为1ms
*******************************************************************************/
void SysTickInit(void)
{
	SysTick_Config(SystemCoreClock/1000);			//uCOS时基1ms
}

/*******************************************************************************
* Function Name :void InterruptOrder(void)
* Description   :中断向量，优先级
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);//优先级设置  全为抢占式优先级
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
* Input         :
* Output        :
* Other         :
* Date          :2011.10.27  13:14:59
*******************************************************************************/
void BspInit(void)
{
  //SysTickInit();
	NVIC_Configuration();	//中断优先级设置
  delay_init(72);
  uart_init(72,9600);
	LED_Init();
}


SD_CardInfo   SDCardInfo;        //SD卡信息
SD_Error      SD_USER_Init(void);//SD卡初始化

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


