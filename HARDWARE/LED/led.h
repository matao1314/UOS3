#ifndef __LED_H
#define __LED_H	 
#include "sys.h"	 

#define LED0 PBout(3)
#define TEST PBout(4)
//�������˿ڶ���
#define BEEP PBout(8)	// BEEP,�������ӿ�		   

void LED_Init(void);//��ʼ��
void BEEP_Init(void);	//��ʼ��
		 				    
#endif
