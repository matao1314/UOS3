#include "stm32f10x.h"
#include "bsp.h"
#include "common.h"
SD_Error SD_USER_Init(void);
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
#if 1
    if (SysTick_Config(SystemCoreClock / 1000)) {	// ST3.5.0��汾
        /* Capture error */
        while (1);
    }
#else
    OS_CPU_SysTickInit(SystemCoreClock / (CPU_INT32U)OSCfg_TickRate_Hz);
#endif
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
    delay_init(72);
    uart_init(72, 115200);
    LED_Init();
    KEY_Init();
    LCD_Init();
    RTC_Init();
    mem_init(SRAMIN);//��ʼ���ڲ��ڴ��
    SPI1_Init();
    VS_Init();//��ʼ��VS1003
    I2C_EE_Init();//Eeprom
    //���SD���Ƿ�ɹ�
    while(SD_Init() != SD_OK) {
        POINT_COLOR = RED;
        LCD_ShowString(20, 10, 180, 16, 16, "SD Card File!        ");
        LED0 = 0;
        delay_ms(500);
        LCD_ShowString(20, 10, 180, 16, 16, "Please Check SD Card!");
        LED0 = 1;
        delay_ms(500);
    }
    exfuns_init();					//Ϊfatfs��ر��������ڴ�
    f_mount(0, fs[0]); 		 		//����SD��
    f_mount(1, fs[1]); 				//����FLASH.
    while(font_init()) {			//����ֿ�
        LCD_ShowString(60, 50, 200, 16, 16, "Font Error!");
        delay_ms(200);
        LCD_Fill(60, 50, 240, 66, WHITE); //�����ʾ
        update_font(20, 110, 16, 0); //��SD������
    }
    tp_dev.init();
    if(KEY_Scan(0) == 1) {//У׼������
        TP_Adjust();
    }
    if(!VS_HD_Reset()) {
        myprntf("VS1003 HARDWARE_ResetOk!\r\n");
    }
    VS_Soft_Reset();
    printf("VS1003 SOFTWARE_ResetOk!\r\n");
    printf("VS1003 Ram:0X%04X\r\n", VS_Ram_Test()); //RAM���Խ��
    VS_Sine_Test();
    gui_init();
    piclib_init();//��ʼ����ͼ
    printf("System Init Over!\r\n");
    printf(__DATE__"\r\n");
    printf(__TIME__"\r\n");
    SysTick->CTRL |= 1 << 1;  //����systick�ж�;
}
