#include <config.h>
void delay10ms()
  {
  	unsigned char a,b;
    for(a=150;a>0;a--)
    	for(b=250;b>0;b--);
}

void led_main()
{ 
  	uchar liushui,k;
	system_init();
	diola = 1;
  	k=0xfe;
	while(message=='1')
    {
		for(liushui=0;liushui<8;liushui++)
		{
			P1=k;
			delay10ms();
			beep=0;
			delay10ms();
			beep=1;
			k=_crol_(k,1);
			if(message!='1') break;
		}
    }
}
