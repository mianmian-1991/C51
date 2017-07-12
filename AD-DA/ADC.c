#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

// 段选 U1
uchar code DigitronTable[] =
{
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71
};

// 位选 U2
uchar code WeiTable[] =
{
    0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};

sbit Duanxuan = P2^6;
sbit Weixuan = P2^7;
sbit AD_WR = P3^6;
sbit AD_RD = P3^7;

void init();
void delay(uint);
void display(uchar);

uchar AD_val;

void main()
{
	uchar i;

	init();
	
	while(1)
	{
		AD_WR = 1;
		_nop_();
		AD_WR = 0;
		_nop_();
		AD_WR = 1;
		
		for(i=0;i<15;i++)
		{
			display(AD_val);
			delay(10);
		}
		
		P1 = 0xff;
		AD_RD = 1;
		_nop_();
		AD_RD = 0;
		_nop_();
		AD_val = P1;     // 8 bit, 0x00~0xff
		AD_RD = 1;
	}
}

void init()
{
	P0 = 0xff;
	Weixuan = 1;
	P0 = 0x7f;	// ADC CS 选通
	Weixuan = 0;
}

void display(uchar num)
{
	uint temp = num;
    uchar i,n;
    uchar wei[6];

    n = 0;
    while(temp!=0)     // 求位数
    {
         n++;
         temp/=10;
    }

    temp = num;
    i = n-1;
    while(temp!=0)     // 取各位，wei[0] 最高位
    {
         wei[i] = temp % 10;     // 取当前个位
         i--;
         temp/=10;     // 去掉最后一位
    }

	for(i=0;i<n;i++)
	{
		Duanxuan = 1;
		P0 = DigitronTable[wei[i]];
		Duanxuan = 0;
		P0 = 0xff;
		Weixuan = 1;
		P0 = WeiTable[i] & 0x7f;	// 特别注意这里不能影响到 ADC 的 CS
		Weixuan = 0;
		delay(3);
	}
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}
