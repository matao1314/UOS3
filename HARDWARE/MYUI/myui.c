#include "piclib.h"
#include "myui.h"
#include "gui.h"
////////////////////////////////////////////////////////////////////////////////// 	   

#define APPPLAY_EX_BACKCOLOR	0X0000			//�����ⲿ����ɫ
#define APPPLAY_IN_BACKCOLOR	0X8C51			//�����ڲ�����ɫ
#define APPPLAY_NAME_COLOR		0X001F			//��������ɫ

#define APPPLAY_ALPHA_VAL 		18 				//APPѡ��͸��������
#define APPPLAY_ALPHA_COLOR		WHITE			//APP͸��ɫ
	
#define SPB_ALPHA_VAL 		16 		//SPBѡ��͸��������

#define SPB_ALPHA_COLOR		WHITE	//SPB͸��ɫ
#define SPB_FONT_COLOR 		BLUE 	//SPB������ɫ

//icos��·����
const u8 *icos_path[]=
{

"0:/SYSTEM/SPB/ICOS/ebook.bmp",
"0:/SYSTEM/SPB/ICOS/picture.bmp",	    
"0:/SYSTEM/SPB/ICOS/music.bmp",	    
"0:/SYSTEM/SPB/ICOS/appstore.bmp",	    
"0:/SYSTEM/SPB/ICOS/time.bmp",	    

"0:/ICO/code.bmp",	    
"0:/ICO/gyro.bmp",	    
"0:/ICO/set.bmp",
"0:/ICO/light.bmp",	    
"0:/ICO/1.bmp",	    
"0:/ICO/2.bmp",	    
"0:/ICO/3.bmp",
};
const u8* GUI_TBL[3]=
{
	"Sure","����","BACK",
};
//����������
void Draw_mainPage(void)
{
_btn_obj*    rbtn;//����	
_window_obj* twin=0;//����

twin=window_creat(0,0,240,320,0,1|1<<5,16);			//��������
twin->caption="MAIN";
window_draw(twin);//��������

rbtn=btn_creat(80,180,40,19,0,0x02);//�����������ְ�ť
rbtn->caption=(u8*)GUI_TBL[0];//����
rbtn->font=16;//����		 
rbtn->bcfdcolor=WHITE;	//����ʱ����ɫ
rbtn->bcfucolor=WHITE;	//�ɿ�ʱ����ɫ
rbtn->sta=0;
btn_draw(rbtn);

gui_show_strmid(60,120,59,12,APPPLAY_NAME_COLOR,12,"������");
gui_show_strmid(160,120,59,12,APPPLAY_NAME_COLOR,12,"��̬");
gui_show_strmid(260,120,59,12,APPPLAY_NAME_COLOR,12,"����");
gui_show_strmid(360,120,59,12,APPPLAY_NAME_COLOR,12,"����");

minibmp_decode((u8*)icos_path[0],40,40,60,60,0,0);    
minibmp_decode((u8*)icos_path[1],120,40,60,60,0,0);    
minibmp_decode((u8*)icos_path[2],40,120,60,60,0,0);    
minibmp_decode((u8*)icos_path[3],120,120,60,60,0,0);    
gui_alphablend_area(40,40,59,60,SPB_ALPHA_COLOR,SPB_ALPHA_VAL);
}


