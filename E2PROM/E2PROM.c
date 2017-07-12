#include<reg52.h>

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
sbit SDA = P2^0;
sbit SCL = P2^1;

void delay();
void delayms(uint);
void init_T0();
void display(uchar);
void write(uchar, uchar);
uchar read(uchar);
void write_byte(uchar);
uchar read_byte();
void init();
void start();
void stop();
void respons();

uchar sec, cnt;
uchar dis[2];
bit flag;

void main()
{
	init();
	sec = read(0x01);
	if(sec>=100)
		sec = 0;
	init_T0();
	while(1)
	{
		display(sec);
		/*
		if(flag==1)
		{
			flag = 0;
			write(0x02,sec);
		}
		*/
	}
}

void init_T0()
{
	TMOD = 0x01;
	TH0 = (65536-45872)/256;
	TL0 = (65536-45872)%256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

void interruptT0() interrupt 1
{
	TH0 = (65536-45872)/256;
	TL0 = (65536-45872)%256;
	cnt++;
	if(cnt>=10)
	{
		cnt = 0;
		sec++;
		if(sec>=100)
			sec = 0;
		write(0x01,sec);
		//flag = 1;
	}
}

void display(uchar num)
{
	uchar i;
	
	dis[0] = num / 10;
	dis[1] = num % 10;

	for(i=0;i<2;i++)
	{
		Duanxuan = 1;
		P0 = DigitronTable[dis[i]];
		Duanxuan = 0;
		P0 = 0xff;
		Weixuan = 1;
		P0 = WeiTable[i];
		Weixuan = 0;
		delayms(3);
	}
}

void init()		// 双双拉高，准备启动
{
	SDA = 1;	// 注意先拉高 SDA，否则可能检测到 SDA 上升沿变 stop 信号
	delay();
	SCL = 1;
	delay();
}

void write(uchar address, uchar datas)
{
	start();
	write_byte(0xa0);	// 写-控制字，器件 1010，A2A1A0 = 000，RW = 0
	respons();
	write_byte(address);
	respons();
	write_byte(datas);
	respons();
	stop();
}

uchar read(uchar address)
{
	uchar datas;
	
	start();
	write_byte(0xa0);	// 写-控制字，器件 1010，A2A1A0 = 000，RW = 0
	respons();
	write_byte(address);
	respons();
	start();
	write_byte(0xa1);	// 读-控制字，器件 1010，A2A1A0 = 000，RW = 1
	respons();
	datas = read_byte();
	stop();
	return datas;
}

void write_byte(uchar byte2send)    // SCL 高电平期间 SDA 稳定不变
{
	uchar i;

	for(i=0;i<8;i++)	// 一个字节分 8 位发送
	{
		byte2send<<=1;		// 一位位将最高位送至 CY
		SCL = 0;	// 先拉低时钟，数据才能变化
		delay();
		SDA = CY;	
		delay();
		SCL = 1;	// SCL 高电平送出数据
		delay();
	}

	SCL = 0;	// SCL 恢复低电平
	delay();
	SDA = 1;	// ？
	delay();
}

uchar read_byte()    // SCL 高电平期间 SDA 稳定不变
{
	uchar i, recieve;

	SCL = 0;
	delay();
	SDA = 1;	// ？
	delay();
	
	for(i=0;i<8;i++)
	{
		SCL = 1;    // SCL 高电平期间 SDA 稳定不变
		delay();
		recieve = (recieve<<1) | SDA;	// 最低位接收 SDA，然后一步步左移
		SCL = 0;    // SCL 恢复低电平
		delay();
	}

	return recieve;
}

void start()	// SDA 下降沿（SCL 高电平期间）
{
	SDA = 1;
	delay();
	SCL = 1;	// 初始准备
	delay();
	SDA = 0;	// SDA 下降沿
	delay();
}

void stop()		// SDA 上升沿（SCL 高电平期间）
{
	SDA = 0;
	delay();
	SCL = 1;	// 初始准备
	delay();
	SDA = 1;	// SDA 上升沿
	delay();
}

void respons()		// 检测 SDA 被从机拉低（SCL 高电平期间），每次读写字节以后都要等应答以确认接收
{
	uchar i;

	SCL = 1;	// 初始准备
	delay();
	while((SDA==1)&&(i++<250));		// 防止没收到应答，设定最长时限
	SCL = 0;	// SCL 恢复低电平
	delay();
}

void delay()
{ ; ; }

void delayms(uint xms)
{
	uint i,j;
	for(i=0;i<xms;i++)
		for(j=0;j<110;j++);
}


