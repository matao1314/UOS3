#ifndef __MYUI_H
#define __MYUI_H
#include "bsp.h"

#define SPB_MOVE_WIN 		2 		//SPB������ⴰ��ֵ
#define SPB_MOVE_MIN		8		//SPB��Ϊ�ǻ�������Сֵ,��������Ϊ�ǻ���,���ǲ�һ���ᷭҳ	   
#define SPB_MOVE_ACT 		50 		//SPB����������ֵ,�������ֵ������з�ҳ

#define SPB_ALPHA_VAL 		18 		//SPBѡ��͸��������
#define SPB_ALPHA_COLOR		WHITE	//SPB͸��ɫ
#define SPB_FONT_COLOR 		BLUE 	//SPB������ɫ

__packed typedef struct _m_spb_icos {
    u16 x;			//ͼ�����꼰�ߴ�
    u16 y;
    u8 width;
    u8 height;
    u8 *path;		//ͼ��·��
    u8 *name;		//ͼ������
} m_spb_icos;

//SPB ������
typedef struct _m_spb_dev {
    u16 oldxpos;     			//��һ��TP��x����λ��
    u16 curxpos;     			//��ǰtp���µ�x����
    u16 curypos;     			//��ǰtp���µ�y����
    u8	spbsta;					//spb״̬
    //[7]:��һ�ΰ��±�־
    //[6]:������־;
    //[5~0]:����
    u8 selico;					//��ǰѡ�е�ͼ��.
    //0~8,��ѡ�е�ͼ����
    //����,û���κ�ͼ�걻ѡ��
    m_spb_icos icos[9];		//2ҳ,ÿҳ9��ͼ��
} m_spb_dev;
extern m_spb_dev spbdev;



void Draw_mainPage(void);
u8 icon_press_chk(void);









#endif
