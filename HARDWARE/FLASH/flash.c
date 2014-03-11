#include "flash.h" 
#include "spi.h"
#include "delay.h"
#include "usart.h"	 
#include "common.h"
#include "touch.h"
//////////////////////////////////////////////////////////////////////////////////	 
u16 SPI_FLASH_TYPE=FLASH_ID;//Ĭ�Ͼ���25Q64
////////////////////////////////////////////////////////////////////////////////// 	  
//32������Ϊ1��Block
//256ҳΪһ������
//AT45DB
//����Ϊ2M�ֽ�,����512����,15��Sector��������4096ҳ��ÿҳ528�ֽ�
//��ʼ��SPI FLASH��IO��
void SPI_Flash_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );
	//Configure PC2 pin: M45PE_CS pin 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	SPI1_Init();		   	//��ʼ��SPI
	//SPI1_SetSpeed(SPI_BaudRatePrescaler_64);//����Ϊ18Mʱ��,����ģʽ	 SPI_BaudRatePrescaler_2
	SPI_FLASH_TYPE=SPI_Flash_ReadID();//��ȡFLASH ID.  
	printf("FlashID=:%x\r\n",SPI_FLASH_TYPE); //��ӡLCD ID  
}
//��ȡSPI_FLASH��״̬�Ĵ���
//Status Register Format
//Bit 7     Bit 6  Bit 5  Bit 4  Bit 3  Bit 2  Bit 1      Bit 0
//RDY/BUSY  COMP   1      0      1      1      PROTECT    PAGE SIZE
//BUSY:æ���λ(0,æ;1,����)
//PAGE SIZE  0:512b  1:528b
//Ĭ��:0x00
u8 SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	CS_Seclect(CS_SPI_FLASH);//ʹ������   
	SPI1_ReadWriteByte(READ_STATE_REGISTER);//���Ͷ�ȡ״̬�Ĵ�������
  SPI1_ReadWriteByte(0X00); 
	SPI1_ReadWriteByte(0X00); 
	SPI1_ReadWriteByte(0X00);     
	byte=SPI1_ReadWriteByte(0Xff);      //��ȡһ���ֽ�  
	SPI_FLASH_CS=1;                     //ȡ��Ƭѡ
	TCS=0;     
	return byte;   
} 
//��ȡоƬID AT45DB161 ��ID:0X1F26
u16 SPI_Flash_ReadID(void)
{
	u16 Temp = 0;
  SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
	CS_Seclect(CS_SPI_FLASH);//ʹ������   
	SPI1_ReadWriteByte(0x9F);//���Ͷ�ȡID����	    
	Temp|=SPI1_ReadWriteByte(Dummy_Byte)<<8;  
	Temp|=SPI1_ReadWriteByte(Dummy_Byte);
	SPI1_ReadWriteByte(Dummy_Byte);//ͨ��д��0xFF���Զ������� 	    
	SPI1_ReadWriteByte(Dummy_Byte); 	    
	SPI_FLASH_CS=1;
	return Temp;
}   		    
//�ȴ�оƬ����
void SPI_Flash_Wait_Busy(void)   
{   
	while (!(SPI_Flash_ReadSR()&0x80));//�ȴ�BUSY��1
}

//��ָ�����洢��ҳ������ת��ָ��������
void DF_mm_to_buf(u8 buffer,unsigned int page)
{	  
  SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
	CS_Seclect(CS_SPI_FLASH);//ʹ������   
	if(buffer==1)   SPI1_ReadWriteByte(MM_PAGE_TO_B1_XFER);	  
	else            SPI1_ReadWriteByte(MM_PAGE_TO_B2_XFER);  
	SPI1_ReadWriteByte((u8)(page >> 6));
  SPI1_ReadWriteByte((u8)(page << 2));
  SPI1_ReadWriteByte(0x00);
	SPI_FLASH_CS=1;
} 
//��ָ���������е�����д�����洢����ָ��ҳ
void DF_buf_to_mm(u8 buffer,u16 page)
{
  SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
	if(page<SPI_FLASH_PageNum)
	{
   	CS_Seclect(CS_SPI_FLASH);//ʹ������   
		if(buffer==1)    SPI1_ReadWriteByte(B1_TO_MM_PAGE_PROG_WITH_ERASE); 
		else             SPI1_ReadWriteByte(B2_TO_MM_PAGE_PROG_WITH_ERASE);	 
		SPI1_ReadWriteByte((u8)(page>>6));
		SPI1_ReadWriteByte((u8)(page<<2));
		SPI1_ReadWriteByte(0x00);
	  SPI_FLASH_CS=1;
	}
}
//��ָ����ַ��ʼд��ָ������������	     
void SPI_Flash_Write(u8 *pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
	u16 offaddr,i;
	u32 paddr;//ҳ��ַ
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//���õ�����ģʽ
	paddr=WriteAddr/SPI_FLASH_PageSize;  //�õ���ʼд�����ҳ��ַ
	offaddr=WriteAddr%SPI_FLASH_PageSize;//�õ�����ҳ��ַ���ƫ��
	DF_mm_to_buf(1,paddr);//����ʼҳ���ݶ�����buf1			  
  SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
	CS_Seclect(CS_SPI_FLASH);//ʹ������   
	SPI1_ReadWriteByte(BUFFER_1_WRITE);//д��1����������	 		   
	SPI1_ReadWriteByte(0x00);//14bit ��Ч����+10bit��ַ���� 
	SPI1_ReadWriteByte((u8)(offaddr>>8));//д���ڸ�ҳ��ƫ�Ƶ�ַ   
	SPI1_ReadWriteByte((u8)offaddr);
	for (i=0;i<NumByteToWrite;)//��������
	{
		SPI1_ReadWriteByte(*pBuffer);//д��һ������
		pBuffer++;
		i++;
		if((i+offaddr)%SPI_FLASH_PageSize==0)
		{
	    SPI_FLASH_CS=1;				    
			DF_buf_to_mm(1,paddr);//��BUF1������д�����洢��
			paddr++;	   
			if(paddr>=SPI_FLASH_PageNum)return; //������AT45DB161�ķ�Χ
			DF_mm_to_buf(1,paddr); //����ʼҳ���ݶ�����buf1			  
      SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
			CS_Seclect(CS_SPI_FLASH);//ʹ������   
			SPI1_ReadWriteByte(BUFFER_1_WRITE);//д��1����������	 	 		   
			SPI1_ReadWriteByte(0x00);//14bit ��Ч����+10bit��ַ���� 
			SPI1_ReadWriteByte(0x00);//���õ�ַ��0 
			SPI1_ReadWriteByte(0x00);		    
		}			   
	}
	SPI_FLASH_CS=1;
	DF_buf_to_mm(1,paddr);//��BUF1������д�����洢��			  
} 

//��ָ����ַ��ʼ����ָ������������	     
void SPI_Flash_Read(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
	u16 offaddr,i;
	u32 paddr;//ҳ��ַ
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//���õ�����ģʽ
	paddr=ReadAddr/SPI_FLASH_PageSize;  //�õ���ʼд�����ҳ��ַ
	offaddr=ReadAddr%SPI_FLASH_PageSize;//�õ�����ҳ��ַ���ƫ��
	DF_mm_to_buf(1,paddr);//����ʼҳ���ݶ�����buf1			  
  SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
	CS_Seclect(CS_SPI_FLASH);//ʹ������   
	SPI1_ReadWriteByte(BUFFER_1_READ);//��1����������	 		   
	SPI1_ReadWriteByte(0x00);//14bit ��Ч����+10bit��ַ���� 
	SPI1_ReadWriteByte((u8)(offaddr>>8));//д���ڸ�ҳ��ƫ�Ƶ�ַ   
	SPI1_ReadWriteByte((u8)offaddr);
	SPI1_ReadWriteByte(0x00); //�ȴ� 
	for (i=0;i<NumByteToRead;)//��ȡNumByteToRead������
	{
		*pBuffer=SPI1_ReadWriteByte(0xff);//��ȡһ������
		pBuffer++;
		i++;
		if((i+offaddr)%SPI_FLASH_PageSize==0)
		{
	    SPI_FLASH_CS=1;				    
			paddr++;	    
			if(paddr>=SPI_FLASH_PageNum)   return; //������AT45DB161�ķ�Χ
			DF_mm_to_buf(1,paddr); //����ʼҳ���ݶ�����buf1			  
      SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
			CS_Seclect(CS_SPI_FLASH);//ʹ������   
			SPI1_ReadWriteByte(BUFFER_1_READ);//��1����������	 		   
			SPI1_ReadWriteByte(0x00);//14bit ��Ч����+10bit��ַ���� 
			SPI1_ReadWriteByte(0x00);//���õ�ַ��0 
			SPI1_ReadWriteByte(0x00);
			SPI1_ReadWriteByte(0x00);//�ȴ�		    
		}			   
	}
	SPI_FLASH_CS=1;	
} 
//����ָ�������洢��ҳ����ַ��Χ0-4095��
void DF_page_earse(u16 page)
{		  
  SPI_Flash_Wait_Busy();//�ж��Ƿ�Ϊæ 
	CS_Seclect(CS_SPI_FLASH);//ʹ������   
	SPI1_ReadWriteByte(PAGE_ERASE);
	SPI1_ReadWriteByte((u8)(page >> 6));
	SPI1_ReadWriteByte((u8)(page << 2));
	SPI1_ReadWriteByte(0x00);
	SPI_FLASH_CS=1;
}
