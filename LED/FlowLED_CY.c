#include<reg52.h>
//#include "DEBUG51.H"

#define uchar unsigned char
#define uint unsigned int

uchar a = 0xfe;   // 11111110 ���һλ��
uchar flag;
	
void delayms(uint);

void main()
{
	//UART_Init();     // ���Դ��ڳ�ʼ��

	while(1)
	{	
		P1 = a;

		// ѭ������
		// a = (a<<1) | CY;

   		// ѭ������
		a = (a>>1);
   		flag = CY;
		a = a | (flag<<7);

		delayms(500);
		//debug51();
	}
}

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}