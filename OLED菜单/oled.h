#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  
#include <STC12C5A60S2.h>

#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	
#define OLED_DATA 1	
#define OLED_MODE 0

sbit OLED_CS=P1^4;
sbit OLED_DC =P1^3;
sbit OLED_RST =P1^2;
sbit OLED_SDIN=P1^1;
sbit OLED_SCL=P1^0;

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1;




#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
			   

void delay_ms(unsigned int ms);


 		     
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);

void OLED_DrawPoint(u8 x,u8 y,u8 t);

void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);

void OLED_ShowChar(u8 x,u8 y,u8 chr);

void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);

void OLED_ShowString(u8 x,u8 y, u8 *p);	 

void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_rolling_vtcandlev(u8 start, u8 end, u8 y_speed);
void OLED_DrawCube(u8 x,u8 y,u8 color1,u8 color2);
void OLED_Pane8_8(u8 x0,u8 x1,u8 y0,u8 y1,u8 color);
#endif  
	 



