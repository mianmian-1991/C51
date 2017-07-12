#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char
#define COMMAND 1
#define DATA 0

uchar code row1[] = "HEY, I AM";
uchar code row2[] = "WATCHING";
uchar code row3[] = ":) :) :) :) :)  ";

sbit LCD_E = P3^4;
sbit LCD_RS = P3^5;
sbit Duanxuan = P2^6;
sbit Weixuan = P2^7;

void delay(uint);
void init();
void write_com(uchar);
void write_data(uchar);
void write(uchar,bit);

uint cnt, shift;

void main()
{
	init();

	//delay(2000);

	write(0x80,COMMAND);	// 7.2.4 RAM ��ַ������һ����д��	
	cnt = 0;
	while(row1[cnt]!='\0')
	{
		write(row1[cnt],DATA);
		delay(300);
		//write(0x10,COMMAND);
		cnt++;
	}

	write(0x80+0x40,COMMAND);	// 7.2.4 RAM ��ַ�����ڶ�����д��
	for(cnt=0;cnt<(sizeof(row2)/sizeof(uchar)-1);cnt++)		// �ַ��������и� '\0'
	{
		write(row2[cnt],DATA);
		delay(300);
	}
	
	for(shift=1;shift<17;shift++)
	{
		write(0x80+0x10-shift,COMMAND);
		cnt = 0;
		while(cnt<shift)
		{
			write(row3[cnt],DATA);
			delay(1);
			cnt++;
		}

		write(0x80+0x50-shift,COMMAND);
		cnt = 0;
		while(cnt<shift)
		{
			write(row3[cnt],DATA);
			delay(1);
			cnt++;
		}

		delay(200);
	}

	while(1);
}

void init()
{
	Duanxuan = 0;
	Weixuan = 0;
	LCD_E = 0;
	write(0x38,COMMAND);
	write(0x0f,COMMAND);
	write(0x06,COMMAND);
	write(0x01,COMMAND);
}

void write(uchar com_data, bit comORdata)
{
	if(comORdata == COMMAND)
		LCD_RS = 0;		// ָ��ģʽ
	else
		LCD_RS = 1;		// ����ģʽ
	P0 = com_data;		// �͵� P0 ��
	delay(5);
	LCD_E = 1;		// ʹ�ܣ����� RAM
	delay(5);
	LCD_E = 0;
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}




