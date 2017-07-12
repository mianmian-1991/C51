#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit Weixuan = P2^7;
sbit Duanxuan = P2^6;

sbit s2 = P3^4;
sbit s3 = P3^5;
sbit s4 = P3^6;
sbit s5 = P3^7;

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

int num = 0;
uint cnt = 0;
uint N_50ms = 65536 - 45872;

void init();
void keyscan();
void display(uint);
void delayms(uint);

void main()
{
	init();
	while(1)
	{
		keyscan();
		display(num);
	}
}

void init()
{
	TMOD = 0x01;
	TH0 = N_50ms / 256;
	TL0 = N_50ms % 256;	
	EA = 1;
	ET0 = 1;
}

void keyscan()
{
	if(s2==0)
	{
		delayms(10);
		if(s2==0)
		{
			num++;
			if(num>=60)
				num = 0;
			while(s2==0)
				display(num);
		}
	}

	if(s3==0)
	{
		delayms(10);
		if(s3==0)
		{
			num--;
			if(num<0)
				num = 59;
			while(s3==0)
				display(num);
		}
	}

	if(s4==0)
	{
		delayms(10);
		if(s4==0)
		{
			num = 0;
			while(s4==0)
				display(num);
		}
	}

	if(s5==0)
	{
		delayms(10);
		if(s5==0)
		{
			TR0 = !TR0;
			cnt = 0;
			while(s5==0)
				display(num);
		}
	}
}

void display(uint number)
{
	uint shi, ge;
	shi = number / 10;
	ge = number % 10;

	Duanxuan = 1;
	P0 = DigitronTable[shi];
	Duanxuan = 0;
	P0 = 0xff;
	Weixuan = 1;
	P0 = WeiTable[0];
	Weixuan = 0;
	delayms(5);

	Duanxuan = 1;
	P0 = DigitronTable[ge];
	Duanxuan = 0;
	P0 = 0xff;
	Weixuan = 1;
	P0 = WeiTable[1];
	Weixuan = 0;
	delayms(5);	
}

void delayms(uint xms)
{
     unsigned int i, j;
     for (i=xms; i>0; i--)
          for (j=110; j>0; j--);
}

void T0_1s() interrupt 1
{
	TH0 = N_50ms / 256;
	TL0 = N_50ms % 256;
	cnt++;
	if(cnt>=1000/50)
	{
		cnt = 0;
		num++;
		if(num>=60)
			num = 0;
	}
}


