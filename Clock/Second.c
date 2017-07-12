#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit led1 = P1^0;
sbit Weixuan = P2^7;
sbit Duanxuan = P2^6;

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
uint second, shi, ge;

void delayms(uint);
void display(uint, uint);

void main()
{
	TMOD = 0x11;	// T1 和 T0 均工作在方式 1
	TH1 = N_50ms / 256;		// T1 用作 LED，200 ms
	TL1 = N_50ms % 256;		
	TH0 = N_50ms / 256;		// T0 用作数码管，1s
	TL0 = N_50ms % 256;	
	EA = 1;
	ET1 = 1;
	ET0 = 1;
	TR1 = 1;
	TR0 = 1;
	while(1)
	{
		display(shi,ge);
	}
}


void LED_T1() interrupt 3
{
	TH1 = N_50ms / 256;
	TL1 = N_50ms % 256;
	num_LED++;
	if (num_LED >= 200/50)
	{
		num_LED = 0;
		led1 = ~led1;
	}	
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
		if (second >= 60)
			second = 0;
		shi = second / 10;
		ge = second % 10;
	}
}

void display(uint shi, uint ge)
{
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




