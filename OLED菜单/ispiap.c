#include <STC12C5A60S2.h>
#include "ispiap.h"
#include <intrins.h>

void IapIdle()	//不使用IAP
{
	IAP_CONTR = 0;
	IAP_CMD = 0;
	IAP_TRIG = 0;
	IAP_ADDRH = 0X80;
	IAP_ADDRL = 0;
}


unsigned char IapRead(unsigned int addr)	//从IAP中读取
{
	unsigned char dat;
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_READ;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0X5A;
	IAP_TRIG = 0XA5;
	_nop_();
	dat = IAP_DATA;
	IapIdle();
	return dat;
}

void IapWrite(unsigned int addr,unsigned char dat)	//写入IAP
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_PROGRAM;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_DATA = dat;
	IAP_TRIG = 0X5A;
	IAP_TRIG = 0XA5;
	_nop_();

	IapIdle();
}

void IapEraseSector(unsigned int addr)	//擦除扇区
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_ERASE;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0X5A;
	IAP_TRIG = 0XA5;
	_nop_();

	IapIdle();
}