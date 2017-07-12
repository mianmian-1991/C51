#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

uchar a = 0xfe;   // 11111110 ���һλ�� 

void delayms(uint);

void main()
{
	while(1)
	{	
		P1 = a;
		a = _crol_(a,1);   // ѭ������ 
		delayms(500);
	}
}

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}