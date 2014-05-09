#include "calendar.h" 	      						  
#include "stdio.h"

_alarm_obj alarm;	//闹钟结构体
					 
#define TIME_TOPY	  50
#define OTHER_TOPY	130 	


const u8 *calendar_week_table[GUI_LANGUAGE_NUM][7]=
{
{"星期天","星期一","星期二","星期三","星期四","星期五","星期六"},
{"星期天","星期一","星期二","星期三","星期四","星期五","星期六"},
{"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"},
};
//闹钟标题
const u8 *calendar_alarm_caption_table[GUI_LANGUAGE_NUM]=
{
"闹钟","鬧鐘","ALARM",
};
//再响按钮
const u8 *calendar_alarm_realarm_table[GUI_LANGUAGE_NUM]=
{
"再响","再響","REALARM",
};

const u8* calendar_loading_str[GUI_LANGUAGE_NUM][3]=
{
{
	"正在加载,请稍候...",
	"未检测到DS18B20!",
	"启用内部温度传感器...",
},
{
	"正在加载,请稍候...",
	"未检测到DS18B20!",
	"启用内部温度传感器...",
},
{
	"Loading...",
	"DS18B20 Check Failed!",
	"Start Inside Sensor...",
},
};	
const char  my_date[] = __DATE__;//month dd yyyy
const char  my_time[] = __TIME__;//Format: hh:mm:ss
//重新初始化闹钟		    
//alarmx:闹钟结构体
void calendar_alarm_init(_alarm_obj *alarmx) 
{	  
  u32 curtime=0;
	u32 temptime=0;
	u32 destime=0XFFFFFFFF;//目标闹铃时间(s)设定到最大	
 	if(alarmx->weekmask)//必须要有闹钟存在,周日到周六任意一天 
	{										       
		curtime=RTC->CNTH;//得到计数器中的值(秒钟数)
		curtime<<=16;
		curtime+=RTC->CNTL;	   
		//取一个与当前时间最接近的值作为闹钟寄存器的内容
		temptime=curtime/86400;	//得到当前运行天数(此处没有用到天数,仅作说明用)
		temptime=temptime*86400;
 		temptime+=(u32)alarmx->hour*3600+(u32)alarmx->min*60;//得到秒钟数
 		if(temptime<=curtime)temptime+=86400;//执行时间已过，推迟到明天
 		destime=temptime;//更改闹钟寄存器
 	}
	RCC->APB1ENR|=1<<28;//使能电源时钟
  RCC->APB1ENR|=1<<27;//使能备份时钟
	PWR->CR|=1<<8;    //取消备份区写保护
	//上面三步是必须的!
	RTC->CRL|=1<<4;   //允许配置 
	RTC->ALRL=destime&0xffff;
	RTC->ALRH=destime>>16;
	RTC->CRL&=~(1<<4);//配置更新
	while(!(RTC->CRL&(1<<5)));//等待RTC寄存器操作完成 
  calendar.hour = my_time[0];
  calendar.min  = my_time[0];  
  calendar.sec  = my_time[0];  
  calendar.w_year = my_date[0];	
	calendar.w_month = my_date[0];
  calendar.w_date = my_date[0];
	//http://www.keil.com/support/man/docs/c51/c51_pp_predefmacroconst.htm
}
//闹钟响闹铃
//type:闹铃类型	   
//0,滴.
//1,滴.滴.
//2,滴.滴.滴
//4,滴.滴.滴.滴
void calendar_alarm_ring(u8 type)
{
	u8 i;	 
	for(i=0;i<(type+1);i++)
	{
		BEEP=1;
		delay_ms(50);
		BEEP=0;
		delay_ms(70);
	}	 
}

//根据当前的日期,更新日历表.
void calendar_date_refresh(void) 
{
 	u8 weekn;   //周寄存
 	//显示阳历年月日
	POINT_COLOR=BRED; 
	BACK_COLOR=BLACK; 
	LCD_ShowxNum(5,OTHER_TOPY+9,(calendar.w_year/100)%100,2,16,0);//显示年  20/19  
	LCD_ShowxNum(21,OTHER_TOPY+9,calendar.w_year%100,2,16,0);     //显示年  
	LCD_ShowString(37,OTHER_TOPY+9,240,320,16,"-"); //"-"
	LCD_ShowxNum(45,OTHER_TOPY+9,calendar.w_month,2,16,0);        //显示月
	LCD_ShowString(61,OTHER_TOPY+9,240,320,16,"-"); //"-"
	LCD_ShowxNum(69,OTHER_TOPY+9,calendar.w_date,2,16,0);         //显示日	  
	//显示周几?
	POINT_COLOR=RED;
  weekn=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//得到星期	   
	Show_Str(10,OTHER_TOPY+35,240,320,(u8 *)calendar_week_table[gui_phy.language][weekn],16,0); //显示周几?	
													 
}
//闹钟数据保存在:SYSTEM_PARA_SAVE_BASE+sizeof(_system_setings)+sizeof(_vs10xx_obj)
//读取日历闹钟信息
//alarm:闹钟信息 
void calendar_read_para(_alarm_obj * alarm)
{
	alarm=(_alarm_obj *)I2C_EE_ReadLenByte(SYSTEM_PARA_SAVE_BASE+sizeof(int)+sizeof(_vs10xx_obj),sizeof(_alarm_obj));
}
//写入日历闹钟信息
//alarm:闹钟信息 
void calendar_save_para(_alarm_obj * alarm)
{
//  	OS_CPU_SR cpu_sr=0;
	alarm->ringsta&=0X7F;	//清空最高位
//	OS_ENTER_CRITICAL();	//进入临界区(无法被中断打断) _system_setings
	I2C_EE_WriteNLenByte(SYSTEM_PARA_SAVE_BASE+sizeof(int)+sizeof(_vs10xx_obj),(u32)alarm,sizeof(_alarm_obj));
//	OS_EXIT_CRITICAL();		//退出临界区(可以被中断打断)
}

//闹铃处理(尺寸:200*160)
//x,y:坐标
//返回值,处理结果
u8 calendar_alarm_msg(u16 x,u16 y)
{
	u8 rval=0; 
	u8 res;
	u32 abr;						    
	FIL* falarm=0;				  	
  	u8 *bfbase=0;					//大字库的基址
	_window_obj* twin=0;			//窗体
 	_btn_obj * rbtn=0;				//取消按钮		  
 	_btn_obj * okbtn=0;				//确定按钮		  

   	twin=window_creat(x,y,200,160,0,1|1<<5|1<<6,16);//创建窗口,读取背景色
   	okbtn=btn_creat(x+20,y+120,70,30,0,0x02);		//创建按钮
 	rbtn=btn_creat(x+20+70+20,y+120,70,30,0,0x02);	//创建按钮
 	falarm=(FIL *)gui_memin_malloc(sizeof(FIL));	//开辟FIL字节的内存区域 
	if(twin==NULL||rbtn==NULL||okbtn==NULL||falarm==NULL)rval=1; 
	else
	{
		//窗口的名字和背景色
		twin->caption=(u8*)calendar_alarm_caption_table[gui_phy.language];
		twin->windowbkc=APP_WIN_BACK_COLOR;	
		//返回按钮的颜色    
		rbtn->bkctbl[0]=0X8452;		//边框颜色
		rbtn->bkctbl[1]=0XAD97;		//第一行的颜色				
		rbtn->bkctbl[2]=0XAD97;		//上半部分颜色
		rbtn->bkctbl[3]=0X8452;		//下半部分颜色
		okbtn->bkctbl[0]=0X8452;	//边框颜色
		okbtn->bkctbl[1]=0XAD97;	//第一行的颜色				
		okbtn->bkctbl[2]=0XAD97;	//上半部分颜色
		okbtn->bkctbl[3]=0X8452;	//下半部分颜色

		rbtn->caption=(u8*)GUI_CANCEL_CAPTION_TBL[gui_phy.language];		//取消按钮
 		okbtn->caption=(u8*)calendar_alarm_realarm_table[gui_phy.language];	//再响按钮

//		res=f_open(falarm,(const TCHAR*)APP_ASCII_60,FA_READ);//打开文件 
		if(res==0)
		{
			bfbase=(u8*)gui_memin_malloc(falarm->fsize);	//为大字体开辟缓存地址
			if(bfbase==0)rval=1;
			else 
			{
				res=f_read(falarm,bfbase,falarm->fsize,(UINT*)&abr);	//一次读取整个文件
			}
			f_close(falarm);
		}

 		window_draw(twin);						//画出窗体
		btn_draw(rbtn);							//画按钮
		btn_draw(okbtn);						//画按钮			    
 		if(res)rval=res;
		else 									//显示闹铃时间
		{
//			app_showbig2num(bfbase,x+15,y+32+14,alarm.hour,60,BLUE,APP_WIN_BACK_COLOR); 	//显示时
// 			app_showbigchar(bfbase,x+15+60,y+32+14,':',60,BLUE,APP_WIN_BACK_COLOR); 		//":"
//			app_showbig2num(bfbase,x+15+90,y+32+14,alarm.min,60,BLUE,APP_WIN_BACK_COLOR);	//显示分	 
		}
//		OSTaskSuspend(6); //挂起主任务
  		while(rval==0)
		{
			tp_dev.scan(0);    
			in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//得到按键键值  
			delay_ms(5); 
// 	 		if(system_task_return)
//			{
//				rval=1;			//取消
//				break;			//TPAD返回	
//			}
			res=btn_check(rbtn,&in_obj);			//取消按钮检测
			if(res&&((rbtn->sta&0X80)==0))			//有有效操作
			{
				rval=1;
				break;//退出
			}
	 		res=btn_check(okbtn,&in_obj);			//再响按钮检测
	 		if(res&&((okbtn->sta&0X80)==0))			//有有效操作
			{		 
				rval=0XFF;//		   
				break;//退出
			}    
		}	 
	}
	alarm.ringsta&=~(1<<7);	//取消闹铃
	if(rval==0XFF)//稍后再响
	{
		alarm.min+=5; 			//推迟5分钟
		if(alarm.min>59)
		{
			alarm.min=alarm.min%60;
			alarm.hour++;
			if(alarm.hour>23)alarm.hour=0;
		}				  
		calendar_alarm_init((_alarm_obj*)&alarm);//重新初始化闹钟
 	}
	window_delete(twin);
	btn_delete(rbtn);
	btn_delete(okbtn); 	  
	gui_memin_free(falarm);
	gui_memin_free(bfbase);
//	OSTaskResume(6); 		//恢复主任务
	return rval;
}
	    
//时间显示模式
//通过向左滑动退出.						 
//改用内部sram,貌似OK了.	   
u8 calendar_play(void)
{
	u8 second=0;
	u8 t=0;
	u8 tempdate=0;
	u8 rval=0;			//返回值	
	u8 res;

	u16 lastx=0;		//记录滑动最后一次检测的x值
	u8  slidercnt=0;	//滑动计数器
	FIL* f_calendar=0;	 
	u8 *bfbase=0;		//大字库的基址
   	/////////////3D时间显示///////////////
	u16 timex=0;
	//////////////////////////////////////
 	f_calendar=(FIL *)gui_memin_malloc(sizeof(FIL));//开辟FIL字节的内存区域 
	if(f_calendar==NULL)rval=1;		//申请失败
	else
	{
		res=f_open(f_calendar,(const TCHAR*)APP_ASCII_60,FA_READ);//打开文件 
		if(res==FR_OK)
		{
			bfbase=(u8*)gui_memin_malloc(f_calendar->fsize);	//为大字体开辟缓存地址
			if(bfbase==0)rval=1;
			else 
			{
				res=f_read(f_calendar,bfbase,f_calendar->fsize,(UINT*)&br);	//一次读取整个文件
 			}
			f_close(f_calendar);
		} 
		if(res)rval=res;
	} 	    
	if(rval==0)//无错误
	{	  
		second=calendar.sec;//得到此刻的秒钟
		POINT_COLOR=GBLUE;
		delay_ms(1100);//等待1.1s 
		BACK_COLOR= BLACK;
		calendar_date_refresh();  //加载日历
		tempdate=calendar.w_date;//天数暂存器

		app_showbigchar(bfbase,70-4,TIME_TOPY,':',60,WHITE,BLACK); 		//":"
		app_showbigchar(bfbase,150-4,TIME_TOPY,':',60,WHITE,BLACK); 	//":"	 
	}
  	while(rval==0)
	{	
		tp_dev.scan(0);    
		if(tp_dev.sta&TP_PRES_DOWN)//触摸按下了
		{
			if(slidercnt==0)//第一次滑动按下
			{
				lastx=tp_dev.x;//记录第一次按下的坐标
				slidercnt++;				
			}else
			{
				if(tp_dev.x>(lastx+10))slidercnt=0;//往右滑动了,直接丢弃  
				if((tp_dev.x+10)<lastx)//向左滑动至少10个像素点
				{
					slidercnt++; 		//是一个有效的滑动
					lastx=tp_dev.x;
				}
				if(slidercnt>5)break;	//滑动有效,直接退出
			}
		}else slidercnt=0;				//松开了,则直接设置滑动无效
 		if(second!=calendar.sec) //秒钟改变了
		{ 	
  		second=calendar.sec;  
			app_showbig2num(bfbase,10,TIME_TOPY,calendar.hour,60,WHITE,BLACK);	//显示时
 			app_showbig2num(bfbase,90,TIME_TOPY,calendar.min,60,WHITE,BLACK);	//显示分	 
 			app_showbig2num(bfbase,170,TIME_TOPY,calendar.sec,60,WHITE,BLACK);	//显示秒	 					   
			if(calendar.w_date!=tempdate)
			{
				calendar_date_refresh();//天数变化了,更新日历.  
				tempdate=calendar.w_date;//修改tempdate，防止重复进入
			}
			t++;  
 		}
 		timex++;
 	};
 	while(tp_dev.sta&TP_PRES_DOWN)tp_dev.scan(0);//等待TP松开.
	gui_memin_free(bfbase);		//删除申请的内存
	gui_memin_free(f_calendar);	//删除申请的内存
	POINT_COLOR=BLUE;
	BACK_COLOR=WHITE ;	
	return rval;
}




















