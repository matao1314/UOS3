#include "common.h"


/*
*********************************************************************************************************
*                                      BSP_OS_SemCreate()
*
* Description : Creates a sempahore to lock/unlock
*
* Argument(s) : p_sem        Pointer to a BSP_OS_SEM structure
*
*               sem_val      Initial value of the semaphore.
*
*               p_sem_name   Pointer to the semaphore name.
*
* Return(s)   : DEF_OK       if the semaphore was created.
*               DEF_FAIL     if the sempahore could not be created.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemCreate (BSP_OS_SEM       *p_sem,
                               BSP_OS_SEM_VAL    sem_val,
                               CPU_CHAR         *p_sem_name)
{
    OS_ERR     err;

    OSSemCreate((OS_SEM *)p_sem,
                (CPU_CHAR *)p_sem_name,
                (OS_SEM_CTR )sem_val,
                (OS_ERR *)&err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                     BSP_OS_SemWait()
*
* Description : Wait on a semaphore to become available
*
* Argument(s) : sem          sempahore handler
*
*               dly_ms       delay in miliseconds to wait on the semaphore
*
* Return(s)   : DEF_OK       if the semaphore was acquire
*               DEF_FAIL     if the sempahore could not be acquire
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemWait (BSP_OS_SEM  *p_sem,
                             CPU_INT32U   dly_ms)
{
    OS_ERR      err;
    CPU_INT32U  dly_ticks;

    dly_ticks  = ((dly_ms * DEF_TIME_NBR_mS_PER_SEC) / OSCfg_TickRate_Hz);

    OSSemPend((OS_SEM *)p_sem,
              (OS_TICK )dly_ticks,
              (OS_OPT  )OS_OPT_PEND_BLOCKING,
              (CPU_TS  )0,
              (OS_ERR *)&err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}

/*
*********************************************************************************************************
*                                      BSP_OS_SemPost()
*
* Description : Post a semaphore
*
* Argument(s) : sem          Semaphore handler
*
* Return(s)   : DEF_OK     if the semaphore was posted.
*               DEF_FAIL      if the sempahore could not be posted.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemPost (BSP_OS_SEM *p_sem)
{
    OS_ERR  err;

    OSSemPost((OS_SEM *)p_sem,
              (OS_OPT  )OS_OPT_POST_1,
              (OS_ERR *)&err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                     uC/OS-II TIMER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    BSP_TimeDlyMs()
*
* Description : This function delay the exceution for specifi amount of miliseconds
*
* Argument(s) : dly_ms       Delay in miliseconds
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void   BSP_OS_TimeDlyMs (CPU_INT32U  dly_ms)
{
    CPU_INT16U  ms;
    CPU_INT16U  sec;
    OS_ERR      err;

    if (dly_ms > 10000u) {                                       /* Limit delays to 10 seconds.                        */
        dly_ms = 10000u;
    }

    if (dly_ms >= 1000u) {
        ms  = dly_ms / 1000u;
        sec = dly_ms % 1000u;
    } else {
        ms  = dly_ms;
        sec = 0u;
    }

    OSTimeDlyHMSM((CPU_INT16U) 0u,
                  (CPU_INT16U) 0u,
                  (CPU_INT16U) sec,
                  (CPU_INT32U) ms,
                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
                  (OS_ERR *)&err);
}


