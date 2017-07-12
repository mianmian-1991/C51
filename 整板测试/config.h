#ifndef _CONFIG_H
#define _CONFIG_H 1
#include <STC89C5xRC.h> 
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define Imax  14000               //�˴�Ϊ����Ϊ11.0592ʱ��ȡֵ, 
#define Imin  8000                //��������Ƶ�ʵľ���ʱ,
#define Inum1 1450                //Ҫ�ı���Ӧ��ȡֵ��
#define Inum2 700 
#define Inum3 3000 

sbit beep=P2^3;							//������
sbit adrd=P3^7;                         //AD
sbit adwr=P3^6;
sbit diola=P2^5;						//LED
sbit dula=P2^6;						   	//�����
sbit wela=P2^7;							
sbit csda=P3^2;							//DA
sbit dawr=P3^6;
sbit sda=P2^0;                          //24C02
sbit scl=P2^1;
sbit DS=P2^2;           				//18b20					
sbit DATA_IN = P1^0;	    			//����
sbit ST_CK = P1^1;	        			
sbit SH_CK = P1^2;	        			
sbit LCD_RS  =  P3^5;            		//LCD1602&12864
sbit LCD_RW  =  P3^6;           
sbit LCD_EN  =  P3^4;           
sbit LCD_PSB =  P3^7;      
sbit dscs=P1^4;	 						//DS12C887
sbit dsas=P1^5;
sbit dsrw=P1^6;
sbit dsds=P1^7;
sbit dsirq=P3^3;  
sbit rs=P3^5;
sbit lcden=P3^4;
sbit s1=P3^0;		//���ܼ�
sbit s2=P3^1;		//���Ӽ�
sbit s3=P3^2;		//��С��
sbit s4=P3^6;		//���Ӳ鿴��
sbit rd=P3^7;
sbit relay = P2^0 ;
sbit helm_motor = P1^7;
sbit dc_motor = P1^7;
 
extern void system_init();
extern void uart();
extern void start();
extern void send_string(uchar code *buffer);
extern void led_main();
extern void da_main();
extern void ad_main();
extern void key_main();
extern void ds18b20_main();
extern void tx1602_main();
extern void tx12864_main();
extern void at24c02_main();
extern void dot_main(void);
extern void ds12c887_main();
extern void step_main();
extern void dc_main();
extern void helm_main();
extern void relay_main();
extern void lcd_write_com(uchar com);
extern void lcd_write_date(uchar date);
extern void delay_1602(uint x);

extern uchar message;
extern uchar Im[4];
extern uchar f, IrOK;
extern uint Tc;
extern uchar code seg_table[];
extern uchar helm_jd, helm_count;                 	//���
extern uchar dc_count, PulseWidth, StartFlag ;   	//ֱ�����
extern unsigned long step_m;
#endif 