/*--------------------------------------------------------------------------
DEBUG51.H

Little Rain Studio Release 2014-07-10
--------------------------------------------------------------------------*/

#ifndef ___DEBUG51_H___
#define ___DEBUG51_H___


#define				XTAL				11.0592			//晶振频率(MHz) 参考值: 6, 11.0592, 12, 12.288, 16, 20, 22.1184, 24
#define				BAUD				9600			//波特率(Baud)  参考值: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200

void				UART_Init();						//串口初始化
unsigned char		help();								//命令帮助
unsigned char		getr(unsigned char idata *buf);		//get register
unsigned char		setr(unsigned char idata *buf);		//set register
unsigned char		geti(unsigned char idata *buf);		//get idata
unsigned char		seti(unsigned char idata *buf);		//set idata
void				debug51();							//串口调试函数


#endif
