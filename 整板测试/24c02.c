//����AT24C02EEPROMоƬ����
#include <config.h>
uchar sec;        									//�������ֵ��ÿ��1�룬sec��1
uint tcnt;        									//��ʱ�жϴ���
bit  write=0;             							//д24C08�ı�־��
void delay_24c(uchar i)								//��ʱ����
{
	uchar j,k;
	for(j=i;j>0;j--)
    	for(k=125;k>0;k--);
}
void display_24c(uchar bai_c,uchar sh_c)			//��ʾ����
{
   dula=0;
   P0=seg_table[bai_c];								//��ʾ��λ
   dula=1;
   dula=0;
   wela=0;
   P0=0x7e;
   wela=1;
   wela=0;
   delay_24c(5);

   dula=0;
   P0=seg_table[sh_c];								//��ʾʮλ
   dula=1;
   dula=0;
   wela=0;
   P0=0x7d;
   wela=1;
   wela=0;
   delay_24c(5);

}

/********************************24C08��д��������************************************/
void delay3_24c(unsigned char x)
{ 
	uint i;
	for(i=0;i<x;i++);
}
void flash()
{  
	;  
	; 
}

void x24c08_init()  								//24c08��ʼ���ӳ���
{
	scl=1; 
	flash(); 
	sda=1; 
	flash();
}
void start_24c()        							//����I2C����
{
	sda=1; 
	flash(); 
	scl=1; 
	flash(); 
	sda=0; 
	flash(); 
	scl=0; 
	flash();
}

void stop()         								//ֹͣI2C����
{
	sda=0; 
	flash(); 
	scl=1; 
	flash(); 
	sda=1; 
	flash();
}

void writex(uchar j)		 						//дһ���ֽ�
{  
	uchar i,temp;
   	temp=j;
   	for (i=0;i<8;i++)
   	{
		temp=temp<<1; 
		scl=0; 
		flash(); 
		sda=CY; 
		flash(); 
		scl=1; 
		flash();
	}
   	scl=0; 
	flash(); 
	sda=1; 
	flash();
}

uchar readx()   									//��һ���ֽ�
{
   uchar i,j,k=0;
   scl=0; flash(); sda=1;
   for (i=0;i<8;i++)
   {  
   		flash(); scl=1; flash();
      	if (sda==1) j=1;
      		else j=0;
      	k=(k<<1)|j;
	  	scl=0;
	}
   flash(); 
   return(k);
}
void clock()         								//I2C����ʱ��
{
	unsigned char i=0;
   	scl=1; flash();
   	while ((sda==1)&&(i<255))i++;
   	scl=0; flash();
}
//��24c02�ĵ�ַaddress�ж�ȡһ���ֽ�����
uchar x24c08_read(uchar address)
{
	uchar i;
	start_24c(); writex(0xa0);
	clock(); writex(address);
	clock(); start_24c();
	writex(0xa1); clock();
	i=readx(); stop();
	delay3_24c(10);
	return(i);
}
//��24c02��address��ַ��д��һ�ֽ�����info
void x24c08_write(uchar address,uchar info)
{
	EA=0;
	start_24c(); writex(0xa0);
	clock(); writex(address);
	clock(); writex(info);
	clock(); stop();
	EA=1;
	delay3_24c(50);
}

void at24c02_main()
{
	uchar i;
	system_init();
	x24c08_init();        					//��ʼ��24C08
	sec=x24c08_read(2);						//������������ݸ���sec
	while(message=='8')
   	{
	    if(sec==100) sec=0;					//��ʱ100�룬�ڴ��㿪ʼ��ʱ    
		write=1;  							//1��дһ��24C08
		sec++;
	  	i=255;
      	while(i--)
      	{			   
 			display_24c(sec/10,sec%10);
      	}
		if(write==1) 						//�жϼ�ʱ���Ƿ��ʱһ��
       	{
	 		write=0;              			//����
          	x24c08_write(2,sec);  			//��24c08�ĵ�ַ2��д������sec
       	}

	} 
    P0=0xff;
  	wela=1;
	wela=0;
}
