#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit DC = P1^7;
sbit Duanxuan = P2^6;
sbit Weixuan = P2^7;
sbit speed_up = P3^4;
sbit speed_down = P3^5;

// ถฮัก U1
uchar code DigitronTable[] =
{
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71
};

// ฮปัก U2
uchar code WeiTable[] =
{
    0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};

void init();
void scan_key();
void PWM_drive();
void display(uchar);
void delay(uint);

uchar max_num = 4;
char num = 0;
uchar high_num = 0, low_num;

void main()
{
	init();
	while(1)
	{
		scan_key();
		PWM_drive();
	}
}

void init()
{
	DC = 0;

	low_num = max_num;

	Duanxuan = 1;
	P0 = DigitronTable[0];
	Duanxuan = 0;

	P0 = 0xff;

	Weixuan = 1;
	P0 = WeiTable[0];
	Weixuan = 0;
}

void scan_key()
{
	if(speed_up==0)
	{
		delay(10);
		if(speed_up==0)
		{
			num++;
			if(num>4)
				num = 4;
			while(speed_up==0);
		}
	}
	if(speed_down==0)
	{
		delay(10);
		if(speed_down==0)
		{
			num--;
			if(num<0)
				num = 0;
			while(speed_down==0);
		}
	}
}

void PWM_drive()
{
	uchar i;

	high_num = num;
	low_num = max_num - num;
	
	for(i=0;i<high_num;i++)
	{
		DC = 1;
		display(num);
	}

	for(i=0;i<low_num;i++)
	{
		DC = 0;
		display(num);
	}
}

void display(uchar num)
{
	Duanxuan = 1;
	P0 = DigitronTable[num];
	Duanxuan = 0;

	delay(30);
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);	
}
