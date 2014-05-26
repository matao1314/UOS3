#ifndef __MYUI_H
#define __MYUI_H
#include "bsp.h"

#define SPB_MOVE_WIN 		2 		//SPB滑动检测窗口值
#define SPB_MOVE_MIN		8		//SPB认为是滑动的最小值,超过会认为是滑动,但是不一定会翻页	   
#define SPB_MOVE_ACT 		50 		//SPB滑动的启动值,超过这个值将会进行翻页

#define SPB_ALPHA_VAL 		18 		//SPB选中透明度设置
#define SPB_ALPHA_COLOR		WHITE	//SPB透明色
#define SPB_FONT_COLOR 		BLUE 	//SPB字体颜色

__packed typedef struct _m_spb_icos {
    u16 x;			//图标坐标及尺寸
    u16 y;
    u8 width;
    u8 height;
    u8 *path;		//图标路径
    u8 *name;		//图标名字
} m_spb_icos;

//SPB 控制器
typedef struct _m_spb_dev {
    u16 oldxpos;     			//上一次TP的x坐标位置
    u16 curxpos;     			//当前tp按下的x坐标
    u16 curypos;     			//当前tp按下的y坐标
    u8	spbsta;					//spb状态
    //[7]:第一次按下标志
    //[6]:滑动标志;
    //[5~0]:保留
    u8 selico;					//当前选中的图标.
    //0~8,被选中的图标编号
    //其他,没有任何图标被选中
    m_spb_icos icos[9];		//2页,每页9个图标
} m_spb_dev;
extern m_spb_dev spbdev;



void Draw_mainPage(void);
u8 icon_press_chk(void);









#endif
