#ifndef __USART_H
#define __USART_H
#include "stdio.h"
	 
#define  DEBUG

#ifdef   DEBUG
#define myprntf printf
#else
#define myprntf /\
/myprntf
#endif

//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
////////////////////////////////////////////////////////////////////////////////// 	  
 
	  	
extern u8 USART_RX_BUF[64];     //���ջ���,���63���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART_RX_STA;         //����״̬���	

//����봮���жϽ��գ��벻Ҫע�����º궨��
//#define EN_USART1_RX //ʹ�ܴ���1����
void uart_init(u32 pclk2,u32 bound);

#endif	   
















