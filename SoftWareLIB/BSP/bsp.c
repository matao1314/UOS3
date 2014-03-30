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
�� �� ����void IWDG_Init(void)
�������������Ź���ʼ��						
********************************************************************************/
void IWDG_Init(void)
{
	IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
	IWDG_SetPrescaler( IWDG_Prescaler_64);//��С
	IWDG_SetReload( 0x138);//40KHz�ڲ�ʱ�� (1/40000 * 64 * 0x138 = 0.5s)
	IWDG_WriteAccessCmd( IWDG_WriteAccess_Disable );
	IWDG_Enable();
	IWDG_ReloadCounter();
}

/*******************************************************************************
* Function Name :void SysTickInit(void)
* Description   :ϵͳ��ʱ��ʱ������
* Other         :ʱ��Ϊ1ms
*******************************************************************************/
void SysTickInit(void)
{
	SysTick_Config(SystemCoreClock/1000);			//uCOSʱ��1ms
}

/*******************************************************************************
* Function Name :void InterruptOrder(void)
* Description   :�ж����������ȼ�
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);//���ȼ�����  ȫΪ��ռʽ���ȼ�
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
* Input         :
* Output        :
* Other         :
* Date          :2011.10.27  13:14:59
*******************************************************************************/
void BspInit(void)
{
  //SysTickInit();
	NVIC_Configuration();	//�ж����ȼ�����
  delay_init(72);
  uart_init(72,9600);
	LED_Init();
}


SD_CardInfo   SDCardInfo;        //SD����Ϣ
SD_Error      SD_USER_Init(void);//SD����ʼ��

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


