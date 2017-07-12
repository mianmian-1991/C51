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
     write(0x34, COMMAND);     // 扩展指令集，暂时关闭 GDRAM 显示
	 write(0x36, COMMAND);

     // 上半屏：y 0-31，x 0x80-0x87（等同于 DDRAM 前两行）
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi 是 y 地址增量，32 行，每个循环写一行
     {
          write(y+yi, COMMAND);     // y 地址，每次加 1
          write(0x80, COMMAND);     // 每写一行 x 总是从行首 0x80 开始，x 地址不用手动加 1
          for(xi=0;xi<16;xi++)     // xi 是 x 地址增量的两倍，8 列，每列 2 个字节，每个循环写一个字节
          {
                a = *image;
				write(*image++, DATA);
          }
     }
     
     // 下半屏：y 0-31，x 0x88-0x8F（等同于 DDRAM 前两行）
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi 是 y 地址增量，32 行，每个循环写一行
     {
          write(y+yi, COMMAND);     // y 地址，每次加 1
          write(0x88, COMMAND);     // 每写一行 x 总是从行首 0x88 开始，x 地址不用手动加 1
          for(xi=0;xi<16;xi++)     // xi 是 x 地址增量的两倍，8 列，每列 2 个字节，每个循环写一个字节
          {
               write(*image++, DATA);
          }
     }

     write(0x36, COMMAND);     // 打开 GDRAM 显示
     write(0x30, COMMAND);     // 回基本指令集
}

void clear_GDRAM()
{
	 uint y, yi, xi;
     write(0x34, COMMAND);     // 扩展指令集，暂时关闭 GDRAM 显示
	 write(0x36, COMMAND);

     // 上半屏：y 0-31，x 0x80-0x87（等同于 DDRAM 前两行）
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi 是 y 地址增量，32 行，每个循环写一行
     {
          write(y+yi, COMMAND);     // y 地址，每次加 1
          write(0x80, COMMAND);     // 每写一行 x 总是从行首 0x80 开始，x 地址不用手动加 1
          for(xi=0;xi<16;xi++)     // xi 是 x 地址增量的两倍，8 列，每列 2 个字节，每个循环写一个字节
          {
               write(0x00, DATA);
          }
     }
     
     // 下半屏：y 0-31，x 0x88-0x8F（等同于 DDRAM 前两行）
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi 是 y 地址增量，32 行，每个循环写一行
     {
          write(y+yi, COMMAND);     // y 地址，每次加 1
          write(0x88, COMMAND);     // 每写一行 x 总是从行首 0x88 开始，x 地址不用手动加 1
          for(xi=0;xi<16;xi++)     // xi 是 x 地址增量的两倍，8 列，每列 2 个字节，每个循环写一个字节
          {
               write(0x00, DATA);
          }
     }

     write(0x36, COMMAND);     // 打开 GDRAM 显示
     write(0x30, COMMAND);     // 回基本指令集
}

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}