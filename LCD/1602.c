#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char
#define COMMAND 1
#define DATA 0

uchar code row1[] = "HEY, I AM";
uchar code row2[] = "WATCHING";
uchar code row3[] = ":) :) :) :) :)";

sbit LCD_E = P3^4;
sbit LCD_RS = P3^5;
sbit Duanxuan = P2^6;
sbit Weixuan = P2^7;

void delay(uint);
void init();
void write_com(uchar);
void write_data(uchar);
void write(uchar,bit);

uint cnt;

/*
void main()
{
	init();
	
	write_com(0x80);	// 7.2.4 RAM ��ַ������һ����д��
	for(cnt=0;cnt<sizeof(row1)/sizeof(uchar);cnt++)
	{
		write_data(row1[cnt]);
		delay(5);
	}

	write_com(0x80+0x40);	// 7.2.4 RAM ��ַ�����ڶ�����д��
	for(cnt=0;cnt<sizeof(row2)/sizeof(uchar);cnt++)
	{
		write_data(row2[cnt]);
		delay(5);
	}
	
	while(1);
}
*/

/*
void init()
{
	Duanxuan = 0;	// �ر��������ʾ
	Weixuan = 0;

	LCD_E = 0;
	write_com(0x38);	// 7.2.6
	write_com(0x0c);	// 7.2.7
	write_com(0x06);	// 7.2.7
	write_com(0x01);	// 7.2.5
}
*/

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

	write(0x80+0x10,COMMAND);
	cnt = 0;
	while(row3[cnt]!='\0')
	{
		write(row3[cnt],DATA);
		delay(5);
		cnt++;
	}

	write(0x80+0x50,COMMAND);
	cnt = 0;
	while(row3[cnt]!='\0')
	{
		write(row3[cnt],DATA);
		delay(5);
		cnt++;
	}

	for(cnt=0;cnt<16;cnt++)
	{
		write(0x18,COMMAND);
		delay(300);
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

void write_com(uchar coms)
{
	LCD_RS = 0;		// ָ��ģʽ
	P0 = coms;		// ָ���͵� P0 ��
	delay(5);
	LCD_E = 1;		// ʹ�ܣ�ָ������ RAM
	delay(5);
	LCD_E = 0;
}

void write_data(uchar datas)
{
	LCD_RS = 1;		// ����
	P0 = datas;		// �����͵� P0 ��
	delay(5);
	LCD_E = 1;		// ʹ�ܣ��������� RAM
	delay(5);
	LCD_E = 0;
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}




