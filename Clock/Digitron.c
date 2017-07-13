#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

#include<delay.h>
#include<E2PROM.h>

#define HOUR 0
#define MINUTE 2
#define SECOND 4

sbit Weixuan = P2^7;
sbit Duanxuan = P2^6;

sbit keyCol = P3^7;
sbit keyS1 = P3^0;
sbit keyS2 = P3^1;
sbit keyS3 = P3^2;

sbit buzzer = P2^3;

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

uint N_50ms = 65536-45872;
uint num_LED = 0;
uint num_Digitron = 0;
int hour = 23, minute = 58, second = 50;
uchar menu = 0; 

void display(uchar, uint);
void init();
void beep();

void main()
{
	init();
	hour = read(0x01);
	minute = read(0x02);
	second = read(0x03);
	while(1) 
	{
		scankey();
		switch(menu)
		{
			case 1:
				display(SECOND, second);
				break;
			case 2:
				display(MINUTE, minute);
				break;
			case 3:
				display(HOUR, hour);
				break;
			default:
				display(HOUR, hour);
				display(MINUTE, minute);
				display(SECOND, second);
				break;
		}
	}
}

void init()
{
	TMOD = 0x01;	// T0 工作在方式 1
	TH0 = N_50ms / 256;		// 50ms
	TL0 = N_50ms % 256;	
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	keyCol = 0;

	buzzer = 1;
}

void beep()
{
	buzzer = 0;
	delayms(100);
	buzzer = 1;
}

void Digitron_T0() interrupt 1
{
	TH0 = N_50ms / 256;
	TL0 = N_50ms % 256;
	num_Digitron++;
	if (num_Digitron >= 1000/50)
	{
		num_Digitron = 0;
		second++;
		write(0x03,second);
		if (second >= 60)
		{
			second = 0;
			minute++;
			write(0x02,minute);
			if (minute >= 60)
			{
				minute = 0;
				hour++;
				write(0x01,hour);
				if (hour >= 24)
					hour = 0;
			}
		}
	}
}

void keyscan()
{
	if(keyS1==0)
	{
		delayms(10);
		if(keyS1==0)
		{
			menu ++;
			while(keyS1==0);
			beep();
			switch(menu)
			{
				case 4:
					menu = 0;
					TR0 = 1;
					break;
				default:
					TR0 = 0;
					break;	
			}
		}
	}
	
	if(menu!=0)
	{
		if(keyS2==0)
		{
			delayms(10);
			if(keyS2==0)
			{
				switch(menu)				
				{
					case 1:
						second++;
						if(second>=60)
							second = 0;
						break;
					case 2:
						minute++;
						if(minute>=60)
							minute = 0;
						break;
					case 3:
						hour++;
						if(hour>=24)
							hour = 0;
						break;	
				}
			}
		}

		if(keyS3==0)
		{
			delayms(10);
			if(keyS3==0)
			{
				switch(menu)				
				{
					case 1:
						second--;
						if(second<0)
							second = 59;
						break;
					case 2:
						minute--;
						if(minute<0)
							minute = 59;
						break;
					case 3:
						hour--;
						if(hour<0)
							hour = 23;
						break;	
				}
			}
		}

	}
}

void display(uchar start, uint num)
{
    Duanxuan = 1;
    P0 = DigitronTable[num/10];     // 段码
    Duanxuan = 0;
    P0 = 0xff;     // 消影
    Weixuan = 1;
    P0 = WeiTable[start];     // 位码
    Weixuan = 0;
    delayms(3);

	Duanxuan = 1;
    P0 = DigitronTable[num%10];     // 段码
    Duanxuan = 0;
    P0 = 0xff;     // 消影
    Weixuan = 1;
    P0 = WeiTable[start+1];     // 位码
    Weixuan = 0;
    delayms(3);
}





