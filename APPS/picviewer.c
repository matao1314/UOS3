#include "picviewer.h"
#include "piclib.h"
//#include "settings.h"

//图片浏览
u8 picviewer_play(void)
{
    DIR picdir;	//picdir专用
    FILINFO picinfo;
    u8 rval = 0;			//返回值
    u8 *pname = 0;
    u8 *fn = 0;
    u8 picsta = 0;		//ebook状态
    //0,属于文件浏览状态
    //1,顺序播放图片
    //2,暂停状态
    //3,双击,弹出返回按钮了


    u16 curindex = 0;	//当前浏览的图片文件的索引号
    u8  endecode = 0;	//使能解码
    u8 key;
    u8 tpccnt = 0;	//触屏按下次数
    u16 dtime = 0;	//延时时间
    u8 keyup = 1;		//松开标记
    u8 pictype = 0;	//图片类型

    _btn_obj *rbtn;		//返回按钮控件
    _filelistbox_obj *flistbox;
    _filelistbox_list *filelistx; 	//文件

    app_filebrower((u8 *)APP_MFUNS_CAPTION_TBL[1][gui_phy.language], 0X07); //选择目标文件,并得到目标数量
    flistbox = filelistbox_creat(0, 20, 240, 280, 1, 12);		//创建一个filelistbox
    if(flistbox == NULL) {
        rval = 1;    //申请内存失败.
    } else {
        flistbox->fliter = FLBOX_FLT_PICTURE;	//图片文件
        filelistbox_addlist(flistbox, (u8 *)APP_DISK_NAME_TBL[0][gui_phy.language], 0);		//磁盘0
        //filelistbox_addlist(flistbox,(u8*)APP_DISK_NAME_TBL[1][gui_phy.language],0);		//磁盘1
        filelistbox_draw_listbox(flistbox);
    }

    //为长文件名申请缓存区
    picinfo.lfsize = _MAX_LFN * 2 + 1;
    picinfo.lfname = gui_memin_malloc(picinfo.lfsize);
    if(picinfo.lfname == NULL) {
        rval = 1;    //申请内存失败
    } else {
        gui_memset((u8 *)picinfo.lfname, 0, picinfo.lfsize);
    }

    rbtn = btn_creat(199, 300, 40, 19, 0, 0x03); //创建文字按钮
    if(rbtn == NULL) {
        rval = 1;    //没有足够内存够分配
    } else {
        rbtn->caption = (u8 *)GUI_BACK_CAPTION_TBL[gui_phy.language];	//名字
        rbtn->font = 16;			//字体
        rbtn->bcfdcolor = WHITE;	//按下时的颜色
        rbtn->bcfucolor = WHITE;	//松开时的颜色
        btn_draw(rbtn);//画按钮
    }
    LED0 = 1; //关闭LED0
    while(rval == 0) { //主循环
        tp_dev.scan(0);
        in_obj.get_key(&tp_dev, IN_TYPE_TOUCH);	//得到按键键值
        delay_ms(5);
        if(picsta == 0) {
            filelistbox_check(flistbox, &in_obj);	//扫描文件
            if(flistbox->dbclick == 0X81) {			//双击文件了
                curindex = flistbox->selindex - flistbox->foldercnt; //得到当前图片索引号
                picsta = 1;	//图片播放状态
                endecode = 1;	//第一张图片自动播放.
                LCD_Clear(0x0);//黑屏
            }
        }
        key = btn_check(rbtn, &in_obj);
        if(key && ((rbtn->sta & 0X80) == 0)) {
            if(flistbox->dbclick != 0X81) { //在文件浏览的时候按了返回按钮,则返回上一层目录
                filelistx = filelist_search(flistbox->list, flistbox->selindex); //得到此时选中的list的信息
                if(filelistx->type == FICO_DISK) { //已经不能再往上了,则退出图片浏览
                    break;
                } else {
                    filelistbox_back(flistbox);    //退回上一层目录
                }
            }
        }
        if(endecode) {
            rval = f_opendir(&picdir, (const TCHAR *)flistbox->path); //打开选中的目录
            if(rval) {
                break;
            }
            dir_sdi(&picdir, flistbox->findextbl[curindex]);
            rval = f_readdir(&picdir, &picinfo); //读取文件信息
            if(rval) {
                break;    //打开成功
            }
            fn = (u8 *)(*picinfo.lfname ? picinfo.lfname : picinfo.fname);
            pname = gui_memin_malloc(strlen((const char *)fn) + strlen((const char *)flistbox->path) + 2); //申请内存
            if(pname == NULL) {
                break;    //申请失败
            }
            {
                pname = gui_path_name(pname, flistbox->path, fn);	//文件名加入路径
                pictype = f_typetell(pname);
                if(pictype == T_GIF) {
                    gui_show_string(fn, 5, 5, lcddev.width - 5, 12, 12, RED);    //显示GIF名字
                }
                ai_load_picfile(pname, 0, 0, 240, 320);				//播放这个图片
                if(pictype != T_GIF) {
                    gui_show_string(fn, 5, 5, lcddev.width - 5, 12, 12, RED);    //显示图片名字
                }
            }
            gui_memin_free(pname);			//释放内存
            pname = NULL;
            endecode = 0;
        }
        keyup = 1;
        tpccnt = 0;
        dtime = 0;
        while(picsta) { //按键扫描循环
            key = pic_tp_scan(picsta & 0x02);
            dtime++;
            if(dtime > 400 && (picsta == 1)) {
                key = 3;    //顺序播放状态下时间溢出,自动播放下一张图片
            }
            if(key) { //有按键按下
                dtime = 0;
                if(keyup) {
                    keyup = 0;
                    if(key == 1) { //上一幅图片
                        if(curindex) {
                            curindex--;
                        } else {
                            curindex = flistbox->filecnt - 1;
                        }
                        endecode = 1;
                        LCD_Clear(0x0);//黑屏
                        break;
                    } else if(key == 2) { //在暂停和非暂停之间切换
                        if(tpccnt) { //双击了
                            picsta = 3; //双击的时候,绝对是暂停状态
                            LED0 = 0;
                            app_gui_tcbar(0, 300, 240, 20, 0x01);	//上分界线
                            btn_draw(rbtn);//画按钮
                        } else {
                            tpccnt = 1; //标记按下了一次
                            if(picsta == 1) {
                                picsta = 2;
                                LED0 = 0;	 	//表示暂停
                            } else {
                                picsta = 1;
                                LED0 = 1;	   	//暂停结束
                            }
                        }
                    } else if(key == 3) {
                        if(curindex < (flistbox->filecnt - 1)) {
                            curindex++;
                        } else {
                            curindex = 0;
                        }
                        //						if(systemset.picmode==0)//顺序播放
                        //						{
                        //							if(curindex<(flistbox->filecnt-1))curindex++;
                        //							else curindex=0;
                        //						}else	//随机播放
                        //						{
                        //							curindex=app_get_rand(flistbox->filecnt);//随机得到下一张图片的编号
                        //						}
                        endecode = 1;
                        LCD_Clear(0x0);//黑屏
                        break;
                    }
                }
            } else {
                keyup = 1;    //标记按键松开
            }
            if(tpccnt) { //双击了
                if(dtime > 20) {
                    tpccnt = 0;    //没有发生双击
                }
            } else if(pictype == T_GIF && picsta == 2 && dtime > 3) { //按键松开,暂停状态,GIF解码中
                endecode = 1; //再次解码
                break;//gif解码的时候,且暂停的时候,循环显示图片.
            }
            if(picsta == 3) { //弹出返回按钮了
                tp_dev.scan(0);
                in_obj.get_key(&tp_dev, IN_TYPE_TOUCH);	//得到按键键值
                key = btn_check(rbtn, &in_obj);
                if(key && ((rbtn->sta & 0X80) == 0)) {
                    picsta = 0;    //回到文件浏览状态
                }
            }
            delay_ms(10);
            if(picsta == 0) { //回到文件浏览状态之前的处理
                LED0 = 1;	   				//关闭LED0
                flistbox->dbclick = 0;	//设置非文件浏览状态
                app_filebrower((u8 *)APP_MFUNS_CAPTION_TBL[1][gui_phy.language], 0X07); //选择目标文件,并得到目标数量
                btn_draw(rbtn);			//画按钮
                filelistbox_rebuild_filelist(flistbox);//重建flistbox
                // 				system_task_return=0;	//还不能退出图片浏览
                break;
            }
        }
    }
    LED0 = 1; //关闭LED0
    filelistbox_delete(flistbox);	//删除filelist
    btn_delete(rbtn);				//删除按钮
    gui_memin_free(pname);			//释放内存
    gui_memin_free(picinfo.lfname);
    return rval;
}


//在上半部分
//mode:0,没有弹出返回按钮.
//	   1,弹出返回按钮了
u8 pic_tp_scan(u8 mode)
{
    tp_dev.scan(0);
    if(tp_dev.sta & TP_PRES_DOWN) {
        if(tp_dev.y < 106) {
            return 1;    //按了上面
        }
        if(tp_dev.y < 212) {
            return 2;    //按了中间
        }
        if(tp_dev.y < 300) {
            return 3;    //按了下面
        }
        if(mode == 0) {
            return 3;    //按了下面
        }
    }
    return 0;
}






































