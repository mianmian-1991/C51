#include <config.h>
#define uint unsigned int
#define uchar unsigned char
uint temp;             					// variable of temperature
uchar flag1;            				// sign of the result positive or negative
void delay_ds18b20(uint count)      	//delay
{
	uint i;
  	while(count)
  	{
    	i=200;
    	while(i>0)
    	i--;
    	count--;
  	}
}
///////功能:串口初始化,波特率9600，方式1///////
void dsreset(void)       				//send reset and initialization command
{
  	uint i;
  	DS=0;
  	i=103;
  	while(i>0)i--;
  	DS=1;
  	i=4;
  	while(i>0)i--;
}

bit tmpreadbit(void)       				//read a bit
{
   	uint i;
   	bit dat;
   	DS=0;i++;          					//i++ for delay
   	DS=1;i++;i++;
   	dat=DS;
   	i=8;while(i>0)i--;
   	return (dat);
}

uchar tmpread(void)   					//read a byte date
{
  	uchar i,j,dat;
  	dat=0;
  	for(i=1;i<=8;i++)
  	{
	    j=tmpreadbit();
	    dat=(j<<7)|(dat>>1);   			//读出的数据最低位在最前面，这样刚好一个字节在DAT里
  	}
  	return(dat);
}

void tmpwritebyte(uchar dat)   			//write a byte to ds18b20
{
  	uint i;
  	uchar j;
  	bit testb;
  	for(j=1;j<=8;j++)
  	{
	    testb=dat&0x01;
	    dat=dat>>1;
	    if(testb)     					//write 1
    	{
      		DS=0;
      		i++;i++;
	      	DS=1;
	      	i=8;while(i>0)i--;
    	}
    	else
    	{
      		DS=0;       				//write 0
      		i=8;while(i>0)i--;
      		DS=1;
      		i++;i++;
    	}
  	}
}

void tmpchange(void)  					//DS18B20 begin change
{
	dsreset();
  	delay_ds18b20(1);
  	tmpwritebyte(0xcc);  				// address all drivers on bus
  	tmpwritebyte(0x44);  				//  initiates a single temperature conversion
}

uint tmp()              				//get the temperature
{
  	float tt;
  	uchar a,b;
  	dsreset();
	delay_ds18b20(1);
  	tmpwritebyte(0xcc);
  	tmpwritebyte(0xbe);
  	a=tmpread();
  	b=tmpread();
  	temp=b;
  	temp<<=8;             				//two byte  compose a int variable
  	temp=temp|a;
  	tt=temp*0.0625;
  	temp=tt*10+0.5;
  	return temp;
}

void display_18b20(uint temp)			//显示程序
{	
   	uchar A1,A2,A2t,A3,ser;
   	ser=temp/10;
//   SBUF=ser;
   	A1=temp/100;
   	A2t=temp%100;
   	A2=A2t/10;
   	A3=A2t%10;

   	P0=0x00;
	dula=0;
   	P0=seg_table[A1];					//显示百位
   	dula=1;
   	dula=0;
	P0=0xff;
   	wela=0;
   	P0=0x7e;
   	wela=1;
   	wela=0;
   	delay_ds18b20(2);

	P0=0x00;
   	dula=0;
   	P0=seg_table[A2]|0x80;					//显示十位
   	dula=1;
   	dula=0;
	P0=0xff;
   	wela=0;
   	P0=0x7d;
   	wela=1;
   	wela=0;
   	delay_ds18b20(2);

	P0=0x00;
	dula=0;
   	P0=seg_table[A3];					//显示个位
   	dula=1;
   	dula=0;
	P0=0xff;
	wela=0;
   	P0=0x7b;
   	wela=1;
   	wela=0;
   	delay_ds18b20(2);
}

void ds18b20_main()
{
	system_init();
	while(message=='5')
	{
		//uchar a,c;
	  	//for(c=0;c<20;c++)
	  	//{
	    	tmpchange();
	   		//for(a=10;a>0;a--)
	     	//{
				display_18b20(tmp());
	     	//5}
		//}
 	}   
}

