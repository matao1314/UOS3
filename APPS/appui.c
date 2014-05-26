#include "piclib.h"
#include "appui.h"
#include "gui.h"

m_spb_dev   spbdev;

//背景图路径
const u8 *bkpic_path_tbl[] = {
    "0:/SYSTEM/SPB/BACKPIC/LEFT.jpg",
};
//icos的路径表
const u8 *icos_path[9] = {
    "0:/SYSTEM/SPB/ICOS/ebook.bmp",
    "0:/SYSTEM/SPB/ICOS/picture.bmp",
    "0:/SYSTEM/SPB/ICOS/music.bmp",
    "0:/SYSTEM/SPB/ICOS/appstore.bmp",
    "0:/SYSTEM/SPB/ICOS/time.bmp",
    "0:/SYSTEM/SPB/ICOS/set.bmp",
    "0:/SYSTEM/SPB/ICOS/game.bmp",
    "0:/SYSTEM/SPB/ICOS/radio.bmp",
    "0:/SYSTEM/SPB/ICOS/notebook.bmp",
};

//各个ICOS的对应功能名字
const u8 *name_tab[GUI_LANGUAGE_NUM][9] = {
    {"电子图书", "音乐播放", "应用中心", "时钟", "系统设置", "FC游戏机", "收音机", "记事本"},
    {"EBOOK", "PHOTOS", "MUSIC", "APP", "TIME", "SETTINGS", "FC GAMES", "RADIO", "NOTEPAD"}
};


const u8 *GUI_TBL[3] = {
    "Sure", "返回", "BACK",
};

//装载ICOS
static void Load_icos(void)
{
    u8 i, j;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 3; j++) {
            minibmp_decode(spbdev.icos[i * 3 + j].path, spbdev.icos[i * 3 + j].x + 5, spbdev.icos[i * 3 + j].y, spbdev.icos[i * 3 + j].width, spbdev.icos[i * 3 + j].height, 0, 0);
            gui_show_strmid(spbdev.icos[i * 3 + j].x, spbdev.icos[i * 3 + j].y + 67, spbdev.icos[i * 3 + j].width, 16, SPB_FONT_COLOR, 16, spbdev.icos[i * 3 + j].name); //显示名字
        }
    }
}

//设置选中哪个图标
//sel:0~8代表当前页的选中ico
void spb_set_sel(u8 sel)
{
    spbdev.selico = sel;
    delay_ms(30);
    gui_alphablend_area(spbdev.icos[sel].x, spbdev.icos[sel].y, spbdev.icos[sel].width, spbdev.icos[sel].height, SPB_ALPHA_COLOR, SPB_ALPHA_VAL);
    minibmp_decode(spbdev.icos[sel].path, spbdev.icos[sel].x + 5, spbdev.icos[sel].y, spbdev.icos[sel].width, spbdev.icos[sel].height, 0, 0);
    gui_show_strmid(spbdev.icos[sel].x, spbdev.icos[sel].y + 67, spbdev.icos[sel].width, 16, SPB_FONT_COLOR, 16, spbdev.icos[sel].name); //显示名字
}


//主操作界面
void Draw_mainPage(void)
{
    u16 i, j;
    spbdev.oldxpos = 0;
    spbdev.curxpos = 0;
    spbdev.curypos = 0;
    spbdev.spbsta = 0;
    spbdev.selico = 0xff;
    for(i = 0; i < 2; i++) { //行
        for(j = 0; j < 3; j++) { //列
            spbdev.icos[i * 3 + j].x = 5 + j * 80;
            spbdev.icos[i * 3 + j].y = 120 + i * 100;
            spbdev.icos[i * 3 + j].width = 70;
            spbdev.icos[i * 3 + j].height = 90;
            spbdev.icos[i * 3 + j].path = (u8 *)icos_path[i * 3 + j];
            spbdev.icos[i * 3 + j].name = (u8 *)name_tab[gui_phy.language][i * 3 + j];
        }
    }
    //指向lcd
    gui_phy.read_point = LCD_ReadPoint;
    gui_phy.draw_point = LCD_Fast_DrawPoint;
    pic_phy.read_point = LCD_ReadPoint;
    pic_phy.draw_point = LCD_Fast_DrawPoint;
    ai_load_picfile(bkpic_path_tbl[0], 0, 0, 240, 320); //画第一张图片
    Load_icos();//加载图标
}

//屏幕滑动及按键检测
//返回值:0~8,被双击的图标编号.
//       0xff,没有任何图标被双击或者按下
u8 icon_press_chk(void)
{
    u8 i = 0xff;
    u8 movecnt = 0;	//得到滑动点数
    tp_dev.scan(0);//扫描
    if(tp_dev.sta & TP_PRES_DOWN) { //有按键被按下

        //			printf("tp_dev.x==%d tp_dev.y==%d!\r\n",tp_dev.x,tp_dev.y);

        spbdev.curxpos = tp_dev.x;				//记录当前坐标
        spbdev.curypos = tp_dev.y;				//记录当前坐标
    }

    for(i = 0; i < 9; i++) {
        if((spbdev.curxpos > spbdev.icos[i].x) && (spbdev.curxpos < spbdev.icos[i].x + spbdev.icos[i].width) && (spbdev.curxpos > spbdev.icos[i].x) &&
                (spbdev.curypos < spbdev.icos[i].y + spbdev.icos[i].height)) {
            break;//得到选中的编号
        }
    }

    if(i < 9) {
        if(i != spbdev.selico) { //选中了不同的图标,切换图标
            spb_set_sel(i);
            i = 0xff;
        } else {
            spbdev.selico = 0XFF; //发生了双击,重新复位selico.
        }
    } else {
        i = 0xff;    //无效的点按.
    }
    spbdev.spbsta = 0; //清空标志

#if 0
    if(tp_dev.sta & TP_PRES_DOWN) { //有按键被按下
        if(spbdev.spbsta & 0X80) { //已经被标记了
            movecnt = spbdev.spbsta & 0X3F; //得到滑动点数
            if(gui_disabs(spbdev.curxpos, tp_dev.x) >= SPB_MOVE_WIN) { //移动大于等于SPB_MOVE_WIN个点
                if(movecnt < SPB_MOVE_MIN / SPB_MOVE_WIN) {
                    spbdev.spbsta++;    //点数增加1
                }
            }
        }
        spbdev.curxpos = tp_dev.x;				//记录当前坐标
        spbdev.curypos = tp_dev.y;				//记录当前坐标
        if((spbdev.spbsta & 0X80) == 0) {			//按键第一次被按下
            spbdev.spbsta = 0;				 	//状态清零
            spbdev.spbsta |= 1 << 7;				//标记按下
            spbdev.oldxpos = tp_dev.x;			//记录按下时的坐标
        }
        //else if(spbdev.spbsta&0X40)			//有滑动
        //		{
        //			if(spbdev.oldxpos>tp_dev.x) 		//x左移,屏幕pos右移
        //			{
        //				if(SLCD.pos<240)SLCD.pos+=spbdev.oldxpos-tp_dev.x;
        //				if(SLCD.pos>240)SLCD.pos=240;	//溢出了.
        //			}else 								//右移,屏幕pos左移
        //			{
        //				if(SLCD.pos>0)SLCD.pos-=tp_dev.x-spbdev.oldxpos;
        //				if(SLCD.pos>240)SLCD.pos=0;		//溢出了.
        //			}
        //			spbdev.oldxpos=tp_dev.x;
        //			SLCD.show(SLCD.pos);
        // 		}else if((gui_disabs(spbdev.curxpos,spbdev.oldxpos)>=SPB_MOVE_MIN)&&(movecnt>=SPB_MOVE_MIN/SPB_MOVE_WIN))//滑动距离超过SPB_MOVE_MIN,并且检测到的有效滑动数不少于SPB_MOVE_MIN/SPB_MOVE_WIN.
        //		{
        //			spbdev.spbsta|=1<<6;//标记滑动
        //		}  8918
    } else { //按键松开了
        if(spbdev.spbsta & 0x80) { //之前有按下
            if(spbdev.spbsta & 0X40) { //有滑动
                //				if(SLCD.frame==1)//原来在第二帧,只能右移
                //				{
                //					if((240-SLCD.pos)>SPB_MOVE_ACT)
                //					{
                //						SLCD.move(1,5,SLCD.pos);
                //						SLCD.pos=0;
                //					}else
                //					{
                //						SLCD.move(0,5,SLCD.pos);
                //						SLCD.pos=240;
                //					}
                //				}else	   //原来在第一帧,只能左移  0开始
                //				{
                //					if(SLCD.pos>SPB_MOVE_ACT)
                //					{
                //						SLCD.move(0,5,SLCD.pos);
                //						SLCD.pos=240;
                //					}else
                //					{
                //						SLCD.move(1,5,SLCD.pos);
                //						SLCD.pos=0;
                //					}

                //	}
                spbdev.selico = 0xff; //取消spbdev.selico原先的设置
            } else {	//属于点按.
                for(i = 0; i < 9; i++) {
                    if((spbdev.curxpos > spbdev.icos[i].x) && (spbdev.curxpos < spbdev.icos[i].x + spbdev.icos[i].width) && (spbdev.curxpos > spbdev.icos[i].x) &&
                            (spbdev.curypos < spbdev.icos[i].y + spbdev.icos[i].height)) {
                        break;//得到选中的编号
                    }
                }
                if(i < 9) {
                    if(i != spbdev.selico) { //选中了不同的图标,切换图标
                        spb_set_sel(i);
                        i = 0xff;
                    } else {
                        spbdev.selico = 0XFF; //发生了双击,重新复位selico.
                    }
                } else {
                    i = 0xff;    //无效的点按.
                }
            }
        }
        spbdev.spbsta = 0; //清空标志
    }
#endif
    return i;
}
