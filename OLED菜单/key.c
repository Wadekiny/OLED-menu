#include <STC12C5A60S2.h>
#include "key.h"
/*

1  2  3  ↑
4  5  6  In
7  8  9  ↓
*  0  √  Out

*/
sbit led = P1^7;
void KeyDelay10ms(void)   //误差 -0.000000000002us
{
    unsigned char a,b;
    for(b=249;b>0;b--)
        for(a=17;a>0;a--);
}

unsigned char KeyScan()
{
	unsigned char temp;
	unsigned char dat = NONE;
	
	P3 = 0xfe;
	temp = P3;
	temp = temp & 0xf0;
	if (temp != 0xf0)
	{
		KeyDelay10ms();
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
				case 0xee: dat = 1;   break;
				case 0xde: dat = 2;   break;
				case 0xbe: dat = 3;   break;
				case 0x7e: dat = UP;  break;
				default:   dat = NONE;break;
			}
		}
		while (temp != 0xf0)
		{
			temp = P3;
			temp = temp & 0xf0;
		}
	}

	P3 = 0xfd;
	temp = P3;
	temp = temp & 0xf0;
	if (temp != 0xf0)
	{
		KeyDelay10ms();
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
				case 0xed: dat = 4; break;
				case 0xdd: dat = 5; break;
				case 0xbd: dat = 6; break;
				case 0x7d: dat = IN;break;
				default :  dat = NONE;break;
			}
		}
		while (temp != 0xf0)
		{
			temp = P3;
			temp = temp & 0xf0;
		}
	}
	
	P3 = 0xfb;
	temp = P3;
	temp = temp & 0xf0;
	if (temp != 0xf0)
	{
		KeyDelay10ms();
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
				case 0xeb: dat = 7; break;
				case 0xdb: dat = 8; break;
				case 0xbb: dat = 9; break;
				case 0x7b: dat = DOWN; break;
				default:   dat = NONE; break;
			}
		}
		while (temp != 0xf0)
		{
			temp = P3;
			temp = temp & 0xf0;
		}
	}
	
	P3 = 0xf7;
	temp = P3;
	temp = temp & 0xf0;
	if (temp != 0xf0)
	{
		KeyDelay10ms();
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
				case 0xe7: dat = DELETE; break;
				case 0xd7: dat = 0; break;
				case 0xb7: dat = OK; break;
				case 0x77: dat = OUT; break;
			}
		}
		while (temp != 0xf0)
		{
			temp = P3;
			temp = temp & 0xf0;
		}
	}
	return dat;
}