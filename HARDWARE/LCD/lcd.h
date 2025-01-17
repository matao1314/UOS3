#ifndef __ILI93XX_H
#define __ILI93XX_H
#include "sys.h"
#include "stdlib.h"
/**********************
X0X1X2X3X4X5X6X7X8X9X10
Y1
Y2
Y3
Y4
Y5
Y6
Y7
Y8
Y9
Y10
***********************/
//////////////////////////////////////////////////////////////////////////////////

//LCD重要参数集
typedef struct {
    u16 width;			//LCD 宽度
    u16 height;			//LCD 高度
    u16 id;				//LCD ID
    u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。
    u8	wramcmd;		//开始写gram指令
    u8  setxcmd;		//设置x坐标指令
    u8  setycmd;		//设置y坐标指令
} _lcd_dev;

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
//LCD的画笔颜色和背景色
extern u16  POINT_COLOR;//默认红色
extern u16  BACK_COLOR; //背景颜色.默认为白色

//////////////////////////////////////////////////////////////////////////////////
//-----------------LCD端口定义----------------
#define	LCD_LED PDout(13) //LCD背光    		 PB0 

#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR		
#define Bank1_LCD_D    ((uint32_t)0x60020000)  //disp Data ADDR	  
#define LCD_REG   	  *(__IO uint16_t *) (Bank1_LCD_C)// ((uint32_t)0x60000000)
#define LCD_DAT    	  *(__IO uint16_t *) (Bank1_LCD_D)// ((uint32_t)0x60020000)
//////////////////////////////////////////////////////////////////////////////////

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE          	 0x001F
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 		     	 0XBC40 //棕色
#define BRRED 		    	 0XFC07 //棕红色
#define GRAY  		    	 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void LCD_Init(void);													   	//初始化
void LCD_DisplayOn(void);													//开显示
void LCD_DisplayOff(void);													//关显示
void LCD_Clear(u16 Color);	 												//清屏
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//设置光标
void LCD_DrawPoint(u16 x, u16 y);											//画点
void LCD_Fast_DrawPoint(u16 x, u16 y, u16 color);								//快速画点
u16  LCD_ReadPoint(u16 x, u16 y); 											//读点
void Draw_Circle(u16 x0, u16 y0, u8 r);										//画圆
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//画矩形
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);		   				//填充单色
void LCD_Color_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 *color);				//填充指定颜色
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode);						//显示一个字符
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size);  						//显示一个数字
void LCD_ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode);				//显示 数字
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8 *p);		//显示一个字符串,12/16字体

void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_Scan_Dir(u8 dir);							//设置屏扫描方向
void LCD_Display_Dir(u8 dir);						//设置屏幕显示方向

#endif





