#ifndef __NOTEPAD_H
#define __NOTEPAD_H 	
#include "common.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//APP-记事本 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/10/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//定义最大的编辑长度.也就是新建文本文件的大小.或者打开一个旧文件后最大允许增加的长度.
#define NOTEPAD_EDIT_LEN	2048	
 
void notepad_new_pathname(u8 *pname);
u8 notepad_play(void);

#endif























