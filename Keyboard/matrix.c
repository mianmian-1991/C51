#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit Weixuan = P2^7;
sbit Duanxuan = P2^6;
sbit s2 = P3^4;

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

uchar code Row[] =
{
    0xfe, 0xfd, 0xfb, 0xf7
};

uchar code Column[] =
{
    0xe0, 0xd0, 0xb0, 0x70
};

uint key = 0;
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
	}
}

void init()
{
	Duanxuan = 1;
	P0 = 0x00;
	Duanxuan = 0;
	P0 = 0xff;
	Weixuan = 1;
	P0 = 0xc0;	// 1100 0000
	Weixuan = 0;
}

void keyscan()
{
	uint i, temp, key;
	for(i=0;i<=3;i++)
	{
		P3 = Row[i];
		temp = P3 & 0xf0;	// 提取列信息
		if(temp!=0xf0)	// 有列低电平，按键按下
		{
			delayms(10);
			P3 = Row[i];
			temp = P3 & 0xf0;
			if(temp!=0xf0)
			{
				switch(temp)
				{
					case 0xe0:
						key = i*4 + 0;
						break;
					case 0xd0:
						key = i*4 + 1;
						break;
					case 0xb0:
						key = i*4 + 2;
						break;
					case 0x70:
						key = i*4 + 3;
						break;
				}
				while(temp!=0xf0)
				{
					temp = P3 & 0xf0;
					display(key);
				}
			}
		}
	}
//	if(s2==0)
//	{
//		delayms(10);
//		if(s2==0)
//			init();
//		while(s2==0);
//	}
}

void display(uint number)
{
	Duanxuan = 1;
	P0 = DigitronTable[number];
	Duanxuan = 0;
}

void delayms(uint xms)
{
     unsigned int i, j;
     for (i=xms; i>0; i--)
          for (j=110; j>0; j--);
}


