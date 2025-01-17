#ifndef __MALLOC_H
#define __MALLOC_H
#include "stm32f10x.h"


//typedef unsigned long  u32;
//typedef unsigned short u16;
//typedef unsigned char  u8;
#ifndef NULL
#define NULL 0
#endif

#define SRAMIN	0	//内部内存池

//mem1内存参数设定.mem1完全处于内部SRAM里面
#define MEM1_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM1_MAX_SIZE			40*1024  						//最大管理内存 40K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//内存表大小


//内存管理控制器
struct _m_mallco_dev {
    void (*init)(u8);					//初始化
    u8 (*perused)(u8);		  	    	//内存使用率
    u8 	*membase[1];					//内存池 管理2个区域的内存
    u16 *memmap[1]; 					//内存管理状态表
    u8  memrdy[1]; 						//内存管理是否就绪
};
extern struct _m_mallco_dev mallco_dev;	 //在mallco.c里面定义

void mymemset(void *s, u8 c, u32 count);	 //设置内存
void mymemcpy(void *des, void *src, u32 n); //复制内存
void mem_init(u8 memx);					 //内存管理初始化函数(外/内部调用)
u32 mem_malloc(u8 memx, u32 size);		 //内存分配(内部调用)
u8 mem_free(u8 memx, u32 offset);		 //内存释放(内部调用)
u8 mem_perused(u8 memx);				 //获得内存使用率(外/内部调用)
////////////////////////////////////////////////////////////////////////////////
//用户调用函数
void myfree(u8 memx, void *ptr);  			//内存释放(外部调用)
void *mymalloc(u8 memx, u32 size);			//内存分配(外部调用)
void *myrealloc(u8 memx, void *ptr, u32 size); //重新分配内存(外部调用)
#endif













