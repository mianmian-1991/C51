#include <config.h>
void delay_da(uchar i)		//ÑÓÊ±³ÌÐò
{
	uchar j,k;
    for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void da_main()
{
	uchar a,k;
	system_init();
    csda=0;
    a=0;
    dawr=0;
    while(message=='2')
    {
		for(k=0;k<255;k++)
		{
			P0=k;
			delay_da(20);
			//a++;
			if(message!='2') break;
		}
	}
}
