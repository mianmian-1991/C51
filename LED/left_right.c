#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

uchar a = 0xaa;

void delayms(uint);

void main()
{
	while(1)
	{	
		P1 = a;
		a = a<<1;
		delayms(1000);
	}
}

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

