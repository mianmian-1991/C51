#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit Weixuan = P2^7;
sbit DA_CS = P3^2;
sbit DA_WR = P3^6;
sbit beep = P2^3;

void delay(uint);

uchar cnt;
bit up_down = 1;
uint period = 5000;

void main()
{
	Weixuan = 0;
	
	DA_CS = 0;
	P0 = 0;
	DA_WR = 0;

	while(1)
	{
		if(up_down==1)	// up
		{
			cnt+=5;
			P0 = cnt;
			if(cnt>=255)
			{
				up_down = 0;
				beep = 0;
				delay(50);
				beep = 1;
			}
			delay(period/2/(255/5));
		}
		else	// down
		{
			cnt-=5;
			P0 = cnt;
			if(cnt<=00)
			{
				up_down = 1;
				beep = 0;
				delay(50);
				beep = 1;
			}
			delay(period/2/(255/5));
		}
	}
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}

