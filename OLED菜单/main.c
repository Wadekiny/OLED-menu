#include <STC12C5A60S2.h>
#include "oled.h"
#include "key.h"
#include "bmp.h"
#include "delay.h"
#include "ispiap.h"
#include "binary.h"
#include "init.h"
#define u8 unsigned char
#define u16 unsigned int

enum main_catalog{LEFT,RIGHT,MODE,PID,MESSAGE,DESIGNED,};
enum mode_catalog{AUTO,MANUAL,};
enum pid_catalog{KP,KI,KD,};

enum main_catalog main_first;
enum main_catalog main_pointer;
u8 main_pointer_y;

enum mode_catalog mode_pointer;
u8 mode_pointer_y;

enum pid_catalog pid_pointer;
u8 pid_pointer_y;

u8 mode;
u8 p,i,d;

void ChangeNum(u8 *number,u8 x, u8 y);			//改变参数
void OpenShow();								//开机动画
void ShowArrow(u8 catalog_pointer_y, u8 line);	//显示箭头
void MessageMenu();		//信息界面
void DesignedMenu();	//设计者界面
void PIDMenu();			//pid界面
void ModeMenu();		//模式界面
void MainMenu();		//主界面

void main()
{	
	Init();
	
	OpenShow();
	MainMenu();		
	while (1);
}

void OpenShow()
{
	u8 i,j;
	OLED_WR_Byte(0x2e,OLED_CMD);	
	Delay20us();
	Delay100us();
	Delay500us();
	Delay1ms();
	Delay10ms();
	DelayMs(1);
	Delay1s();
	for (i=0; i<60; i++)			//关门
	{
		OLED_Pane8_8(i,120-i,0,7,1);
		Delay10ms();
	}
	for (i=60; i>0; i--)			//开门
	{
		OLED_Pane8_8(i,120-i,0,7,0);
		Delay10ms();
	}
	OLED_DrawBMP(0,0,128,8,BMP1);
	Delay1s();
	Delay1s();
	OLED_DrawBMP(0,0,128,8,BMP2);
	Delay1s();
	Delay1s();
	OLED_DrawBMP(0,0,128,8,BMP3);
	Delay1s();
	Delay1s();
	OLED_DrawBMP(0,0,128,8,BMP4);  
	Delay1s();
	Delay1s();

	
	//网格
	for (i=0; i<16; i++)	
	{
		OLED_DrawCube(0,i,1,1);
		DelayMs(30);
	}
	Delay500ms();
	for (j=0; j<32; j++)
	{
		for (i=0; i<16; i++)
		{
			OLED_DrawCube(j,i,1,1);
		}
		DelayMs(30);
	}
	Delay500ms();

	//很菜的菜单 滚屏 反色
	OLED_Clear();
	OLED_ShowCHinese(0,0,1);
	OLED_ShowCHinese(20,0,2);
	OLED_ShowCHinese(40,0,3);
	OLED_ShowCHinese(60,0,4);
	OLED_ShowCHinese(80,0,5);
	OLED_ShowCHinese(0,3,6);
	OLED_ShowCHinese(20,3,7);
	OLED_ShowCHinese(40,3,8);
	OLED_ShowCHinese(60,3,9);
	OLED_ShowCHinese(80,3,10);
	OLED_ShowCHinese(100,3,11);

	OLED_rolling_vtcandlev(0,7,1);
	while (KeyScan() == NONE)
	{
		OLED_WR_Byte(0xa6,OLED_CMD);
		Delay100ms();
		OLED_WR_Byte(0xa7,OLED_CMD);
		Delay100ms();
	}
	OLED_WR_Byte(0x2e,OLED_CMD);
	OLED_WR_Byte(0xa6,OLED_CMD);
}

void MainMenu()
{
	u8 key_data;
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
	OLED_Clear();
	while (1)
	{
		ShowArrow(main_pointer_y,4);
		switch (main_first)
		{
			case LEFT:	OLED_ShowString(20,0,"LEFT    ");
						OLED_ShowString(20,2,"RIGHT   ");
						OLED_ShowString(20,4,"MODE    ");
						OLED_ShowString(20,6,"PID     ");
						break;
			case RIGHT:	OLED_ShowString(20,0,"RIGHT   ");
						OLED_ShowString(20,2,"MODE    ");
						OLED_ShowString(20,4,"PID     ");
						OLED_ShowString(20,6,"MESSAGE ");
						break;
			case MODE:	OLED_ShowString(20,0,"MODE    ");
						OLED_ShowString(20,2,"PID     ");
						OLED_ShowString(20,4,"MESSAGE ");
						OLED_ShowString(20,6,"DESIGNED");
						break;
			default:	OLED_ShowString(20,0,"MODE     ");
						OLED_ShowString(20,2,"PID      ");
						OLED_ShowString(20,4,"MESSAGE  ");
						OLED_ShowString(20,6,"DESIGNED ");
						break;
		}
		
		key_data = KeyScan();
		if (key_data == DOWN)
		{
			if (main_pointer_y != 6)	
			{
				main_pointer++;
				main_pointer_y += 2;
			}
			else if (main_pointer < DESIGNED)
			{
				main_pointer++;
				main_first++;
			}
		}
		else if (key_data == UP)
		{
			if (main_pointer_y != 0)
			{
				main_pointer--;
				main_pointer_y -= 2;
				
			}
			else if (main_pointer > LEFT)
			{
				main_first--;
				main_pointer--;
			}
		}
		else if (key_data == IN)
		{
			switch (main_pointer)
			{
				case LEFT:		break;
				case RIGHT:		break;
				case MODE:		ModeMenu();break;
				case PID:		PIDMenu();break;
				case MESSAGE:	MessageMenu();break;
				case DESIGNED:	DesignedMenu();break;
				default :		break;
			}
		}	
	}	
}

void ModeMenu()
{
	u8 key_data;
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
	OLED_Clear();
	while (1)
	{	
		ShowArrow(mode_pointer_y,2);
		OLED_ShowString(20,0,"AUTO    ");
		OLED_ShowString(20,2,"MANUAL  ");
		
		if (mode == AUTO)
		{
			OLED_ShowChar(100,0,'N');
			OLED_ShowChar(100,2,' ');
		}
		else if (mode == MANUAL)
		{
			OLED_ShowChar(100,0,' ');
			OLED_ShowChar(100,2,'N');
		}
		
		key_data = KeyScan();//¼ì²â¼üÅÌ
		if (key_data == DOWN)
		{
			mode_pointer_y = 2;
			mode_pointer = MANUAL;
		}
		else if (key_data == UP)
		{
			mode_pointer_y = 0;
			mode_pointer = AUTO;
		}
		else if (key_data == IN)
		{
			if (mode_pointer == AUTO) mode = AUTO;
			else if (mode_pointer == MANUAL) mode = MANUAL;
		}	
		else if (key_data == OUT)
		{
			OLED_Clear();
			return;
		}
	}
}

void PIDMenu()
{
	u8 key_data;
	OLED_Clear();
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
	OLED_DrawBMP(0,6,128,8,pidpid);
	OLED_rolling_vtcandlev(6,7,0);
	while (1)
	{
		p = IapRead(0);
		i = IapRead(1);
		d = IapRead(2);
		OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
		ShowArrow(pid_pointer_y,3);
		OLED_ShowString(20,0,"KP      ");
		OLED_ShowString(20,2,"KI      ");
		OLED_ShowString(20,4,"KD      ");
		
		OLED_ShowNum(80,0,p,3,16);
		OLED_ShowNum(80,2,i,3,16);
		OLED_ShowNum(80,4,d,3,16);
		OLED_WR_Byte(0x2f,OLED_CMD);	//开启滚动
		
		while ((key_data=KeyScan()) == NONE);
		if (key_data==DOWN && pid_pointer<KD)
		{
			pid_pointer++;
			pid_pointer_y += 2;
		}
		else if (key_data == UP && pid_pointer>KP)
		{
			pid_pointer--;
			pid_pointer_y -= 2;
		}
		else if (key_data == IN)
		{
			switch (pid_pointer)
			{
				case KP:ChangeNum(&p,80,0);break;
				case KI:ChangeNum(&i,80,2);break;
				case KD:ChangeNum(&d,80,4);break;
				default:break;
			}
			IapEraseSector(0);
			IapWrite(0,p);
			IapWrite(1,i);
			IapWrite(2,d);
		}	
		else if (key_data == OUT)
		{
			OLED_Clear();
			return;
		}
	}
}

void MessageMenu()
{
	u8 key_data;
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
	OLED_Clear();
	while (1)
	{
		OLED_ShowString(0,0,"Wang Tianyong");
		OLED_ShowString(0,2,"17061227");
		OLED_ShowString(0,4,"QQ:1059152613");
		OLED_ShowString(0,6,"Phone13777804491");
		key_data = KeyScan();
		if (key_data != NONE)
		{
			OLED_Clear();
			break;
		}
	}
}
void DesignedMenu()
{
	u8 page = 0;
	u8 key_data;
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
	OLED_Clear();
	while (1)
	{	
		OLED_ShowString(0,0-page, "Designed by Wang");
		OLED_ShowString(0,2-page, "----------------");
		OLED_ShowString(0,4-page, "-SPECIAL THANKS-");
		OLED_ShowString(0,6-page, "You Jingyun     ");
		OLED_ShowString(0,8-page, "Lin Kefan       ");
		OLED_ShowString(0,10-page,"Hu Yizhou       ");
		OLED_ShowString(0,12-page,"Wang Zhaohui    ");
		OLED_ShowString(0,14-page,"Lin Chenxi     T");
		OLED_ShowString(0,16-page,"Ma Zhongyang   T");
		key_data = KeyScan();
		if (key_data == UP)
		{
			if (page>0)
				page -= 2;
		}
		else if (key_data == DOWN)
		{
			if (page<10)
				page += 2;
		}
		else if (key_data != NONE)
		{
			OLED_Clear();
			return;
		}
	}
}

void ChangeNum(u8 *number,u8 x, u8 y)
{
	u8 key_change;
	u8 temp = 0;
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
	OLED_ShowChar(x-10,y,'*');
	OLED_WR_Byte(0x2f,OLED_CMD);	//开启滚动
	while (1)
	{
		OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
		OLED_ShowNum(x,y,temp,3,16);
		OLED_WR_Byte(0x2f,OLED_CMD);	//开启滚动
		
		while ((key_change=KeyScan()) == NONE);
		if (key_change < 10 && temp < 100)
		{
			if (temp*10 + key_change> 255) temp = 255;
			else temp = temp*10 + key_change;
		}
		else if (key_change == DELETE)
		{
			temp /= 10;
		}
		else if (key_change == OK)
		{
			*number = temp;
			OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
			OLED_ShowChar(x-10,y,' ');
			OLED_WR_Byte(0x2f,OLED_CMD);	//开启滚动
			break;
		}
		else if (key_change == OUT)
		{
			OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
			OLED_ShowChar(x-10,y,' ');
			OLED_WR_Byte(0x2f,OLED_CMD);	//开启滚动
			break;
		}
	}
}

void ShowArrow(u8 catalog_pointer_y, u8 line)
{
	u8 i,j;
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动
	for (i=0; i<10; i++)
	{
		for (j=0; j<line*2; j+=2)
		{
			if (j != catalog_pointer_y)
				OLED_ShowString(i,j," ");
		}
	}
	OLED_ShowCHinese(0,catalog_pointer_y,0);
}