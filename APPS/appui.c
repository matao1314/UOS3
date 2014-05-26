#include "piclib.h"
#include "appui.h"
#include "gui.h"

m_spb_dev   spbdev;

//����ͼ·��
const u8 *bkpic_path_tbl[] = {
    "0:/SYSTEM/SPB/BACKPIC/LEFT.jpg",
};
//icos��·����
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

//����ICOS�Ķ�Ӧ��������
const u8 *name_tab[GUI_LANGUAGE_NUM][9] = {
    {"����ͼ��", "���ֲ���", "Ӧ������", "ʱ��", "ϵͳ����", "FC��Ϸ��", "������", "���±�"},
    {"EBOOK", "PHOTOS", "MUSIC", "APP", "TIME", "SETTINGS", "FC GAMES", "RADIO", "NOTEPAD"}
};


const u8 *GUI_TBL[3] = {
    "Sure", "����", "BACK",
};

//װ��ICOS
static void Load_icos(void)
{
    u8 i, j;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 3; j++) {
            minibmp_decode(spbdev.icos[i * 3 + j].path, spbdev.icos[i * 3 + j].x + 5, spbdev.icos[i * 3 + j].y, spbdev.icos[i * 3 + j].width, spbdev.icos[i * 3 + j].height, 0, 0);
            gui_show_strmid(spbdev.icos[i * 3 + j].x, spbdev.icos[i * 3 + j].y + 67, spbdev.icos[i * 3 + j].width, 16, SPB_FONT_COLOR, 16, spbdev.icos[i * 3 + j].name); //��ʾ����
        }
    }
}

//����ѡ���ĸ�ͼ��
//sel:0~8����ǰҳ��ѡ��ico
void spb_set_sel(u8 sel)
{
    spbdev.selico = sel;
    delay_ms(30);
    gui_alphablend_area(spbdev.icos[sel].x, spbdev.icos[sel].y, spbdev.icos[sel].width, spbdev.icos[sel].height, SPB_ALPHA_COLOR, SPB_ALPHA_VAL);
    minibmp_decode(spbdev.icos[sel].path, spbdev.icos[sel].x + 5, spbdev.icos[sel].y, spbdev.icos[sel].width, spbdev.icos[sel].height, 0, 0);
    gui_show_strmid(spbdev.icos[sel].x, spbdev.icos[sel].y + 67, spbdev.icos[sel].width, 16, SPB_FONT_COLOR, 16, spbdev.icos[sel].name); //��ʾ����
}


//����������
void Draw_mainPage(void)
{
    u16 i, j;
    spbdev.oldxpos = 0;
    spbdev.curxpos = 0;
    spbdev.curypos = 0;
    spbdev.spbsta = 0;
    spbdev.selico = 0xff;
    for(i = 0; i < 2; i++) { //��
        for(j = 0; j < 3; j++) { //��
            spbdev.icos[i * 3 + j].x = 5 + j * 80;
            spbdev.icos[i * 3 + j].y = 120 + i * 100;
            spbdev.icos[i * 3 + j].width = 70;
            spbdev.icos[i * 3 + j].height = 90;
            spbdev.icos[i * 3 + j].path = (u8 *)icos_path[i * 3 + j];
            spbdev.icos[i * 3 + j].name = (u8 *)name_tab[gui_phy.language][i * 3 + j];
        }
    }
    //ָ��lcd
    gui_phy.read_point = LCD_ReadPoint;
    gui_phy.draw_point = LCD_Fast_DrawPoint;
    pic_phy.read_point = LCD_ReadPoint;
    pic_phy.draw_point = LCD_Fast_DrawPoint;
    ai_load_picfile(bkpic_path_tbl[0], 0, 0, 240, 320); //����һ��ͼƬ
    Load_icos();//����ͼ��
}

//��Ļ�������������
//����ֵ:0~8,��˫����ͼ����.
//       0xff,û���κ�ͼ�걻˫�����߰���
u8 icon_press_chk(void)
{
    u8 i = 0xff;
    u8 movecnt = 0;	//�õ���������
    tp_dev.scan(0);//ɨ��
    if(tp_dev.sta & TP_PRES_DOWN) { //�а���������

        //			printf("tp_dev.x==%d tp_dev.y==%d!\r\n",tp_dev.x,tp_dev.y);

        spbdev.curxpos = tp_dev.x;				//��¼��ǰ����
        spbdev.curypos = tp_dev.y;				//��¼��ǰ����
    }

    for(i = 0; i < 9; i++) {
        if((spbdev.curxpos > spbdev.icos[i].x) && (spbdev.curxpos < spbdev.icos[i].x + spbdev.icos[i].width) && (spbdev.curxpos > spbdev.icos[i].x) &&
                (spbdev.curypos < spbdev.icos[i].y + spbdev.icos[i].height)) {
            break;//�õ�ѡ�еı��
        }
    }

    if(i < 9) {
        if(i != spbdev.selico) { //ѡ���˲�ͬ��ͼ��,�л�ͼ��
            spb_set_sel(i);
            i = 0xff;
        } else {
            spbdev.selico = 0XFF; //������˫��,���¸�λselico.
        }
    } else {
        i = 0xff;    //��Ч�ĵ㰴.
    }
    spbdev.spbsta = 0; //��ձ�־

#if 0
    if(tp_dev.sta & TP_PRES_DOWN) { //�а���������
        if(spbdev.spbsta & 0X80) { //�Ѿ��������
            movecnt = spbdev.spbsta & 0X3F; //�õ���������
            if(gui_disabs(spbdev.curxpos, tp_dev.x) >= SPB_MOVE_WIN) { //�ƶ����ڵ���SPB_MOVE_WIN����
                if(movecnt < SPB_MOVE_MIN / SPB_MOVE_WIN) {
                    spbdev.spbsta++;    //��������1
                }
            }
        }
        spbdev.curxpos = tp_dev.x;				//��¼��ǰ����
        spbdev.curypos = tp_dev.y;				//��¼��ǰ����
        if((spbdev.spbsta & 0X80) == 0) {			//������һ�α�����
            spbdev.spbsta = 0;				 	//״̬����
            spbdev.spbsta |= 1 << 7;				//��ǰ���
            spbdev.oldxpos = tp_dev.x;			//��¼����ʱ������
        }
        //else if(spbdev.spbsta&0X40)			//�л���
        //		{
        //			if(spbdev.oldxpos>tp_dev.x) 		//x����,��Ļpos����
        //			{
        //				if(SLCD.pos<240)SLCD.pos+=spbdev.oldxpos-tp_dev.x;
        //				if(SLCD.pos>240)SLCD.pos=240;	//�����.
        //			}else 								//����,��Ļpos����
        //			{
        //				if(SLCD.pos>0)SLCD.pos-=tp_dev.x-spbdev.oldxpos;
        //				if(SLCD.pos>240)SLCD.pos=0;		//�����.
        //			}
        //			spbdev.oldxpos=tp_dev.x;
        //			SLCD.show(SLCD.pos);
        // 		}else if((gui_disabs(spbdev.curxpos,spbdev.oldxpos)>=SPB_MOVE_MIN)&&(movecnt>=SPB_MOVE_MIN/SPB_MOVE_WIN))//�������볬��SPB_MOVE_MIN,���Ҽ�⵽����Ч������������SPB_MOVE_MIN/SPB_MOVE_WIN.
        //		{
        //			spbdev.spbsta|=1<<6;//��ǻ���
        //		}  8918
    } else { //�����ɿ���
        if(spbdev.spbsta & 0x80) { //֮ǰ�а���
            if(spbdev.spbsta & 0X40) { //�л���
                //				if(SLCD.frame==1)//ԭ���ڵڶ�֡,ֻ������
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
                //				}else	   //ԭ���ڵ�һ֡,ֻ������  0��ʼ
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
                spbdev.selico = 0xff; //ȡ��spbdev.selicoԭ�ȵ�����
            } else {	//���ڵ㰴.
                for(i = 0; i < 9; i++) {
                    if((spbdev.curxpos > spbdev.icos[i].x) && (spbdev.curxpos < spbdev.icos[i].x + spbdev.icos[i].width) && (spbdev.curxpos > spbdev.icos[i].x) &&
                            (spbdev.curypos < spbdev.icos[i].y + spbdev.icos[i].height)) {
                        break;//�õ�ѡ�еı��
                    }
                }
                if(i < 9) {
                    if(i != spbdev.selico) { //ѡ���˲�ͬ��ͼ��,�л�ͼ��
                        spb_set_sel(i);
                        i = 0xff;
                    } else {
                        spbdev.selico = 0XFF; //������˫��,���¸�λselico.
                    }
                } else {
                    i = 0xff;    //��Ч�ĵ㰴.
                }
            }
        }
        spbdev.spbsta = 0; //��ձ�־
    }
#endif
    return i;
}
