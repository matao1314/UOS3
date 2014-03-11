#ifndef __FLASH_H
#define __FLASH_H			    
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//AT45DB ��������	   
//�޸�����:2011��11��13��21:38:42
///////////////////////////////////////////////////////////	  
#define	SPI_FLASH_CS     PCout(2)  //ѡ��FLASH					 
///////////////////////////////////////////////////////////
extern u16 SPI_FLASH_TYPE;//��������ʹ�õ�flashоƬ�ͺ�

//AT45DB��д
#define FLASH_ID       0X1F26//ID
#define Dummy_Byte     0xA5	 //���
//ָ���
#define SPI_FLASH_PageSize            528	//ÿҳ528���ֽ�
#define SPI_FLASH_PageNum             4096//ÿ����
///////////////////////////////////////////////////////////
#define BUFFER_1_WRITE                0x84// д���һ������
#define BUFFER_2_WRITE                0x87// д��ڶ�������
#define BUFFER_1_READ                 0xD4// ��ȡ��һ������
#define BUFFER_2_READ                 0xD6// ��ȡ�ڶ�������
#define B1_TO_MM_PAGE_PROG_WITH_ERASE 0x83// ����һ������������д�����洢��������ģʽ��
#define B2_TO_MM_PAGE_PROG_WITH_ERASE 0x86// ���ڶ�������������д�����洢��������ģʽ��
#define MM_PAGE_TO_B1_XFER            0x53// �����洢����ָ��ҳ���ݼ��ص���һ������
#define MM_PAGE_TO_B2_XFER            0x55// �����洢����ָ��ҳ���ݼ��ص��ڶ�������
#define PAGE_ERASE                    0x81// ҳ����  ��ÿҳ512/528�ֽڣ�
#define SECTOR_ERASE                  0x7C// ����������ÿ����128K�ֽڣ�
#define READ_STATE_REGISTER           0xD7// ��ȡ״̬�Ĵ���
/////////////////////////////////////////////////////////////
/*----- High layer function -----*/
void SPI_Flash_Write(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite);//��ȡflash
void SPI_Flash_Read (u8 *pBuffer, u32 ReadAddr,  u16 NumByteToRead); //��ȡflash
/////////////////////////////////////////////////////////////////////////
void DF_mm_to_buf(u8 buffer,unsigned int page);//��ָ�����洢��ҳ������ת��ָ��������
void DF_buf_to_mm(u8 buffer,u16 page);//��ָ���������е�����д�����洢����ָ��ҳ
void DF_page_earse(u16 page);       //����ָ�������洢��ҳ����ַ��Χ0-4095��
/*----- Low layer function -----*/
u8	 SPI_Flash_ReadSR(void);        //��ȡ״̬�Ĵ���
u16  SPI_Flash_ReadID(void);  	    //��ȡFLASH ID
void SPI_Flash_Init(void);					//SPI��ʼ��
void SPI_Flash_Wait_Busy(void);     //�ȴ�����
#endif
















