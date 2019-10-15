#ifndef _ISPIAP_H_
#define _ISPIAP_H_

#define CMD_IDLE 0
#define CMD_READ 1
#define CMD_PROGRAM 2
#define CMD_ERASE 3

#define IAP_ADDRESS 0X0000

#define ENABLE_IAP 0x83;	//11.0592
//#define ENABLE_IAP 0X82	//12.0000


void IapIdle();
unsigned char IapRead(unsigned int addr);
void IapWrite(unsigned int addr,unsigned char dat);
void IapEraseSector(unsigned int addr);

#endif