#include <config.h>
uchar code table1_1602[]="TX-1C TEST   ";
uchar code table2_1602[]="WWW.TXMCU.COM";
void delay_1602(uint x)
{
	uint a,b;
	if(message!='6') return;
	for(a=x;a>0;a--)
		for(b=10;b>0;b--); 
}

void delay1_1602(uint x)
{
	uint a,b;
	if(message!='6') return;
	for(a=x;a>0;a--)
		for(b=100;b>0;b--); 
}

void lcd_write_com(uchar com)
{
	P0=com;
	rs=0;
	lcden=0;
	delay_1602(10);
	lcden=1;
	delay_1602(10);
	lcden=0;
	
}

void lcd_write_date(uchar date)
{
	P0=date;
	rs=1;
	lcden=0;
	delay_1602(10);
	lcden=1;
	delay_1602(10);
	lcden=0;
	
}

void init()
{
	lcd_write_com(0x38);
	delay_1602(20);
	lcd_write_com(0x0f);
	delay_1602(20);
	lcd_write_com(0x06);
	delay_1602(20);
	lcd_write_com(0x01);
	delay_1602(20);	
}

void tx1602_main()
{
	uchar a;
	system_init();
	init();
	lcd_write_com(0x80+17);
	delay_1602(20);
	for(a=0;a<13;a++)
	{
		//if(message!='6') break;
		lcd_write_date(table1_1602[a]);
		delay_1602(20);		
	}
	lcd_write_com(0xc0+17);
	delay_1602(50);
	for(a=0;a<13;a++)
	{
		//if(message!='6') break;
		lcd_write_date(table2_1602[a]);
		delay_1602(40);		
	}	
	for(a=0;a<16;a++)
	{
		//if(message!='6') break;
		lcd_write_com(0x18);
		delay1_1602(200);
	}
	delay1_1602(1000);
	while(message=='6') ;
}

