#ifndef __LED_H
#define __LED_H	 
#include "sys.h"	 

#define LED0 PBout(3)
#define TEST PBout(4)
//蜂鸣器端口定义
#define BEEP PBout(8)	// BEEP,蜂鸣器接口		   

void LED_Init(void);//初始化
void BEEP_Init(void);	//初始化
		 				    
#endif
