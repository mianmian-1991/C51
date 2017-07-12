#include<reg52.h>
#include<intrins.h>
#include<image.h>

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

void delay(uint);
void init();
void write(uchar, bit);
void draw_GDRAM(uchar *);
void clear_GDRAM();

uchar a;

void main()
{	
	init();	
	/*
	write(0x34, COMMAND); 
	write(0x36, COMMAND); 
	delay(2000);
	write(0x01, COMMAND); 
*/
	clear_GDRAM();
	
	draw_GDRAM(begger);
	
	while(1);
}

void init()
{
	Weixuan = 0;
	Duanxuan = 0;
	LCD_PSB = 1;
	write(0x30, COMMAND);
	delay(5);	
	write(0x08, COMMAND);
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
	delay(1);
	LCD_E = 1;
	delay(1);
	LCD_E = 0;
}

void draw_GDRAM(uchar *image)
{
     uint y, yi, xi;
     write(0x34, COMMAND);     // ��չָ�����ʱ�ر� GDRAM ��ʾ
	 write(0x36, COMMAND);

     // �ϰ�����y 0-31��x 0x80-0x87����ͬ�� DDRAM ǰ���У�
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi �� y ��ַ������32 �У�ÿ��ѭ��дһ��
     {
          write(y+yi, COMMAND);     // y ��ַ��ÿ�μ� 1
          write(0x80, COMMAND);     // ÿдһ�� x ���Ǵ����� 0x80 ��ʼ��x ��ַ�����ֶ��� 1
          for(xi=0;xi<16;xi++)     // xi �� x ��ַ������������8 �У�ÿ�� 2 ���ֽڣ�ÿ��ѭ��дһ���ֽ�
          {
                a = *image;
				write(*image++, DATA);
          }
     }
     
     // �°�����y 0-31��x 0x88-0x8F����ͬ�� DDRAM ǰ���У�
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi �� y ��ַ������32 �У�ÿ��ѭ��дһ��
     {
          write(y+yi, COMMAND);     // y ��ַ��ÿ�μ� 1
          write(0x88, COMMAND);     // ÿдһ�� x ���Ǵ����� 0x88 ��ʼ��x ��ַ�����ֶ��� 1
          for(xi=0;xi<16;xi++)     // xi �� x ��ַ������������8 �У�ÿ�� 2 ���ֽڣ�ÿ��ѭ��дһ���ֽ�
          {
               write(*image++, DATA);
          }
     }

     write(0x36, COMMAND);     // �� GDRAM ��ʾ
     write(0x30, COMMAND);     // �ػ���ָ�
}

void clear_GDRAM()
{
	 uint y, yi, xi;
     write(0x34, COMMAND);     // ��չָ�����ʱ�ر� GDRAM ��ʾ
	 write(0x36, COMMAND);

     // �ϰ�����y 0-31��x 0x80-0x87����ͬ�� DDRAM ǰ���У�
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi �� y ��ַ������32 �У�ÿ��ѭ��дһ��
     {
          write(y+yi, COMMAND);     // y ��ַ��ÿ�μ� 1
          write(0x80, COMMAND);     // ÿдһ�� x ���Ǵ����� 0x80 ��ʼ��x ��ַ�����ֶ��� 1
          for(xi=0;xi<16;xi++)     // xi �� x ��ַ������������8 �У�ÿ�� 2 ���ֽڣ�ÿ��ѭ��дһ���ֽ�
          {
               write(0x00, DATA);
          }
     }
     
     // �°�����y 0-31��x 0x88-0x8F����ͬ�� DDRAM ǰ���У�
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi �� y ��ַ������32 �У�ÿ��ѭ��дһ��
     {
          write(y+yi, COMMAND);     // y ��ַ��ÿ�μ� 1
          write(0x88, COMMAND);     // ÿдһ�� x ���Ǵ����� 0x88 ��ʼ��x ��ַ�����ֶ��� 1
          for(xi=0;xi<16;xi++)     // xi �� x ��ַ������������8 �У�ÿ�� 2 ���ֽڣ�ÿ��ѭ��дһ���ֽ�
          {
               write(0x00, DATA);
          }
     }

     write(0x36, COMMAND);     // �� GDRAM ��ʾ
     write(0x30, COMMAND);     // �ػ���ָ�
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}