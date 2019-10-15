#include "intrins.h"
#include "delay.h"	
//包含调用时间
//	#if FOCS == 11059200UL

void Delay20us()
{
    unsigned char a;
    for(a=52;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void Delay100us()
{
    unsigned char a,b;
    for(b=78;b>0;b--)
        for(a=2;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void Delay500us()
{
    unsigned char a,b;
    for(b=14;b>0;b--)
        for(a=97;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void Delay1ms()
{
    unsigned char a,b;
	for(b=21;b>0;b--)
	    for(a=130;a>0;a--);
	_nop_();  //if Keil,require use intrins.h
}
void Delay10ms()
{
    unsigned char a,b;
    for(b=194;b>0;b--)
        for(a=141;a>0;a--);
}

void Delay100ms()
{
    unsigned char a,b,c;
    for(c=157;c>0;c--)
        for(b=207;b>0;b--)
            for(a=7;a>0;a--);
}
void Delay500ms()
{
    unsigned char a,b,c;
    for(c=246;c>0;c--)
        for(b=212;b>0;b--)
            for(a=25;a>0;a--);
}

void Delay1s()
{
    unsigned char a,b,c;
    for(c=217;c>0;c--)
        for(b=171;b>0;b--)
            for(a=73;a>0;a--);
}

void DelayMs(unsigned int n)
{
	unsigned char i, j;
	for(n;n>0;n--)
	{

		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} 
		while (--i);
	}
}
