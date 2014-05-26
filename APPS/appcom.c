#include "appcom.h"
//#include "spb.h"
//#include "appplay.h"
//#include "calculator.h"
//#include "tomcatplay.h"
//#include "settings.h"
#include "calendar.h"
//#include "paint.h"

//模式选择列表的窗体名字
const u8 *APP_MODESEL_CAPTION_TBL[GUI_LANGUAGE_NUM] = {
    "模式选择", "模式選擇", "Mode Select",
};
//提示信息的窗体名字
const u8 *APP_REMIND_CAPTION_TBL[GUI_LANGUAGE_NUM] = {
    "提示信息", "提示信息", "Remind",
};
//提醒保存的窗体名字
const u8 *APP_SAVE_CAPTION_TBL[GUI_LANGUAGE_NUM] = {
    "是否保存编辑后的文件?", "是否保存編輯后的文件?", "Do you want to save?",
};
//创建文件失败,提示是否存在SD卡? ,200的宽度
const u8 *APP_CREAT_ERR_MSG_TBL[GUI_LANGUAGE_NUM] = {
    "创建文件失败,请检查SD卡!", "創建文件失敗,請檢查SD卡!", "Creat File Failed,Check SD Card!",
};
//磁盘名字表
const u8 *APP_DISK_NAME_TBL[2][GUI_LANGUAGE_NUM] = {
    {"SD卡", "SD卡", "SD Card",},
    {"FLASH磁盘", "FLASH磁盤", "FLASH Disk",},
};
//app主要功能界面标题
const u8 *APP_MFUNS_CAPTION_TBL[APP_FUNS_NUM][GUI_LANGUAGE_NUM] = {
    {"电子图书", "電子圖書", "EBOOK",},
    {"数码相框", "數碼相框", "PHOTOS",},
    {"音乐播放器", "音樂播放器", "MUSIC PLAYER",},
    {"应用中心", "應用中心", "APPLICATIONS",},
    {"", "", "",},
    {"系统设置", "系統設置", "SYSTEM SET",},
    {"FC游戏机", "FC遊戲機", "FC PLAYER",},
    {"收音机", "收音機", "RADIO",},
    {"记事本", "記事本", "NOTEPAD",},
    {"运行器", "運行器", "EXE",},
    {"", "", "",},
    {"手写画笔", "手寫畫筆", "PAINT",},
    {"照相机", "照相機", "CAMERA",},
    {"录音机", "錄音機", "RECODER",},
    {"USB连接", "USB連接", "USB",},
    {"红外遥控", "紅外遙控", "REMOTE",},
    {"无线传书", "無線傳書", "WIRELESS",},
    {"计算器", "計算器", "CALCULATOR",},

};
#if ICOS_LOCATION==ICOS_SD_CARD//存放在SD卡  
const u8 *APP_OK_PIC = "0:/SYSTEM/APP/COMMON/ok.bmp";				//确认图标
const u8 *APP_CANCEL_PIC = "0:/SYSTEM/APP/COMMON/cancel.bmp";		//取消图标
const u8 *APP_UNSELECT_PIC = "0:/SYSTEM/APP/COMMON/unselect.bmp";	//未选中图标
const u8 *APP_SELECT_PIC = "0:/SYSTEM/APP/COMMON/select.bmp";		//选中图标
//PC2LCD2002字体取模方法:逐行式,顺向(高位在前),阴码.C51格式.
//60字体包括:
//'0'~':'+'.'+'C'+' ' 总共14个字符
const u8 *APP_ASCII_60 = "0:/SYSTEM/APP/COMMON/font60.fon";		//60*30大数字字体路径
//28字体包括:
//'0'~'9'+'.'+'-'+'A'~'F'+' ' 总共19个字符
const u8 *APP_ASCII_28 = "0:/SYSTEM/APP/COMMON/font28.fon";		//28*14大数字字体路径
const u8 *APP_VOL_PIC = "0:/SYSTEM/APP/COMMON/VOL.bmp";			//音量图片路径
#else//存放在FLASH DISK
const u8 *APP_OK_PIC = "1:/SYSTEM/APP/COMMON/ok.bmp";				//确认图标
const u8 *APP_CANCEL_PIC = "1:/SYSTEM/APP/COMMON/cancel.bmp";		//取消图标
const u8 *APP_UNSELECT_PIC = "1:/SYSTEM/APP/COMMON/unselect.bmp";	//未选中图标
const u8 *APP_SELECT_PIC = "1:/SYSTEM/APP/COMMON/select.bmp";		//选中图标
//PC2LCD2002字体取模方法:逐行式,顺向(高位在前),阴码.C51格式.
//60字体包括:
//'0'~':'+'.'+'C'+' ' 总共14个字符
const u8 *APP_ASCII_60 = "1:/SYSTEM/APP/COMMON/font60.fon";		//60*30大数字字体路径
//28字体包括:
//'0'~'9'+'.'+'-'+'A'~'F'+' ' 总共19个字符
const u8 *APP_ASCII_28 = "1:/SYSTEM/APP/COMMON/font28.fon";		//28*14大数字字体路径
const u8 *APP_VOL_PIC = "1:/SYSTEM/APP/COMMON/VOL.bmp";			//音量图片路径
#endif
////////////////////////////////伪随机数产生办法////////////////////////////////
u32 random_seed = 1;
void app_srand(u32 seed)
{
    random_seed = seed;
}
//获取伪随机数
//可以产生0~RANDOM_MAX-1的随机数
//seed:种子
//max:最大值
//返回值:0~(max-1)中的一个值
u32 app_get_rand(u32 max)
{
    random_seed = random_seed * 22695477 + 1;
    return (random_seed) % max;
}
/////////////////////////////////////////////////////////////////////////////////
//读取背景色
//x,y,width,height:背景色读取范围
//ctbl:背景色存放指针
void app_read_bkcolor(u16 x, u16 y, u16 width, u16 height, u16 *ctbl)
{
    u16 x0, y0, ccnt;
    ccnt = 0;
    for(y0 = y; y0 < y + height; y0++) {
        for(x0 = x; x0 < x + width; x0++) {
            ctbl[ccnt] = gui_phy.read_point(x0, y0); //读取颜色
            ccnt++;
        }
    }
}
//恢复背景色
//x,y,width,height:背景色还原范围
//ctbl:背景色存放指针
void app_recover_bkcolor(u16 x, u16 y, u16 width, u16 height, u16 *ctbl)
{
    u16 x0, y0, ccnt;
    ccnt = 0;
    for(y0 = y; y0 < y + height; y0++) {
        for(x0 = x; x0 < x + width; x0++) {
            gui_phy.draw_point(x0, y0, ctbl[ccnt]); //读取颜色
            ccnt++;
        }
    }
}
//2色条
//x,y,width,height:坐标及尺寸.
//mode:	设置分界线
//	    [3]:右边分界线
//		[2]:左边分界线
//		[1]:下边分界线
//		[0]:上边分界线
void app_gui_tcbar(u16 x, u16 y, u16 width, u16 height, u8 mode)
{
    u16 halfheight = height / 2;
    gui_fill_rectangle(x, y, width, halfheight, LIGHTBLUE);  			//填充底部颜色(浅蓝色)
    gui_fill_rectangle(x, y + halfheight, width, halfheight, GRAYBLUE); 	//填充底部颜色(灰蓝色)
    if(mode & 0x01) {
        gui_draw_hline(x, y, width, DARKBLUE);
    }
    if(mode & 0x02) {
        gui_draw_hline(x, y + height - 1, width, DARKBLUE);
    }
    if(mode & 0x04) {
        gui_draw_vline(x, y, height, DARKBLUE);
    }
    if(mode & 0x08) {
        gui_draw_vline(x + width - 1, y, width, DARKBLUE);
    }
}
//得到数字的位数
//num:数字
//dir:0,从高位到低位.1,从低位到高位.
//返回值:数字的位数.(最大为10位)
//注:0,的位数为0位.
u8 app_get_numlen(long long num, u8 dir)
{
#define MAX_NUM_LENTH		10		//最大的数字长度
    u8 i = 0, j;
    u8 temp = 0;
    if(dir == 0) { //从高到底
        i = MAX_NUM_LENTH - 1;
        while(1) {
            temp = (num / gui_pow(10, i)) % 10;
            if(temp || i == 0) {
                break;
            }
            i--;
        }
    } else {	//从低到高
        j = 0;
        while(1) {
            if(num % 10) {
                i = app_get_numlen(num, 0);
                return i;
            }
            if(j == (MAX_NUM_LENTH - 1)) {
                break;
            }
            num /= 10;
            j++;
        }
    }
    if(i) {
        return i + 1;
    } else if(temp) {
        return 1;
    } else {
        return 0;
    }
}

//显示单色图标
//x,y,width,height:坐标及尺寸.
//icosbase:点整位置
//color:画点的颜色.
//bkcolor:背景色
void app_show_mono_icos(u16 x, u16 y, u8 width, u8 height, u8 *icosbase, u16 color, u16 bkcolor)
{
    u16 rsize;
    u8 i, j;
    u8 temp;
    u8 t = 0;
    u16 x0 = x; //保留x的位置
    rsize = width / 8 + ((width % 8) ? 1 : 0); //每行的字节数
    for(i = 0; i < rsize * height; i++) {
        temp = icosbase[i];
        for(j = 0; j < 8; j++) {
            if(temp & 0x80) {
                gui_phy.draw_point(x, y, color);
            } else {
                gui_phy.draw_point(x, y, bkcolor);
            }
            temp <<= 1;
            x++;
            t++;			//宽度计数器
            if(t == width) {
                t = 0;
                x = x0;
                y++;
                break;
            }
        }
    }
}
//显示一个浮点数(支持负数)
//注意:这里的坐标是从右到左显示的.
//x,y:开始显示的坐标
//num:数字
//flen:小数的位数.0,没有小数部分;1,有一位小数;2,有两位小数;其他以此类推.
//clen:要清除的位数(清除前一次的痕迹)
//font:字体
//color:字体颜色.
//bkcolor:背景色
void app_show_float(u16 x, u16 y, long long num, u8 flen, u8 clen, u8 font, u16 color, u16 bkcolor)
{
    u8 offpos = 0;
    u8 ilen = 0;						//整数部分长度和小数部分的长度
    u8 negative = 0;					//负数标记
    u16 maxlen = (u16)clen * (font / 2);	//清除的长度
    gui_fill_rectangle(x - maxlen, y, maxlen, font, bkcolor); //清除之前的痕迹
    if(num < 0) {
        num = -num;
        negative = 1;
    }
    ilen = app_get_numlen(num, 0);	//得到总位数
    gui_phy.back_color = bkcolor;
    if(flen) {
        gui_show_num(x - (font / 2)*flen, y, flen, color, font, num, 0X80); //显示小数部分
        gui_show_ptchar(x - (font / 2) * (flen + 1), y, GUI_LCD_W, GUI_LCD_H, 0, color, font, '.', 0); //显示小数点
        offpos = 2 + flen;
    }
    if(ilen <= flen) {
        ilen = 1;
    } else {
        offpos = ilen + 1;
        ilen = ilen - flen;	//得到整数部分的长度.
    }
    num = num / gui_pow(10, flen); //得到整数部分
    gui_show_num(x - (font / 2)*offpos, y, ilen, color, font, num, 0X80);	//填充0显示
    if(negative) {
        gui_show_ptchar(x - (font / 2) * (offpos + 1), y, GUI_LCD_W, GUI_LCD_H, 0, color, font, '-', 0);    //显示符号
    }
}

//topname:浏览的时候要显示的名字
//mode:
//[0]:0,不显示上方色条;1,显示上方色条
//[1]:0,不显示下方色条;1,显示下方色条
//[2]:0,不显示名字;1,显示名字
//[3~7]:保留
//返回值:无
void app_filebrower(u8 *topname, u8 mode)
{
    if(mode & 0X01) {
        app_gui_tcbar(0, 0, 240, 20, 0x02);    //下分界线
    }
    if(mode & 0X02) {
        app_gui_tcbar(0, 300, 240, 20, 0x01);    //上分界线
    }
    if(mode & 0X04) {
        gui_show_strmid(0, 0, 240, 20, WHITE, 16, topname);
    }
}
//在指定位置显示一个大字符
//字符取模方法:逐行式,顺向(高位在前),阴码.C51格式.
//fontbase:字库地址
//x,y:坐标
//chr:范围根据字库而定
//size:尺寸.使用的有60/28
//color:字体颜色
//bkcolor:背景色
void app_showbigchar(u8 *fontbase, u16 x, u16 y, u8 chr, u8 size, u16 color, u16 bkcolor)
{
    u8 n, t;
    u8 temp;
    u16 offset;
    u16 colortemp = POINT_COLOR;
    u16 x0 = x;
    if(size == 60) { //60字体
        if(chr >= '0' && chr <= ':') {
            offset = chr - '0';
        } else if(chr == '.') {
            offset = 11;
        } else if(chr == 'C') {
            offset = 12;
        } else if(chr == ' ') {
            offset = 13;
        } else {
            return;    //不能显示的字符
        }
        offset *= 240;		//偏移(每个字符点阵占用240字节)
        for(n = 0; n < 240; n++) {
            temp = fontbase[offset + n];
            for(t = 0; t < 8; t++) {
                if(temp & 0x80) {
                    gui_phy.draw_point(x, y, color);
                } else {
                    gui_phy.draw_point(x, y, bkcolor);
                }
                temp <<= 1;
                x++;
                if(((n % 4) == 3) && t == 5) {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    } else {	//28字体
        if(chr >= '0' && chr <= '9') {
            offset = chr - '0';
        } else if(chr == '.') {
            offset = 10;
        } else if(chr == '-') {
            offset = 11;
        } else if(chr >= 'A' && chr <= 'F') {
            offset = 12 + chr - 'A';
        } else if(chr == ' ') {
            offset = 18;
        } else {
            return;    //不能显示的字符
        }
        offset *= 56;			//偏移(每个字符点阵占用56字节)
        for(n = 0; n < 56; n++) {
            temp = fontbase[offset + n];
            for(t = 0; t < 8; t++) {
                if(temp & 0x80) {
                    gui_phy.draw_point(x, y, color);
                } else {
                    gui_phy.draw_point(x, y, bkcolor);
                }
                temp <<= 1;
                x++;
                if(((n % 2) == 1) && t == 5) {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
    POINT_COLOR = colortemp;
}
//在指定位置开始显示字符串
//fontbase:字库地址
//*p:字符串
//x,y:开始位置
//size:尺寸.60/28
//color,bkcolor:颜色和背景色
void app_showbigstring(u8 *fontbase, u16 x, u16 y, const u8 *p, u8 size, u16 color, u16 bkcolor)
{
    while(*p != '\0') {
        app_showbigchar(fontbase, x, y, *p, size, color, bkcolor);
        x += size / 2;
        p++;
    }
}
//显示大个数字
//fontbase:字库地址
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//color:颜色
//num:数值(0~4294967295);
void app_showbignum(u8 *fontbase, u16 x, u16 y, u32 num, u8 len, u8 size, u16 color, u16 bkcolor)
{
    u8 t, temp;
    u8 enshow = 0;
    for(t = 0; t < len; t++) {
        temp = (num / gui_pow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1)) {
            if(temp == 0) {
                app_showbigchar(fontbase, x + (size / 2)*t, y, ' ', size, color, bkcolor);
                continue;
            } else {
                enshow = 1;
            }

        }
        app_showbigchar(fontbase, x + (size / 2)*t, y, temp + '0', size, color, bkcolor);
    }
}
//显示2个字符
//x,y :起点坐标
//size:字体尺寸
//color:颜色
//bkcolor:背景色
//num:数值(0~99)
void app_showbig2num(u8 *fontbase, u16 x, u16 y, u8 num, u8 size, u16 color, u16 bkcolor)
{
    app_showbigchar(fontbase, x, y, (num / 10) % 10 + '0', size, color, bkcolor); //显示十位
    app_showbigchar(fontbase, x + size / 2, y, num % 10 + '0', size, color, bkcolor);	//显示个位
}
//在一个区域中间显示数字
//x,y,width,height:区域
//num:要显示的数字
//len:位数
//size:字体尺寸
//ptcolor,bkcolor:画笔颜色以及背景色
void app_show_nummid(u16 x, u16 y, u16 width, u16 height, u32 num, u8 len, u8 size, u16 ptcolor, u16 bkcolor)
{
    u16 numlen;
    u8 xoff, yoff;
    numlen = (size / 2) * len; //数字长度
    if(numlen > width || size > height) {
        return;
    }
    xoff = (width - numlen) / 2;
    yoff = (height - size) / 2;
    POINT_COLOR = ptcolor;
    BACK_COLOR = bkcolor;
    LCD_ShowxNum(x + xoff, y + yoff, num, len, size, 0X80); //显示这个数字
}
//画一条平滑过渡的彩色线(或矩形)
//以中间为间隔,两边展开
//x,y,width,height:线条的坐标尺寸
//sergb,mrgb:起止颜色和中间颜色
void app_draw_smooth_line(u16 x, u16 y, u16 width, u16 height, u32 sergb, u32 mrgb)
{
    gui_draw_smooth_rectangle(x, y, width / 2, height, sergb, mrgb);	   		//前半段渐变
    gui_draw_smooth_rectangle(x + width / 2, y, width / 2, height, mrgb, sergb); //后半段渐变
}

//判断触摸屏当前值是不是在某个区域内
//tp:触摸屏
//x,y,width,height:坐标和尺寸
//返回值:0,不在区域内;1,在区域内.
u8 app_tp_is_in_area(_m_tp_dev *tp, u16 x, u16 y, u16 width, u16 height)
{
    if(tp->x <= (x + width) && tp->x >= x && tp->y <= (y + height) && tp->y >= y) {
        return 1;
    } else {
        return 0;
    }
}
//显示条目
//x,y,itemwidth,itemheight:条目坐标及尺寸
//name:条目名字
//icopath:图标路径
void app_show_items(u16 x, u16 y, u16 itemwidth, u16 itemheight, u8 *name, u8 *icopath, u16 color, u16 bkcolor)
{
    gui_fill_rectangle(x, y, itemwidth, itemheight, bkcolor);	//填充背景色
    gui_show_ptstr(x + 5, y + (itemheight - 16) / 2, x + itemwidth - 10 - APP_ITEM_ICO_SIZE - 5, y + itemheight, 0, color, 16, name, 1);	//显示条目名字
    if(icopath) {
        minibmp_decode(icopath, x + itemwidth - 10 - APP_ITEM_ICO_SIZE, y + (itemheight - APP_ITEM_ICO_SIZE) / 2, APP_ITEM_ICO_SIZE, APP_ITEM_ICO_SIZE, 0, 0);    //解码APP_ITEM_ICO_SIZE*APP_ITEM_ICO_SIZE的bmp图片
    }
}
//获得当前条目的图标路径
//mode:0,单选模式;1,多选模式
//selpath,unselpath:选中和非选中的图标路径
//selx:选中图标编号(单选模式)/有效图标掩码(多选模式)
//index:当前条目编号
u8 *app_get_icopath(u8 mode, u8 *selpath, u8 *unselpath, u8 selx, u8 index)
{
    u8 *icopath = 0;
    if(mode) { //多选模式
        if(selx & (1 << index)) {
            icopath = selpath;    //是选中的条目
        } else {
            icopath = unselpath;    //是非选中的条目
        }
    } else {
        if(selx == index) {
            icopath = selpath;    //是选中的条目
        } else {
            icopath = unselpath;    //是非选中的条目
        }
    }
    return icopath;
}
//条目选择
//x,y,width,height:坐标尺寸(width最小为150,height最小为72)
//items[]:条目名字集
//itemsize:总条目数(最大不超过8个)
//selx:结果.多选模式时,对应各项的选择情况.单选模式时,对应选择的条目.
//mode:
//[7]:0,无OK按钮;1,有OK按钮
//[6]:0,不读取背景色;1,读取背景色
//[5]:0,单选模式;1,多选模式
//[4]:0,不加载图表;1,加载图标
//[3:0]:保留
//caption:窗口名字
//返回值:0,ok;其他,取消或者错误.
u8 app_items_sel(u16 x, u16 y, u16 width, u16 height, u8 *items[], u8 itemsize, u8 *selx, u8 mode, u8 *caption)
{
    u8 rval = 0, res;
    u8 selsta = 0;	//选中状态为0,
    //[7]:标记是否已经记录第一次按下的条目;
    //[6:4]:保留
    //[3:0]:第一次按下的条目
    u16 i;

    u8 temp;
    u16 itemheight = 0;		//每个条目的高度
    u16 itemwidth = 0;		//每个条目的宽度
    u8 *unselpath = 0;		//未选中的图标的路径
    u8 *selpath = 0;			//选中图标的路径
    u8 *icopath = 0;

    _window_obj *twin = 0;	//窗体
    _btn_obj *okbtn = 0;		//确定按钮
    _btn_obj *cancelbtn = 0; //取消按钮

    if(itemsize > 8 || itemsize < 1) {
        return 0xff;    //条目数错误
    }
    if(width < 150 || height < 72) {
        return 0xff;    //尺寸错误
    }

    itemheight = (height - 72) / itemsize - 1;	//得到每个条目的高度
    itemwidth = width - 10;					//每个条目的宽度

    twin = window_creat(x, y, width, height, 0, 1 | (1 << 5) | ((1 << 6)&mode), 16); //创建窗口
    if(mode & (1 << 7)) {
        temp = (width - APP_ITEM_BTN1_WIDTH * 2) / 3;
        okbtn = btn_creat(x + temp, y + height - APP_ITEM_BTN_HEIGHT - 5, APP_ITEM_BTN1_WIDTH, APP_ITEM_BTN_HEIGHT, 0, 0x02);							//创建OK按钮
        cancelbtn = btn_creat(x + APP_ITEM_BTN1_WIDTH + temp * 2, y + height - APP_ITEM_BTN_HEIGHT - 5, APP_ITEM_BTN1_WIDTH, APP_ITEM_BTN_HEIGHT, 0, 0x02); //创建CANCEL按钮
        if(twin == NULL || okbtn == NULL || cancelbtn == NULL) {
            rval = 1;
        } else {
            okbtn->caption = (u8 *)GUI_OK_CAPTION_TBL[gui_phy.language]; //确认
            okbtn->bkctbl[0] = 0X8452; //边框颜色
            okbtn->bkctbl[1] = 0XAD97; //第一行的颜色
            okbtn->bkctbl[2] = 0XAD97; //上半部分颜色
            okbtn->bkctbl[3] = 0X8452; //下半部分颜色
        }
    } else {
        temp = (width - APP_ITEM_BTN2_WIDTH) / 2;
        cancelbtn = btn_creat(x + temp, y + height - APP_ITEM_BTN_HEIGHT - 5, APP_ITEM_BTN2_WIDTH, APP_ITEM_BTN_HEIGHT, 0, 0x02);	//创建CANCEL按钮
        if(twin == NULL || cancelbtn == NULL) {
            rval = 1;
        }
    }
    if(rval == 0) { //之前的操作正常
        twin->caption = caption;
        twin->windowbkc = APP_WIN_BACK_COLOR;
        cancelbtn->caption = (u8 *)GUI_CANCEL_CAPTION_TBL[gui_phy.language]; //取消
        cancelbtn->bkctbl[0] = 0X8452; //边框颜色
        cancelbtn->bkctbl[1] = 0XAD97; //第一行的颜色
        cancelbtn->bkctbl[2] = 0XAD97; //上半部分颜色
        cancelbtn->bkctbl[3] = 0X8452; //下半部分颜色

        if(mode & (1 << 4)) { //需要加载图标
            if(mode & (1 << 5)) { //多选模式
                unselpath = (u8 *)APP_CANCEL_PIC;		//未选中的图标的路径
                selpath = (u8 *)APP_OK_PIC;			//选中图标的路径
            } else {	  //单选模式
                unselpath = (u8 *)APP_UNSELECT_PIC;	//未选中的图标的路径
                selpath = (u8 *)APP_SELECT_PIC;		//选中图标的路径
            }
        }
        window_draw(twin);				//画出窗体
        btn_draw(cancelbtn);			//画按钮
        if(mode & (1 << 7)) {
            btn_draw(okbtn);    //画按钮
        }
        for(i = 0; i < itemsize; i++) {
            icopath = app_get_icopath(mode & (1 << 5), selpath, unselpath, *selx, i); //得到图标路径
            app_show_items(x + 5, y + 32 + i * (itemheight + 1), itemwidth, itemheight, items[i], icopath, BLACK, twin->windowbkc); //显示所有的条目
            if((i + 1) != itemsize) {
                app_draw_smooth_line(x + 5, y + 32 + (i + 1) * (itemheight + 1) - 1, itemwidth, 1, 0Xb1ffc4, 0X1600b1);    //画彩线
            }
        }
        while(rval == 0) {
            tp_dev.scan(0);
            in_obj.get_key(&tp_dev, IN_TYPE_TOUCH);	//得到按键键值
            //			delay_ms(1000/OS_TICKS_PER_SEC);		//延时一个时钟节拍
            //			if(system_task_return){rval=1;break;};	//TPAD返回
            if(mode & (1 << 7)) {
                res = btn_check(okbtn, &in_obj);		//确认按钮检测
                if(res) {
                    if((okbtn->sta & 0X80) == 0) { //有有效操作
                        rval = 0XFF;
                        break;//确认按钮
                    }
                }
            }
            res = btn_check(cancelbtn, &in_obj);		//取消按钮检测
            if(res) {
                if((cancelbtn->sta & 0X80) == 0) { //有有效操作
                    rval = 1;
                    break;//取消按钮
                }
            }
            temp = 0XFF; //标记量,如果为0XFF,在松开的时候,说明是不在有效区域内的.如果非0XFF,则表示TP松开的时候,是在有效区域内.
            for(i = 0; i < itemsize; i++) {
                if(tp_dev.sta & TP_PRES_DOWN) { //触摸屏被按下
                    if(app_tp_is_in_area(&tp_dev, x + 5, y + 32 + i * (itemheight + 1), itemwidth, itemheight)) { //判断某个时刻,触摸屏的值是不是在某个区域内
                        if((selsta & 0X80) == 0) { //还没有按下过
                            icopath = app_get_icopath(mode & (1 << 5), selpath, unselpath, *selx, i); //得到图标路径
                            app_show_items(x + 5, y + 32 + i * (itemheight + 1), itemwidth, itemheight, items[i], icopath, BLACK, APP_ITEM_SEL_BKCOLOR); //反选条目
                            selsta = i;		//记录第一次按下的条目
                            selsta |= 0X80;	//标记已经按下过了
                        }
                        break;
                    }
                } else { //触摸屏被松开了
                    if(app_tp_is_in_area(&tp_dev, x + 5, y + 32 + i * (itemheight + 1), itemwidth, itemheight)) { //判断某个时刻,触摸屏的值是不是在某个区域内
                        temp = i;
                        break;
                    }
                }
            }
            if((selsta & 0X80) && (tp_dev.sta & TP_PRES_DOWN) == 0) { //有按下过,且按键松开了
                if((selsta & 0X0F) == temp) { //松开之前的坐标也是在按下时的区域内.
                    if(mode & (1 << 5)) { //多选模式,执行取反操作
                        if((*selx) & (1 << temp)) {
                            *selx &= ~(1 << temp);
                        } else {
                            *selx |= 1 << temp;
                        }
                    } else { //单选模式
                        app_show_items(x + 5, y + 32 + (*selx) * (itemheight + 1), itemwidth, itemheight, items[*selx], unselpath, BLACK, twin->windowbkc); //取消之前选择的条目
                        *selx = temp;
                    }
                } else {
                    temp = selsta & 0X0F;    //得到当时按下的条目号
                }
                icopath = app_get_icopath(mode & (1 << 5), selpath, unselpath, *selx, temp); //得到图标路径
                app_show_items(x + 5, y + 32 + temp * (itemheight + 1), itemwidth, itemheight, items[temp], icopath, BLACK, twin->windowbkc); //反选条目
                selsta = 0; //取消
            }
        }
    }
    window_delete(twin);
    btn_delete(okbtn);
    btn_delete(cancelbtn);
    //	system_task_return=0;
    if(rval == 0XFF) {
        return 0;
    }
    return rval;
}

//新建选择框
//sel:当前选中的条目
//top:当前最顶部的条目
//caption:选择框名字
//items[]:条目名字集
//itemsize:总条目数
//返回值:[7]:0,按下的是返回按键,或者发生了错误;1,按下了确认按键,或者双击了选中的条目.
//     [6:0]:0,表示无错误;非零,错误代码.
u8 app_listbox_select(u8 *sel, u8 *top, u8 *caption, u8 *items[], u8 itemsize)
{
    u8  res;
    u8 rval = 0;			//返回值
    u16 i;

    _btn_obj *rbtn = 0;			//返回按钮控件
    _btn_obj *okbtn = 0;			//确认按钮控件
    _listbox_obj *tlistbox;	//listbox

    if(*sel >= itemsize || *top >= itemsize) {
        return 2;    //参数错误/参数非法
    }

    app_filebrower(caption, 0X07);				//显示标题
    tlistbox = listbox_creat(0, 20, 240, 280, 1, 16);	//创建一个filelistbox
    if(tlistbox == NULL) {
        rval = 1;    //申请内存失败.
    } else {	//添加条目
        for(i = 0; i < itemsize; i++) {
            res = listbox_addlist(tlistbox, items[i]);
            if(res) {
                rval = 1;
                break;
            }
        }
    }
    if(rval == 0) { //成功添加了条目
        tlistbox->scbv->topitem = *top;
        tlistbox->selindex = *sel;
        listbox_draw_listbox(tlistbox);
        rbtn = btn_creat(199, 300, 40, 19, 0, 0x03);	//创建返回文字按钮
        okbtn = btn_creat(0, 300, 40, 19, 0, 0x03);	//创建确认文字按钮
        if(rbtn == NULL || okbtn == NULL) {
            rval = 1;    //没有足够内存够分配
        } else {
            rbtn->caption = (u8 *)GUI_BACK_CAPTION_TBL[gui_phy.language];	//名字
            rbtn->font = 16;			//字体
            rbtn->bcfdcolor = WHITE;	//按下时的颜色
            rbtn->bcfucolor = WHITE;	//松开时的颜色
            btn_draw(rbtn);//画按钮

            okbtn->caption = (u8 *)GUI_OK_CAPTION_TBL[gui_phy.language];	//名字
            okbtn->font = 16;			//字体
            okbtn->bcfdcolor = WHITE;	//按下时的颜色
            okbtn->bcfucolor = WHITE;	//松开时的颜色
            btn_draw(okbtn);//画按钮
        }
    }
    while(rval == 0) {
        tp_dev.scan(0);
        in_obj.get_key(&tp_dev, IN_TYPE_TOUCH);	//得到按键键值
        //		delay_ms(1000/OS_TICKS_PER_SEC);		//延时一个时钟节拍
        // 		if(system_task_return)break;			//TPAD返回
        res = btn_check(rbtn, &in_obj);		 //返回按钮检测
        if(res) {
            if(((rbtn->sta & 0X80) == 0)) {
                break;    //退出
            }
        }
        res = btn_check(okbtn, &in_obj); //确认按钮检测
        if(res) {
            if(((okbtn->sta & 0X80) == 0)) { //按钮状态改变了
                *top = tlistbox->scbv->topitem; //记录退出时选择的条目
                *sel = tlistbox->selindex;
                rval |= 1 << 7; //标记双击按下了
            }
        }
        listbox_check(tlistbox, &in_obj);	//扫描
        if(tlistbox->dbclick == 0X80) { //双击了
            *top = tlistbox->scbv->topitem; //记录退出时选择的条目
            *sel = tlistbox->selindex;
            rval |= 1 << 7; //标记双击按下了
        }
    }
    listbox_delete(tlistbox);		//删除listbox
    btn_delete(okbtn);				//删除按钮
    btn_delete(rbtn);				//删除按钮
    return rval;
}

//系统总共需要的图标/图片/系统文件有141个,其中SPB部分占20个.其余121个为APP各功能占用
//这还不包括SYSTEM/FONT文件夹内的字体文件.
//141个文件总大小:1,033,804 字节(0.98MB)
//3个字体文件总大小:1,514,984 字节(1.44MB)
//检测所有的系统文件是否正常
//返回值:0,正常
//    其他,错误代码
u8 app_system_file_check(void)
{
    u8 i;
    u8 rval = 0;
    u8 res = 0;
    FIL *f_check;
    f_check = (FIL *)gui_memin_malloc(sizeof(FIL));	//开辟FIL字节的内存区域
    if(f_check == NULL) {
        rval = 0XFF;    //申请失败
    }
#if 0
    while(rval == 0) {
        //SPB文件检测,20个.
        rval++;
        res = f_open(f_check, (const TCHAR *)spb_bkpic_path_tbl[0], FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)spb_bkpic_path_tbl[1], FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);        //关闭文件
        for(i = 0; i < 9; i++) {
            res = f_open(f_check, (const TCHAR *)spb_icos_path_tbl[0][i], FA_READ); //只读方式打开文件
            if(res) {
                break;    //打开失败
            }
            f_close(f_check);    //关闭文件
        }
        rval += i;
        if(i < 9) {
            rval++;
            break;
        }
        for(i = 0; i < 9; i++) {
            res = f_open(f_check, (const TCHAR *)spb_icos_path_tbl[1][i], FA_READ); //只读方式打开文件
            if(res) {
                break;    //打开失败
            }
            f_close(f_check); 	//关闭文件
        }
        rval += i;
        if(i < 9) {
            rval++;
            break;
        }
        //COMMON文件检测,7个
        rval++;
        res = f_open(f_check, (const TCHAR *)APP_OK_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)APP_CANCEL_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)APP_UNSELECT_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)APP_SELECT_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)APP_ASCII_60, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)APP_ASCII_28, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)APP_VOL_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        //MP3文件检测,15个
        rval++;
        res = f_open(f_check, (const TCHAR *)FLAC_PATCH_PATH, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)SPEC_PATCH_PATH, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)MP3_DEMO_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)MP3_PLAYR_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        rval++;
        res = f_open(f_check, (const TCHAR *)MP3_PAUSEP_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        for(i = 0; i < 5; i++) {
            res = f_open(f_check, (const TCHAR *)MP3_BTN_PIC_TBL[0][i], FA_READ); //只读方式打开文件
            if(res) {
                break;    //打开失败
            }
            f_close(f_check);    //关闭文件
        }
        rval += i;
        if(i < 5) {
            rval++;
            break;
        }
        for(i = 0; i < 5; i++) {
            res = f_open(f_check, (const TCHAR *)MP3_BTN_PIC_TBL[1][i], FA_READ); //只读方式打开文件
            if(res) {
                break;    //打开失败
            }
            f_close(f_check);    //关闭文件
        }
        rval += i;
        if(i < 5) {
            rval++;
            break;
        }
        //检测应用程序16个图标
        for(i = 0; i < 16; i++) {
            res = f_open(f_check, (const TCHAR *)appplay_icospath_tbl[i], FA_READ); //只读方式打开文件
            if(res) {
                break;    //打开失败
            }
            f_close(f_check);    //关闭文件
        }
        rval += i;
        if(i < 16) {
            rval++;
            break;
        }
        //检测计算器58个图标
        for(i = 0; i < 29; i++) {
            res = f_open(f_check, (const TCHAR *)CALC_UP_BTN_TBL[i], FA_READ); //只读方式打开文件
            if(res) {
                break;    //打开失败
            }
            f_close(f_check);    //关闭文件
        }
        rval += i;
        if(i < 29) {
            rval++;
            break;
        }
        for(i = 0; i < 29; i++) {
            res = f_open(f_check, (const TCHAR *)CALC_DOWN_BTN_TBL[i], FA_READ); //只读方式打开文件
            if(res) {
                break;    //打开失败
            }
            f_close(f_check);    //关闭文件
        }
        rval += i;
        if(i < 29) {
            rval++;
            break;
        }
        //检测TOM猫1个图标
        rval++;
        res = f_open(f_check, (const TCHAR *)TOMCAT_DEMO_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        //检测画图1个图标
        rval++;
        res = f_open(f_check, (const TCHAR *)PAINT_COLOR_TBL_PIC, FA_READ); //只读方式打开文件
        if(res) {
            break;    //打开失败
        }
        f_close(f_check);		//关闭文件
        printf("\r\ntotal system files:%d\r\n", rval);
        rval = 0;
        break;
    }
#endif
    gui_memin_free(f_check);//释放内存
    return rval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//一下代码仅用于实现SYSTEM文件夹更新
const u8 *APP_SYSTEM_APPPATH = "0:/SYSTEM/APP";	//APP文件夹路径
const u8 *APP_SYSTEM_FONTPATH = "0:/SYSTEM/FONT";	//FONT文件夹路径
const u8 *APP_SYSTEM_SPBPATH = "0:/SYSTEM/SPB";	//SPB文件夹路径
const u8 *APP_SYSTEM_DSTPATH = "1:/SYSTEM";		//系统文件目标路径

//文件复制信息提示
//mode:
//[0]:更新文件名
//[1]:更新百分比pct
//[2]:更新文件夹
//[3~7]:保留
//返回值:0,正常;
//       1,结束复制
static u16 cpdmsg_x;
static u16 cpdmsg_y;


//系统启动的时候,用于显示更新进度
//*pname:更新文件名字
//pct:百分比
//mode:模式
//[0]:更新文件名
//[1]:更新百分比pct
//[2]:更新文件夹
//[3~7]:保留
//返回值:0,正常;
//       1,结束复制
u8 app_boot_cpdmsg(u8 *pname, u8 pct, u8 mode)
{
    if(mode & 0X01) {
        LCD_Fill(cpdmsg_x + 9 * 6, cpdmsg_y, cpdmsg_x + 21 * 6, cpdmsg_y + 12, BLACK);	//填充底色
        LCD_ShowString(cpdmsg_x + 9 * 6, cpdmsg_y, 6 * 12, 12, 12, pname);			 	//显示文件名
        printf("\r\nCopy File:%s\r\n", pname);
    }
    if(mode & 0X04) {
        printf("Copy Folder:%s\r\n", pname);
    }
    if(mode & 0X02) { //更新百分比
        LCD_ShowString(cpdmsg_x + 25 * 6, cpdmsg_y, 240, 320, 12, "%");
        LCD_ShowNum(cpdmsg_x + 22 * 6, cpdmsg_y, pct, 3, 12); //显示数值
        printf("File Copyed:%d\r\n", pct);
    }
    return 0;
}
//设置app_boot_cpdmsg的显示坐标
void app_boot_cpdmsg_set(u16 x, u16 y)
{
    cpdmsg_x = x;
    cpdmsg_y = y;
}
//系统更新
//返回值:0,正常
//    其他,错误,0XFF强制退出了
u8 app_system_update(u8(*fcpymsg)(u8 *pname, u8 pct, u8 mode))
{
    u32 totsize = 0;
    u32 cpdsize = 0;
    u8 res = 0;
    totsize += exf_fdsize((u8 *)APP_SYSTEM_APPPATH); //得到三个文件夹的总大小
    totsize += exf_fdsize((u8 *)APP_SYSTEM_FONTPATH);
    totsize += exf_fdsize((u8 *)APP_SYSTEM_SPBPATH);
    printf("totsize:%d\r\n", totsize);
    f_mkdir((const TCHAR *)APP_SYSTEM_DSTPATH);//强制创建目标文件夹
    res = exf_fdcopy(fcpymsg, (u8 *)APP_SYSTEM_APPPATH, (u8 *)APP_SYSTEM_DSTPATH, &totsize, &cpdsize, 1);
    if(res) {
        if(res != 0xff) {
            return 1;    //第一阶段复制出错
        } else {
            return 0XFF;    //强制退出
        }
    }
    res = exf_fdcopy(fcpymsg, (u8 *)APP_SYSTEM_FONTPATH, (u8 *)APP_SYSTEM_DSTPATH, &totsize, &cpdsize, 1);
    if(res) {
        if(res != 0xff) {
            return 1;    //第二阶段复制出错
        } else {
            return 0XFF;    //强制退出
        }
    }
    res = exf_fdcopy(fcpymsg, (u8 *)APP_SYSTEM_SPBPATH, (u8 *)APP_SYSTEM_DSTPATH, &totsize, &cpdsize, 1);
    if(res) {
        if(res != 0xff) {
            return 1;    //第三阶段复制出错
        } else {
            return 0XFF;    //强制退出
        }
    }
    return 0;
}
//得到STM32的序列号
//sn0,sn1,sn2:3个固有序列号
void app_getstm32_sn(u32 *sn0, u32 *sn1, u32 *sn2)
{
    *sn0 = *(vu32 *)(0x1FFFF7E8);
    *sn1 = *(vu32 *)(0x1FFFF7EC);
    *sn2 = *(vu32 *)(0x1FFFF7F0);
}
//打印SN
void app_usmart_getsn(void)
{
    u32 sn0, sn1, sn2;
    app_getstm32_sn(&sn0, &sn1, &sn2);
    printf("\r\nSerial Number:%X%X%X\r\n", sn0, sn1, sn2);
}
//得到版本信息
//buf:版本缓存区(最少需要6个字节,如保存:V1.00)
//ver:版本宏定义
//len:版本位数.1,代表只有1个位的版本,V1;2,代表2个位版本,V1.0;3,代表3个位版本,V1.00;
void app_get_version(u8 *buf, u32 ver, u8 len)
{
    u8 i = 0;
    buf[i++] = 'V';
    if(len == 1) {
        buf[i++] = ver % 10 + '0';
    } else if(len == 2) {
        buf[i++] = (ver / 10) % 10 + '0';
        buf[i++] = '.';
        buf[i++] = ver % 10 + '0';
    } else {
        buf[i++] = (ver / 100) % 10 + '0';
        buf[i++] = '.';
        buf[i++] = (ver / 10) % 10 + '0';
        buf[i++] = ver % 10 + '0';
    }
    buf[i] = 0; //加入结束符
}

//初始化各个系统参数
//包括系统设置,闹钟数据,收音机数据等
u8 app_system_parameter_init(void)
{
    //	sysset_read_para(&systemset);		//读取系统设置信息
    //	vs10xx_read_para(&vsset);			//读取VS10XX设置数据
    //	calendar_read_para(&alarm);			//读取闹钟信息
#if 0
    if(systemset.saveflag != 0X0A) {	//之前没有保存过
        systemset.syslanguage = 0;		//默认为简体中文
        systemset.lcdbklight = 110;		//背光默认最亮
        systemset.picmode = 0;			//图片顺序播放
        systemset.mp3mode = 0;			//MP3顺序播放
        systemset.fmtxmode = 1;			//FM发射开启
        systemset.fmrxmode = 0;			//FM关闭后台播放
        systemset.fmtxfreq = 936;			//FM发射频率 93.6MHz
        systemset.audiosel = 3;			//设置为无声通道
        systemset.saveflag = 0X0A;  		//设置保存标记
        sysset_save_para(&systemset);	//保存系统设置信息
    }
#endif
    if(vsset.saveflag != 0X0A) {			//之前没有保存过
        vsset.mvol = 220;					//音量:220
        vsset.bflimit = 6;				//低音上线 60Hz
        vsset.bass = 15;					//低音提升 15dB
        vsset.tflimit = 10;				//高音下限 10Khz
        vsset.treble = 15; 				//高音提升 10.5dB
        vsset.effect = 0;					//空间效果	0
        vsset.saveflag = 0X0A;  			//设置保存标记
        //		vs10xx_save_para(&vsset);		//保存VS10XX设置信息
    }
    if(alarm.saveflag != 0X0A) {			//之前没有保存过
        alarm.weekmask = 0;				//闹钟响铃掩码为0
        alarm.ringsta = 0;				//闹铃状态及铃声标志为0
        alarm.hour = 0;					//闹铃时间设置为00:00
        alarm.min = 0;
        alarm.saveflag = 0X0A;  			//设置保存标记
        calendar_save_para(&alarm);		//保存闹钟设置信息
    }
    f_mkdir("0:TEXT");		//强制创建文件夹,给记事本用
    f_mkdir("0:PAINT");		//强制创建文件夹,给画图用
    // 	gui_phy.language=systemset.syslanguage;			//设置语言
    //	LCD_BLPWM_VAL=systemset.lcdbklight;				//设置背光
    return 0;
}












