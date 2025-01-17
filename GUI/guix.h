#ifndef __GUIX_H
#define __GUIX_H
#include "sys.h"
#include "malloc.h"
#include "lcd.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//GUI-底层实现 代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/10/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////



//gui显示器的尺寸
#define GUI_LCD_W		240	//gui显示区域的宽度
#define GUI_LCD_H 		320	//gui显示区域的高度	   

//用到ucos的滴答时钟
typedef unsigned int   INT32U;
//extern volatile  INT32U  OSTime;
#define  OSTime  100

//gui时间计数器,需要在外部实现
//gui定时器,每10ms增加1次
#define GUI_TIMER_10MS	OSTime/2 	//ucos的调度时间设置为5ms 

#define GUI_VERSION		100			//gui版本(扩大了100倍),100表示V1.00
//////////////////////////////////////////////////////////////////////////////////////////////
//GUI支持的语言种类数目
//系统语言种类数
#define GUI_LANGUAGE_NUM	2//语言种类数
//0,简体中文
//1,英文

extern const u8 *GUI_OK_CAPTION_TBL[GUI_LANGUAGE_NUM]; 			//确认按钮
extern const u8 *GUI_OPTION_CAPTION_TBL[GUI_LANGUAGE_NUM];		//选项按钮
extern const u8 *GUI_BACK_CAPTION_TBL[GUI_LANGUAGE_NUM];		//取消按钮
extern const u8 *GUI_CANCEL_CAPTION_TBL[GUI_LANGUAGE_NUM];		//取消按钮
extern const u8 *GUI_QUIT_CAPTION_TBL[GUI_LANGUAGE_NUM];		//退出按钮
////////////////////////////////////////////////////////////////////////////////////////////////////////
//gui颜色定义
#define GUI_COLOR_BLACK 0X0000
#define GUI_COLOR_WHITE 0XFFFF


//输入事件类型
#define	IN_TYPE_TOUCH	0X00
#define IN_TYPE_KEY		0X01
#define IN_TYPE_JOYPAD  0X02
#define IN_TYPE_MOUSE	0X03
#define IN_TYPE_ERR	 	0XFF

//gui输入接口
__packed typedef struct {
    void (*get_key)(void *, u8);	//获取键值参数
    u16 x;						//坐标
    u16 y;
    u32 keyval;					//按键键值
    u8  intype;					//输入类型
    u8 	ksta;					//输入设备(按键)的状态 [7:1],保留;[0],0,松开;1,按下.
} _in_obj;
extern _in_obj in_obj;

//gui底层接口
//也就是外部需要实现的函数!
//这里我们需要外部提供4个函数
//1,读点函数;
//2,画点函数;
//3,单色填充函数;
//4,彩色填充函数
__packed typedef struct {
    u8 language;							//GUI当前语言,取值范围0~GUI_LANGUAGE_NUM-1;
    u16 back_color;							//背景色
    u16(*read_point)(u16, u16);				//读点函数
    void(*draw_point)(u16, u16, u16);			//画点函数
    void(*fill)(u16, u16, u16, u16, u16);		//单色填充函数
    void(*colorfill)(u16, u16, u16, u16, u16 *);	//彩色填充函数
} _gui_phy;
extern _gui_phy gui_phy;

u16 gui_alpha_blend565(u16 src, u16 dst, u8 alpha);						//alpha blending
u16 gui_color_chg(u32 rgb);												//颜色转换.将32位色转为16位色
u16 gui_rgb332torgb565(u16 rgb332);										//将rgb332转为rgb565
long long gui_pow(u8 m, u8 n);											//得到m^n
u8 *gui_path_name(u8 *pname, u8 *path, u8 *name);

void gui_memset(void *p, u8 c, u32 len);
void *gui_memin_malloc(u32 size);
void gui_memin_free(void *ptr);
void *gui_memin_realloc(void *ptr, u32 size);

void gui_init(void);
void gui_get_key(void *obj, u8 type);
u32 gui_disabs(u32 x1, u32 x2);											//差的绝对值
void gui_alphablend_area(u16 x, u16 y, u16 width, u16 height, u16 color, u8 aval);
void gui_draw_bigpoint(u16 x0, u16 y0, u16 color);						//画大点
void gui_draw_line(u16 x0, u16 y0, u16 x1, u16 y1, u16 color);				//画任意线
void gui_draw_rectangle(u16 x0, u16 y0, u16 width, u16 height, u16 color);	//画矩形
void gui_draw_arcrectangle(u16 x, u16 y, u16 width, u16 height, u8 r, u8 mode, u16 upcolor, u16 downcolor); //画圆角矩形
void gui_draw_vline(u16 x0, u16 y0, u16 len, u16 color);								//画垂直线
void gui_draw_hline(u16 x0, u16 y0, u16 len, u16 color);								//画水平线
void gui_fill_colorblock(u16 x0, u16 y0, u16 width, u16 height, u16 *ctbl, u8 mode);		//填充颜色块
void gui_smooth_color(u32 srgb, u32 ergb, u16 *cbuf, u16 len);							//颜色平滑过渡
void gui_draw_smooth_rectangle(u16 x, u16 y, u16 width, u16 height, u32 srgb, u32 ergb);	//画颜色平滑过渡的矩形/线条
void gui_fill_rectangle(u16 x0, u16 y0, u16 width, u16 height, u16 color);				//填充区域
void gui_fill_circle(u16 x0, u16 y0, u16 r, u16 color);
void gui_draw_ellipse(u16 x0, u16 y0, u16 rx, u16 ry, u16 color);
void gui_fill_ellipse(u16 x0, u16 y0, u16 rx, u16 ry, u16 color);
void gui_draw_argrec(u16 x0, u16 y0, u16 width, u16 height, u16 color);
void gui_show_strmid(u16 x, u16 y, u16 width, u16 height, u16 color, u8 size, u8 *str);
void gui_show_ptchar(u16 x, u16 y, u16 xend, u16 yend, u8 offset, u16 color, u16 size, u8 chr, u8 mode);
void gui_show_ptfont(u16 x, u16 y, u16 xend, u16 yend, u8 offset, u16 color, u16 size, u8 *chr, u8 mode);
void gui_show_ptstr(u16 x, u16 y, u16 xend, u16 yend, u16 offset, u16 color, u8 size, u8 *str, u8 mode);
void gui_show_ptstrwhiterim(u16 x, u16 y, u16 xend, u16 yend, u16 offset, u16 color, u16 rimcolor, u8 size, u8 *str); //特效显示字符串
void gui_draw_icos(u16 x, u16 y, u8 index);
void gui_draw_icosalpha(u16 x, u16 y, u8 index);
void gui_show_num(u16 x, u16 y, u8 len, u16 color, u8 size, long long num, u8 mode);
u8 *gui_num2str(u8 *str, u32 num); //将数字转为字符串
void gui_draw_arc(u16 sx, u16 sy, u16 ex, u16 ey, u16 rx, u16 ry, u16 r, u16 color, u8 mode);

u32 gui_get_stringline(u8 *str, u16 linelenth, u8 font);
void gui_show_string(u8 *str, u16 x, u16 y, u16 width, u16 height, u8 font, u16 fcolor);
u16 gui_string_forwardgbk_count(u8 *str, u16 pos);


#endif



























