#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	   
//////////////////////////////////////////////////////////////////////////////////	 
				 
//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;
		   
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_LCD_WriteReg(u16 regval)
{ 
	*(__IO uint16_t *) (Bank1_LCD_C)= regval;
}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(u16 data)
{										    	   
	*(__IO uint16_t *) (Bank1_LCD_D)= data; 	
}
//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{										    	   
	return LCD_DAT;		 
}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= LCD_Reg;	
	*(__IO uint16_t *) (Bank1_LCD_D)= LCD_RegValue;
}	   
//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(u8 LCD_Reg)
{										   
	LCD_LCD_WriteReg(LCD_Reg);		//д��Ҫ���ļĴ������
	delay_us(5);		  
	return LCD_RD_DATA();		//���ض�����ֵ
}   
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
 	LCD_LCD_WriteReg(0x0022);	  
}	 
//LCDдGRAM
//RGB_Code:��ɫֵ
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD_DAT = RGB_Code;//дʮ��λGRAM
}
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay_ms(u8 i)
{
	while(i--);
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0;
	LCD_SetCursor(x,y);	
	LCD_LCD_WriteReg(0x22);
	if(LCD_DAT)  r=0;	//dummy Read	   
	delay_us(2);	  
 	r=LCD_DAT;  		  		//ʵ��������ɫ  
  return LCD_BGR2RGB(r);	//����IC
}			 
//LCD������ʾ
void LCD_DisplayOn(void)
{					   
	//LCD_WriteReg(R7,0x0173); 			//������ʾ
}	 
//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   
 //LCD_WriteReg(R7,0x0);//�ر���ʾ 
}   
//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
	LCD_WriteReg(0x004E, Xpos);
	LCD_WriteReg(0X004F, Ypos);
} 		 
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
//dir:0~7,����8������(���嶨���lcd.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341��IC�Ѿ�ʵ�ʲ���	   	   
void LCD_Scan_Dir(u8 dir)
{
}   
//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_DAT=POINT_COLOR; 
}
//���ٻ���
//x,y:����
//color:��ɫ
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{	
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_DAT=color; 
   
}	 
//����LCD��ʾ����6804��֧�ֺ�����ʾ��
//dir:0,������1,����
void LCD_Display_Dir(u8 dir)
{
	lcddev.dir=0;//����
	lcddev.width =240;
	lcddev.height=320;
}
/*******************************************
 * ��������LCD_GPIO_Config
 * ����  ������FSMC����LCD��I/O
*********************************************/  
void LCD_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* ʹ��FSMC��Ӧ��Ӧ�ܽ�ʱ�� D E */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* ����LCD������ƹܽ�*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		
  GPIO_Init(GPIOD, &GPIO_InitStructure);


  /* ����FSMC���Ӧ��������,FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10*/	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |  GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_8 | GPIO_Pin_9 | 
                                GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOD, &GPIO_InitStructure);    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
 /* ����FSMC���Ӧ�Ŀ�����
 * PD4-FSMC_NOE  :LCD-RD
 * PD5-FSMC_NWE  :LCD-WR
 * PD7-FSMC_NE1  :LCD-CS
 * PD11-FSMC_A16 :LCD-DC
 */
  /* NE1 configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /* RS */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
  GPIO_Init(GPIOD, &GPIO_InitStructure); 
  /* TFT control gpio init */	 
  GPIO_SetBits(GPIOD, GPIO_Pin_4);		 // RD = 1  
  GPIO_SetBits(GPIOD, GPIO_Pin_5);		 // WR = 1 
  GPIO_SetBits(GPIOD, GPIO_Pin_7);		 //	CS = 1
	GPIO_SetBits(GPIOD, GPIO_Pin_11);		 //	RS = 1 
}

/*******************************************
 * ��������LCD_FSMC_Config
 * ����  ��LCD  FSMC ģʽ����
*********************************************/ 
void LCD_FSMC_Config(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p; 
  /* ʹ��FSMCʱ��*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  p.FSMC_AddressSetupTime = 0x02;
  p.FSMC_AddressHoldTime = 0x00;
  p.FSMC_DataSetupTime = 0x05;
  p.FSMC_BusTurnAroundDuration = 0x00;
  p.FSMC_CLKDivision = 0x00;
  p.FSMC_DataLatency = 0x00;
  p.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;	  
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  /* Enable FSMC Bank1_SRAM Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}
	 
//��ʼ��lcd
void LCD_Init(void)
{ 										  
  LCD_GPIO_Config();
	LCD_FSMC_Config();										  			 
 	delay_ms(50); // delay_ms 50 ms 
 	LCD_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay_ms 50 ms 
  lcddev.id = LCD_ReadReg(0x0000);   
 	printf("LCD ID:%x\r\n",lcddev.id); //��ӡLCD ID  0x8989  
	//************* Start Initial Sequence **********//
	LCD_WriteReg(0x00, 0x0001); // Start internal OSC.
	LCD_WriteReg(0x01, 0x3B3F); // Driver output control, RL=0;REV=1;GD=1;BGR=0;SM=0;TB=1
	LCD_WriteReg(0x02, 0x0600); // set 1 line inversion
	//************* Power control setup ************/
	LCD_WriteReg(0x0C, 0x0007); // Adjust VCIX2 output voltage
	LCD_WriteReg(0x0D, 0x0006); // Set amplitude magnification of VLCD63
	LCD_WriteReg(0x0E, 0x3200); // Set alternating amplitude of VCOM
	LCD_WriteReg(0x1E, 0x00BB); // Set VcomH voltage
	LCD_WriteReg(0x03, 0x6A64); // Step-up factor/cycle setting
	//************ RAM position control **********/
	LCD_WriteReg(0x0F, 0x0000); // Gate scan position start at G0.
	LCD_WriteReg(0x44, 0xEF00); // Horizontal RAM address position
	LCD_WriteReg(0x45, 0x0000); // Vertical RAM address start position
	LCD_WriteReg(0x46, 0x013F); // Vertical RAM address end position
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WriteReg(0x30, 0x0000);
	LCD_WriteReg(0x31, 0x0706);
	LCD_WriteReg(0x32, 0x0206);
	LCD_WriteReg(0x33, 0x0300);
	LCD_WriteReg(0x34, 0x0002);
	LCD_WriteReg(0x35, 0x0000);
	LCD_WriteReg(0x36, 0x0707);
	LCD_WriteReg(0x37, 0x0200);
	LCD_WriteReg(0x3A, 0x0908);
	LCD_WriteReg(0x3B, 0x0F0D);
	//************* Special command **************/
	LCD_WriteReg(0x28, 0x0006); // Enable test command
	LCD_WriteReg(0x2F, 0x12EB); // RAM speed tuning
	LCD_WriteReg(0x26, 0x7000); // Internal Bandgap strength
	LCD_WriteReg(0x20, 0xB0E3); // Internal Vcom strength
	LCD_WriteReg(0x27, 0x0044); // Internal Vcomh/VcomL timing
	LCD_WriteReg(0x2E, 0x7E45); // VCOM charge sharing time  
	//************* Turn On display ******************/
	LCD_WriteReg(0x10, 0x0000); // Sleep mode off.
	delay_ms(15); // Wait 30mS
	LCD_WriteReg(0x11, 0x6878); // Entry mode setup. 262K type B, take care on the data bus with 16it only
	LCD_WriteReg(0x07, 0x0033); // Display ON	*/

  LCD_WriteRAM_Prepare();     //��ʼд��GRAM

	LCD_Display_Dir(1);		 	//Ĭ��Ϊ����
	LCD_LED=1;//��������
	LCD_Clear(WHITE);
}  
//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD_DAT=color;	   
	}
}
// ��������:���ô��ں���
void LCD_SetDisplayWindow(u16 x,u16 y,u16 x_end,u16 y_end)
{
 	LCD_SetCursor(x,y);			//���ù��λ��
	LCD_WriteReg(0x44,x|((x_end)<<8));
	LCD_WriteReg(0x45,y);
	LCD_WriteReg(0x46,y_end);
}
  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 height,width;
	width=ex-sx+1; 		//�õ����Ŀ��
	height=ey-sy+1;		//�߶�
		LCD_SetDisplayWindow(sx,sy,ex,ey);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++) 
			{
			LCD_DAT=color;//д������ 	 
			}
		}	  
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//�õ����Ŀ��
	height=ey-sy+1;		//�߶�
// 	for(i=0;i<height;i++)
//	{
// 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
//		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
//		for(j=0;j<width;j++) LCD_DAT=color[i*height+j];//д������ 
//	}	 
	LCD_SetDisplayWindow(sx,sy,ex,ey);
	LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
 	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++) 
		{
		LCD_DAT=color[i*height+j];//д������ 	 
		}
	}	  
 
}  
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
  u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }    
	}else//���ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(x>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}






























