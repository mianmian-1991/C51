/*--------------------------------------------------------------------------
DEBUG51.H

Little Rain Studio Release 2014-07-10
--------------------------------------------------------------------------*/

#ifndef ___DEBUG51_H___
#define ___DEBUG51_H___


#define				XTAL				11.0592			//����Ƶ��(MHz) �ο�ֵ: 6, 11.0592, 12, 12.288, 16, 20, 22.1184, 24
#define				BAUD				9600			//������(Baud)  �ο�ֵ: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200

void				UART_Init();						//���ڳ�ʼ��
unsigned char		help();								//�������
unsigned char		getr(unsigned char idata *buf);		//get register
unsigned char		setr(unsigned char idata *buf);		//set register
unsigned char		geti(unsigned char idata *buf);		//get idata
unsigned char		seti(unsigned char idata *buf);		//set idata
void				debug51();							//���ڵ��Ժ���


#endif