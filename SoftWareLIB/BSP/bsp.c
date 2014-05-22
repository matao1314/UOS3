#include "stm32f10x.h"
#include "bsp.h"

#include "common.h"//Common head file
SD_Error SD_USER_Init(void);
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
INT32U  OS_CPU_SysTickClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    RCC_GetClocksFreq(&rcc_clocks);
    return ((INT32U)rcc_clocks.HCLK_Frequency);
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
#if 1
    if (SysTick_Config(SystemCoreClock / 100))	// ST3.5.0库版本
    {
        /* Capture error */
        while (1);
    }
#else
    OS_CPU_SysTickInit(SystemCoreClock / (CPU_INT32U)OSCfg_TickRate_Hz);
#endif
}

CPU_INT32U BSP_CPU_ClkFreq(void)
{
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    return((CPU_INT32U)RCC_Clocks.HCLK_Frequency);
}
/*******************************************************************************
* Function Name :void InterruptOrder(void)
* Description   :中断向量，优先级
*******************************************************************************/
void NVIC_Cfg(void)
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
*******************************************************************************/
void BSP_Init(void)
{
    SystemInit();//Clock72MHZ
    //SysTick_Init();
    delay_init(72);
    NVIC_Cfg();
    uart_init(72, 115200);
    LED_Init();
    KEY_Init();
    LCD_Init();
    RTC_Init();
    mem_init(SRAMIN);//初始化内部内存池
    SPI1_Init();
    VS_Init();//初始化VS1003
    I2C_EE_Init();//Eeprom
    //检测SD卡是否成功
    while(SD_USER_Init() != SD_OK)
    {
        POINT_COLOR = RED;
        LCD_ShowString(20, 10, 8, 16, 16, "SD Card File!            ");
        LED0 = 0;
        delay_ms(500);
        LCD_ShowString(20, 10, 8, 16, 16, "Please Check SD Card!");
        LED0 = 1;
        delay_ms(500);
    }
    sd_fs_init();//文件系统初始化-汉字字库保存在sd卡中，并将盘符设置为0
    exfuns_init();					//为fatfs相关变量申请内存
    f_mount(0, fs[0]); 		 		//挂载SD卡
    f_mount(1, fs[1]); 				//挂载FLASH.
    while(font_init()) 				//检查字库
    {
        LCD_ShowString(60, 50, 200, 16, 16, "Font Error!");
        delay_ms(200);
        LCD_Fill(60, 50, 240, 66, WHITE); //清除显示
        update_font(20, 110, 16, 0); //从SD卡更新
    }
    tp_dev.init();
    if(KEY_Scan(0) == 1) TP_Adjust();
    if(!VS_HD_Reset())
    {
        myprntf("VS1003 HARDWARE_ResetOk!\r\n");
    }
    VS_Soft_Reset();
    printf("VS1003 SOFTWARE_ResetOk!\r\n");
    printf("VS1003 Ram:0X%04X\r\n", VS_Ram_Test()); //RAM测试结果
    VS_Sine_Test();
    gui_init();
    piclib_init();//初始化画图
    printf("System Init Over!\r\n");
    printf(__DATE__"\r\n");
    printf(__TIME__"\r\n");
    SysTick_Init();
}

SD_CardInfo   SDCardInfo;        //SD卡信息
SD_Error      SD_USER_Init(void);//SD卡初始化
//SD Card Init
SD_Error SD_USER_Init(void)
{
    SD_Error   Status = SD_OK;
    /* SD Init */
    Status = SD_Init();
    if (Status == SD_OK)
    {
        /* Read CSD/CID MSD registers */
        Status = SD_GetCardInfo( &SDCardInfo );//获得SD卡索引信息
        printf("SDCardCapacity = %dMB\r\n", SDCardInfo.CardCapacity >> 20);
        printf("CardBlockSize  = %d\r\n", SDCardInfo.CardBlockSize );
    }
    if (Status == SD_OK)
    {
        /* Select Card */
        Status = SD_SelectDeselect( (u32) (SDCardInfo.RCA << 16) );
    }
    if (Status == SD_OK)
    {
        /* set bus wide */
        Status = SD_EnableWideBusOperation( SDIO_BusWide_1b );
    }
    /* Set Device Transfer Mode to DMA */
    if (Status == SD_OK)
    {
        /* 任选一种都可以工作 */
        //Status = SD_SetDeviceMode( SD_DMA_MODE );
        Status = SD_SetDeviceMode( SD_POLLING_MODE );
        //Status = SD_SetDeviceMode( SD_INTERRUPT_MODE );
    }
    return Status;
}


