#include <config.h>
uchar message=100;
void send_char(uchar date)

{
   	SBUF=date;             // ��������
	while(!TI);
	TI=0;				      // �ȴ����ݷ������
}

void send_string(uchar code *buffer)	 //ע��ָ�����ͣ�
{  										 //�ڱ��������ͨ��RAM��ָ�룬Ҳ��falsh��ָ�롣
   while( *buffer !='\0') 				 //�������Ƿ��͵����ַ�������ַ���������flash�洢����
   send_char(*buffer++);				 //������Ƕ����ָ��ӦΪ const *
										 //����ЩGCC��������������𣬵���keil�����£��ⷽ��û�����𣬶�����ʹ��
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
