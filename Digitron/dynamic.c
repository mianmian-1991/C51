#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit WeiXuan = P2^7;
sbit DuanXuan = P2^6;

uchar code DigitronTable[] = 
{
	0x3f, 0x06, 0x5b, 0x4f, 
	0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c,
	0x39, 0x5e, 0x79, 0x71
};

uchar code WeiTable[] =
{
	0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};

void delayms(uint);

void main()
{
	uint num = 0;

	while(1)
	{
		for (num=0;num<6;num++)
		{
			DuanXuan = 1;
			P0 = DigitronTable[num*2];
			DuanXuan = 0;

			P0 = 0xff;   // ÏûÓ°

			WeiXuan = 1;
			P0 = WeiTable[num];
			WeiXuan = 0;

			delayms(3);
		}
	}
}

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
