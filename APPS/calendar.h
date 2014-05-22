#ifndef __CALENDAR_H
#define __CALENDAR_H
#include "sys.h"
#include "common.h"
#include "bsp.h"
//闹钟结构体
__packed typedef struct
{
    u8  weekmask;		//闹钟响铃掩码
    u8  ringsta;		//闹铃状态及铃声标志.
    //[7]:0,无闹铃;1,闹铃中;
    //[6:3]:保留
    //[2:0]:闹钟铃声类型
    u8  hour;	   		//闹铃小时
    u8  min;			//闹铃分钟

    u8 saveflag;		//保存标志,0X0A,保存过了;其他,还从未保存
} _alarm_obj;

extern _alarm_obj alarm;//闹钟结构体
extern const u8 *calendar_week_table[GUI_LANGUAGE_NUM][7];//外部定义的星期表

void calendar_alarm_init(_alarm_obj *alarmx);
void calendar_alarm_ring(u8 type);
void calendar_date_refresh(void);
void calendar_read_para(_alarm_obj *alarm);
void calendar_save_para(_alarm_obj *alarm);
u8 calendar_alarm_msg(u16 x, u16 y);
u8 calendar_play(void);

#endif












