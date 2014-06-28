/**
  ******************************************************************************
  * @file    mass storage.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  *****************************************************************************/
#include "storage.h"
#include "hw_config.h" 
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_prop.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);
uint8_t DeviceState;
uint8_t DeviceStatus[6];
uint32_t JumpAddress;
pFunction Jump_To_Application;


/*******************************************************************************
* Function Name  : void DFU_Init(void) 
* Description    : This function is DFU init.
* Input          : None
* Return         : None
*******************************************************************************/
void MS_Init(void)
{
  Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
  while (bDeviceState != CONFIGURED);
}
/*******************************************************************************
* Function Name  : USB_HP_CAN1_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts requests
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN1_TX_IRQHandler(void)
{
  CTR_HP();
}
/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}

