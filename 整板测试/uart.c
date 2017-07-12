#include <config.h>
uchar message=100;
void send_char(uchar date)

{
   	SBUF=date;             // 发送数据
	while(!TI);
	TI=0;				      // 等待数据发送完毕
}

void send_string(uchar code *buffer)	 //注意指针类型，
{  										 //在编程中有普通的RAM的指针，也有falsh的指针。
   while( *buffer !='\0') 				 //由于我们发送的是字符串这个字符串是来自flash存储器。
   send_char(*buffer++);				 //因而我们定义的指针应为 const *
										 //在有些GCC程序中有这个区别，但在keil环境下，这方面没有区别，都可以使用
}


void start()
{ 
  send_string("\r\n\r\n                       TX-1C BOARD TEST \
  \r\n\r\n           Please chose the index number then press Enter \
  \r\n\r\n1.LED      2.DA      3.AD      4.key      5.DS18B20      6.1602   \
      \r\n7.12864    8.24c02   9.dot     a.12887    b.stepmotor    c.dcmotor\
  	  \r\nd.helm     e.relay   \
  \r\n\r\nTXMCU_CMD==>");
}


/****************************************************************************
send a string
****************************************************************************/


void uart()
{
	TMOD=0x21;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;
	PCON=0x80;
}
void serial() interrupt 4
{
	if(RI)
	{	
		RI=0;
		if((SBUF=='1')||(SBUF=='2')||(SBUF=='3')||(SBUF=='4')||(SBUF=='5')||(SBUF=='6')||(SBUF=='7')||(SBUF=='8')||(SBUF=='9')||(SBUF=='a')||(SBUF=='b')||(SBUF=='c')||(SBUF=='d')||(SBUF=='e')) message=SBUF;
		//((void (code *) (void)) 0) ();
	}
	//P11 = ~P11;
}
