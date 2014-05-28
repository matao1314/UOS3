/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/


#include "diskio.h"
#include "sdcard.h"

#include "flash.h"
#include "malloc.h"		 		   
#include "os.h"
#define SECTOR_SIZE 512U

SD_CardInfo SDCardInfo;

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{ 
	u8 state;
	state=  SD_Init();							//��ʼ��
	if(!state){
	 return STA_NODISK;
	}   
	return 0;									  
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{ /**
    if(drv)
    {
        return STA_NOINIT;  //��֧�ִ���0����
    }

    //���SD���Ƿ����
    if(!SD_DET())
    {
        return STA_NODISK;
    }
    return 0;
	**/
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
		u8 res=0;
    if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������		 	 
		res=SD_ReadDisk(buff,sector,count);
    //������ֵ����SPI_SD_driver.c�ķ���ֵת��ff.c�ķ���ֵ
    if(res == 0x00)
    {
        return RES_OK;
    }
    else
    {
        return RES_ERROR;
    }
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	u8 res;
	u8 retry=0X1F;		//д��ʧ�ܵ�ʱ��,���Դ���
	if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������		 	 
	while(retry)
	{
		res=SD_WriteDisk((u8*)buff,sector,count);
		if(res==0)break;
		retry--;
	}
	// ����ֵת��
	if(res == 0)
	{
			return RES_OK;
	}
	else
	{
			return RES_ERROR;
	}
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    DRESULT res;


    if (drv)
    {    
        return RES_PARERR;  //��֧�ֵ����̲��������򷵻ز�������
    }
    
    //FATFSĿǰ�汾���账��CTRL_SYNC��GET_SECTOR_COUNT��GET_BLOCK_SIZ��������
    switch(ctrl)
    {
    case CTRL_SYNC:
	/*
         SD_CS_ENABLE();
	 
        if(SD_WaitReady()==0)
        {
            res = RES_OK;
        }
        else
        {
            res = RES_ERROR;
        }
        SD_CS_DISABLE();
		*/
		res=RES_OK;
        break;
        
    case GET_BLOCK_SIZE:
        *(DWORD*)buff = SDCardInfo.CardBlockSize;
        res = RES_OK;
        break;

    case GET_SECTOR_COUNT:
        *(DWORD*)buff = (SDCardInfo.CardCapacity*1024)/SDCardInfo.CardBlockSize;   					//��������
        res = RES_OK;
        break;
    default:
        res = RES_PARERR;
        break;
    }

    return res;
}

/* �õ��ļ�Calendar��ʽ�Ľ�������,��DWORD get_fattime (void) ��任 */							
/*-----------------------------------------------------------------------*/
/* User defined function to give a current time to fatfs module          */
/* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
/* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{   
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
CPU_SR cpu_sr=0;
void ff_enter(void)
{
 	OS_CRITICAL_ENTER();//�����ٽ���(�޷����жϴ��)    
}
void ff_leave(void)
{
 	OS_CRITICAL_EXIT();	//�˳��ٽ���(���Ա��жϴ��)
}
/////////////////////////////////////////////////////////////////////////////////////

//��̬�����ڴ�
void *ff_memalloc (UINT size)			
{
	return (void*)mymalloc(SRAMIN,size);
}
//�ͷ��ڴ�
void ff_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}

