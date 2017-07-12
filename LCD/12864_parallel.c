#include<reg52.h>
#include<intrins.h>
#include<stdlib.h>
#include<string.h>

#define uchar unsigned char
#define uint unsigned int

#define LCD_data P0

#define COMMAND 1
#define DATA 0

sbit LCD_E = P3^4;
sbit LCD_RS = P3^5;
sbit LCD_RW = P3^6;
sbit LCD_PSB = P3^7;
sbit Weixuan = P2^6;
sbit Duanxuan = P2^7;

uchar row[4][17] = 
{
	"若这一束吊灯",
	"倾泻下来",
	"或者我",
	"已不会存在"
};

uchar emoji[] = {0x20,' ',0x02,0};

void delay(uint);
void init();
void write(uchar, bit);
void position(uchar, uchar);

void main()
{	
	uint i,j;
	init();	
	strcat(row[3],emoji);
	for(i=0;i<4;i++)
	{
		position(i,0);
		j = 0;
		while(row[i][j]!='\0')
		{
			write(row[i][j], DATA);
			delay(50);
			j++;
		}
	}
	delay(1000);
	// write(0x18, COMMAND);
	while(1);
}

void init()
{
	Weixuan = 0;
	Duanxuan = 0;
	LCD_PSB = 1;
	write(0x30, COMMAND);
	delay(5);	
	write(0x0f, COMMAND);
	delay(5);	
	write(0x01, COMMAND);
	delay(5);	
}

void write(uchar com_data, bit flag)
{
	if(flag==COMMAND)
		LCD_RS = 0;
	else
		LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 0;
	P0 = com_data;
	delay(5);
	LCD_E = 1;
	delay(5);
	LCD_E = 0;
}

void position(uchar x, uchar y)		// x 行，y 列
{
	uchar pos;
	switch(x)
	{
		case 0:
			pos = 0x80;
			break;
		case 1:
			pos = 0x90;
			break;
		case 2:
			pos = 0x88;
			break;
		case 3:
			pos = 0x98;
			break;
	}
	pos += y;
	write(pos, COMMAND);
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}


