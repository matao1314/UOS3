#include "stm32f10x.h"
#include "bsp.h"
#include "lcd.h"
#include "usart.h"
#include "delay.h"	

#include "common.h"//Common head file

/*******************************************************************************
�� �� ����void IWDG_Init(void)
�������������Ź���ʼ��						
********************************************************************************/
void IWDG_Init(void)
{
//	IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
//	IWDG_SetPrescaler( IWDG_Prescaler_64);//��С
//	IWDG_SetReload( 0x138);//40KHz�ڲ�ʱ�� (1/40000 * 64 * 0x138 = 0.5s)
//	IWDG_WriteAccessCmd( IWDG_WriteAccess_Disable );
//	IWDG_Enable();
//	IWDG_ReloadCounter();
}
/*
 * ��������SysTick_Init
 * ����  ������ϵͳ�δ�ʱ�� SysTick
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock/1000))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
	//�رյδ�ʱ��  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/*******************************************************************************
* Function Name :void InterruptOrder(void)
* Description   :�ж����������ȼ�
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
* Description   :ϵͳʱ��� ��ʼ��
*******************************************************************************/
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit (void)
{

}
#endif

/*******************************************************************************
* Function Name :void SystemConfig(void)
* Description   :��ʱ��� ����ֵ
* Input         :�����ļ���ֵ
*******************************************************************************/
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    return (SysTick->VAL);
}
#endif

/*******************************************************************************
* Function Name :void SystemConfig(void)
* Description   :ϵͳ��ʼ��
*******************************************************************************/
void BSP_Init(void)
{	
	SystemInit();//Clock72MHZ
  SysTick_Init();
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	NVIC_Cfg();	//�ж����ȼ�����
  //delay_init(72);
  uart_init(72,115200);
	LED_Init();
}


SD_CardInfo   SDCardInfo;        //SD����Ϣ
SD_Error      SD_USER_Init(void);//SD����ʼ��
//SD Card Init
SD_Error SD_USER_Init(void)
{
	SD_Error   Status = SD_OK;
	/* SD Init */
	Status =SD_Init();
	if (Status == SD_OK)
	{
		/* Read CSD/CID MSD registers */
		Status = SD_GetCardInfo( &SDCardInfo );//���SD��������Ϣ
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
	/* ��ѡһ�ֶ����Թ��� */ 
	//Status = SD_SetDeviceMode( SD_DMA_MODE );
	Status = SD_SetDeviceMode( SD_POLLING_MODE );
	//Status = SD_SetDeviceMode( SD_INTERRUPT_MODE );	
	}
	return Status;
}


