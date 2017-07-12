#include <config.h>
/*
#define m_clear       0
#define m_LED         1
#define m_DA          2
#define m_AD          3 
#define m_DS18B20     4
#define m_KEY         5
#define m_24C02       6
#define m_1602        7
#define m_12864       8
*/
void test_process();
void system_init()
{
	csda=0;
    dawr=0;
	P0=0xff;
	csda=1;
    dawr=1;
	P1 = 0xff;
	diola = 1;
	diola = 0;
	P0 = 0xff;
	dula = 1;
 	wela = 1;
	dula = 0;
	wela = 0;
	dc_motor = 0;
	relay = 0;
	helm_motor = 0;
	P1 &= 0xf0; 
	IE = 0x90;
}
void main()
{   				
	message=0;
	system_init();
	uart(); 
	start();   
	while(1)
   	{
 		test_process();
   	}
}
void test_process()
{		
		switch(message)
		{
			case 27:
					{
						start();
						break;	
					}
			case '1':
					{	
						send_string("LED��⣬��RESET�˳�");
						led_main();
						start();
						break;	
					}
			case '2':
					{	
						send_string("DA��⣬��RESET�˳�");
						da_main();
						start();
						break;	
					}
			case '3':
					{	
						send_string("AD��⣬��RESET�˳�");
						ad_main();
						start();
						break;	
					}	

			case '4':
					{	
						send_string("�����̼�⣬��RESET�˳�");
						key_main();
						start();
						break;
					}

			case '5':
					{	
						send_string(" DS12B20��⣬��RESET�˳�");
						ds18b20_main();
						start();
						break;
					}
			case '6':
					{	
						send_string("1602Һ����⣬�轫Һ�����ϲ�������Ӧ��λ������RESET�˳�");
						tx1602_main();
						start();
						break;	
					}
			case '7':
					{	
						send_string(" 12864Һ����⣬�轫Һ�����ϲ�������Ӧ��λ������RESET�˳�");
						tx12864_main();
						start();
						break;
					}
			case '8':
					{	
						send_string(" AT24C02��⣬��RESET�˳�");
						at24c02_main();
						start();
						break;
					}
			case '9':
					{	
						send_string("�����⣬���������ӶŰ���:");
						send_string("\n\r	 P3.0 ----------> SCK\
									 \n\r	 P3.1 ----------> RCK\
									 \n\r	 P3.2 ----------> SDI");
						send_string("\n\r��RESET�˳�");
						dot_main();
						start();
						break;
					}
			case 'a':
					{	
						send_string("DS12C887��⣬�����1602Һ�����������ӶŰ���:");

						send_string("\r\n	      P1.4 ----------> CS\
									 \r\n	      P1.5 ----------> AS\
									 \r\n	      P1.6 ----------> WR\
									 \r\n	      P1.7 ----------> RD\
									 \r\n	 P0.0~P0.7 ----------> AD0~AD7");
						send_string("\n\r��RESET�˳�");	
						ds12c887_main();
						start();
						break;
					}
			case 'b':
					{
						send_string("���������⣬����벽��������������ӶŰ���:");
						send_string("\n\r	      P3.3 ---------->  IO(����)\
									 \n\r	 P1.0~P1.3 ---------->  INA~IND(�������)");
						send_string("\n\r��RESET�˳�");	
						step_main();
						start();
						break;
					}
			case 'c':
					{	
						send_string("ֱ�������⣬�����ֱ��������������ӶŰ���:");
						send_string("\n\r	 P2.2 ---------->  DC(ֱ�����)\
									 \n\r	 P3.3 ---------->  IO(����)");
						send_string("\n\r��RESET�˳�");	
						dc_main();
						start();
						break;
					}
			case 'd':
					{	
						send_string("�����⣬����������������ӶŰ���:");
						send_string("\n\r	 P2.1 ---------->  SE(���)\
									 \n\r	 P3.3 ---------->  IO(����)");
						send_string("\n\r��RESET�˳�");	
						helm_main();
						start();
						break;
					}
			case 'e':
					{	
						send_string("�̵�����⣬���������ӶŰ���:");
						send_string("\n\r	 P2.0 ---------->  RYIN(�̵���)\
									 \n\r	 P3.3 ---------->  IO(����)");
						send_string("\n\r��RESET�˳�");	
						relay_main();
						start();
						break;
					}
		}
}
