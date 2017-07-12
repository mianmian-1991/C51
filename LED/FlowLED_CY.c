#include<reg52.h>
//#include "DEBUG51.H"

#define uchar unsigned char
#define uint unsigned int

uchar a = 0xfe;   // 11111110 最后一位亮
uchar flag;
	
void delayms(uint);

void main()
{
	//UART_Init();     // 调试串口初始化

	while(1)
	{	
		P1 = a;

		// 循环左移
		// a = (a<<1) | CY;

   		// 循环右移
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