#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar character;
uchar code table[] = "I get ";

void init();

void main()
{
	init();
	while(1);
}

void init()
{
	TMOD = 0x20;
	TH1 = 0xfd;		// ²¨ÌØÂÊ 9600£¬SCON=0
	TL1 = 0xfd;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
}

void recieve() interrupt 4
{
	uint i;
	RI = 0;
	character = SBUF;
	for(i=0;i<sizeof(table)/sizeof(uchar);i++)
	{
		SBUF = table[i];
		while(TI==0);
		TI = 0;
	}
	SBUF = character;
	while(TI==0);
	TI = 0;
}
