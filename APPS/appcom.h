#ifndef __COMMON_H
#define __COMMON_H
//APP HEADFILE
#include "picviewer.h"
#include "calendar.h"
#include "mp3player.h"
#include "settingserver.h"

//#include "firmwareupgrade.h"
#include "storage.h"

//硬件平台软硬件版本定义
#define HARDWARE_VERSION	   		18		//硬件版本,放大10倍,如1.0表示为10
#define SOFTWARE_VERSION	    	224		//软件版本,放大100倍,如1.00,表示为100

//系统数据保存基址
#define SYSTEM_PARA_SAVE_BASE 		100		//系统信息保存首地址.从100开始.			    

////////////////////////////////////////////////////////////////////////////////////////////
//各图标/图片路径
extern const u8 *APP_OK_PIC;			//确认图标
extern const u8 *APP_CANCEL_PIC;		//取消图标
extern const u8 *APP_UNSELECT_PIC;		//未选中图标
extern const u8 *APP_SELECT_PIC;		//选中图标
extern const u8 *APP_ASCII_60;			//大数字字体路径
extern const u8 *APP_ASCII_28;			//大数字字体路径
extern const u8 *APP_VOL_PIC;			//音量图片路径

extern const u8 APP_ALIENTEK_ICO[72];	//启动界面图标,存放在flash
////////////////////////////////////////////////////////////////////////////////////////////
//APP的总功能数目
#define APP_FUNS_NUM	18

//app主要功能界面标题
extern const u8 *APP_MFUNS_CAPTION_TBL[APP_FUNS_NUM][GUI_LANGUAGE_NUM];
extern const u8 *APP_DISK_NAME_TBL[2][GUI_LANGUAGE_NUM];

extern const u8 *APP_MODESEL_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8 *APP_REMIND_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8 *APP_SAVE_CAPTION_TBL[GUI_LANGUAGE_NUM];
extern const u8 *APP_CREAT_ERR_MSG_TBL[GUI_LANGUAGE_NUM];
//平滑线的起止颜色定义
#define WIN_SMOOTH_LINE_SEC	0XB1FFC4	//起止颜色
#define WIN_SMOOTH_LINE_MC	0X1600B1	//中间颜色

//弹出窗口选择条目的设置信息
#define APP_ITEM_BTN1_WIDTH		60	  		//有2个按键时的宽度
#define APP_ITEM_BTN2_WIDTH		100			//只有1个按键时的宽度
#define APP_ITEM_BTN_HEIGHT		30			//按键高度
#define APP_ITEM_ICO_SIZE		32			//ICO图标的尺寸

#define APP_ITEM_SEL_BKCOLOR	0X0EC3		//选择时的背景色
#define APP_WIN_BACK_COLOR	 	0XC618		//窗体背景色

/////////////////////////////////////////////////////////////////////////

u32  app_get_rand(u32 max);
void app_srand(u32 seed);
void app_read_bkcolor(u16 x, u16 y, u16 width, u16 height, u16 *ctbl);
void app_recover_bkcolor(u16 x, u16 y, u16 width, u16 height, u16 *ctbl);
void app_gui_tcbar(u16 x, u16 y, u16 width, u16 height, u8 mode);
u8 app_get_numlen(long long num, u8 dir);
void app_show_float(u16 x, u16 y, long long num, u8 flen, u8 clen, u8 font, u16 color, u16 bkcolor);
void app_filebrower(u8 *topname, u8 mode);
void app_showbigchar(u8 *fontbase, u16 x, u16 y, u8 chr, u8 size, u16 color, u16 bkcolor);
void app_showbigstring(u8 *fontbase, u16 x, u16 y, const u8 *p, u8 size, u16 color, u16 bkcolor);
void app_showbignum(u8 *fontbase, u16 x, u16 y, u32 num, u8 len, u8 size, u16 color, u16 bkcolor);
void app_showbig2num(u8 *fontbase, u16 x, u16 y, u8 num, u8 size, u16 color, u16 bkcolor);
void app_show_nummid(u16 x, u16 y, u16 width, u16 height, u32 num, u8 len, u8 size, u16 ptcolor, u16 bkcolor);
void app_draw_smooth_line(u16 x, u16 y, u16 width, u16 height, u32 sergb, u32 mrgb);

u8 app_tp_is_in_area(_m_tp_dev *tp, u16 x, u16 y, u16 width, u16 height);
void app_show_items(u16 x, u16 y, u16 itemwidth, u16 itemheight, u8 *name, u8 *icopath, u16 color, u16 bkcolor);
u8 *app_get_icopath(u8 mode, u8 *selpath, u8 *unselpath, u8 selx, u8 index);
u8 app_items_sel(u16 x, u16 y, u16 width, u16 height, u8 *items[], u8 itemsize, u8 *selx, u8 mode, u8 *caption);
u8 app_listbox_select(u8 *sel, u8 *top, u8 *caption, u8 *items[], u8 itemsize);
void app_show_mono_icos(u16 x, u16 y, u8 width, u8 height, u8 *icosbase, u16 color, u16 bkcolor);

u8 app_system_file_check(void);//系统文件检测
u8 app_boot_cpdmsg(u8 *pname, u8 pct, u8 mode);
void app_boot_cpdmsg_set(u16 x, u16 y);
u8 app_system_update(u8(*fcpymsg)(u8 *pname, u8 pct, u8 mode));
void app_getstm32_sn(u32 *sn0, u32 *sn1, u32 *sn2);
void app_get_version(u8 *buf, u32 ver, u8 len); //得到版本号

void app_usmart_getsn(void);//USMART专用.
u8 app_system_parameter_init(void);//系统信息初始化
#endif




























































