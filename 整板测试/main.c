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
						send_string("LED检测，按RESET退出");
						led_main();
						start();
						break;	
					}
			case '2':
					{	
						send_string("DA检测，按RESET退出");
						da_main();
						start();
						break;	
					}
			case '3':
					{	
						send_string("AD检测，按RESET退出");
						ad_main();
						start();
						break;	
					}	

			case '4':
					{	
						send_string("矩阵建盘检测，按RESET退出");
						key_main();
						start();
						break;
					}

			case '5':
					{	
						send_string(" DS12B20检测，按RESET退出");
						ds18b20_main();
						start();
						break;
					}
			case '6':
					{	
						send_string("1602液晶检测，需将液晶插上并调节相应电位器，按RESET退出");
						tx1602_main();
						start();
						break;	
					}
			case '7':
					{	
						send_string(" 12864液晶检测，需将液晶插上并调节相应电位器，按RESET退出");
						tx12864_main();
						start();
						break;
					}
			case '8':
					{	
						send_string(" AT24C02检测，按RESET退出");
						at24c02_main();
						start();
						break;
					}
			case '9':
					{	
						send_string("点阵检测，需如下连接杜邦线:");
						send_string("\n\r	 P3.0 ----------> SCK\
									 \n\r	 P3.1 ----------> RCK\
									 \n\r	 P3.2 ----------> SDI");
						send_string("\n\r按RESET退出");
						dot_main();
						start();
						break;
					}
			case 'a':
					{	
						send_string("DS12C887检测，需接入1602液晶并如下连接杜邦线:");

						send_string("\r\n	      P1.4 ----------> CS\
									 \r\n	      P1.5 ----------> AS\
									 \r\n	      P1.6 ----------> WR\
									 \r\n	      P1.7 ----------> RD\
									 \r\n	 P0.0~P0.7 ----------> AD0~AD7");
						send_string("\n\r按RESET退出");	
						ds12c887_main();
						start();
						break;
					}
			case 'b':
					{
						send_string("步进电机检测，需接入步进电机并如下连接杜邦线:");
						send_string("\n\r	      P3.3 ---------->  IO(红外)\
									 \n\r	 P1.0~P1.3 ---------->  INA~IND(步进电机)");
						send_string("\n\r按RESET退出");	
						step_main();
						start();
						break;
					}
			case 'c':
					{	
						send_string("直流电机检测，需接入直流电机并如下连接杜邦线:");
						send_string("\n\r	 P2.2 ---------->  DC(直流电机)\
									 \n\r	 P3.3 ---------->  IO(红外)");
						send_string("\n\r按RESET退出");	
						dc_main();
						start();
						break;
					}
			case 'd':
					{	
						send_string("舵机检测，需接入舵机并如下连接杜邦线:");
						send_string("\n\r	 P2.1 ---------->  SE(舵机)\
									 \n\r	 P3.3 ---------->  IO(红外)");
						send_string("\n\r按RESET退出");	
						helm_main();
						start();
						break;
					}
			case 'e':
					{	
						send_string("继电器检测，需如下连接杜邦线:");
						send_string("\n\r	 P2.0 ---------->  RYIN(继电器)\
									 \n\r	 P3.3 ---------->  IO(红外)");
						send_string("\n\r按RESET退出");	
						relay_main();
						start();
						break;
					}
		}
}
