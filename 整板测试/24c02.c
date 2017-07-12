//试验AT24C02EEPROM芯片程序
#include <config.h>
uchar sec;        									//定义计数值，每过1秒，sec加1
uint tcnt;        									//定时中断次数
bit  write=0;             							//写24C08的标志；
void delay_24c(uchar i)								//延时程序
{
	uchar j,k;
	for(j=i;j>0;j--)
    	for(k=125;k>0;k--);
}
void display_24c(uchar bai_c,uchar sh_c)			//显示程序
{
   dula=0;
   P0=seg_table[bai_c];								//显示百位
   dula=1;
   dula=0;
   wela=0;
   P0=0x7e;
   wela=1;
   wela=0;
   delay_24c(5);

   dula=0;
   P0=seg_table[sh_c];								//显示十位
   dula=1;
   dula=0;
   wela=0;
   P0=0x7d;
   wela=1;
   wela=0;
   delay_24c(5);

}

/********************************24C08读写驱动程序************************************/
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

void x24c08_init()  								//24c08初始化子程序
{
	scl=1; 
	flash(); 
	sda=1; 
	flash();
}
void start_24c()        							//启动I2C总线
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

void stop()         								//停止I2C总线
{
	sda=0; 
	flash(); 
	scl=1; 
	flash(); 
	sda=1; 
	flash();
}

void writex(uchar j)		 						//写一个字节
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

uchar readx()   									//读一个字节
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
void clock()         								//I2C总线时钟
{
	unsigned char i=0;
   	scl=1; flash();
   	while ((sda==1)&&(i<255))i++;
   	scl=0; flash();
}
//从24c02的地址address中读取一个字节数据
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
//向24c02的address地址中写入一字节数据info
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
	x24c08_init();        					//初始化24C08
	sec=x24c08_read(2);						//读出保存的数据赋于sec
	while(message=='8')
   	{
	    if(sec==100) sec=0;					//定时100秒，在从零开始计时    
		write=1;  							//1秒写一次24C08
		sec++;
	  	i=255;
      	while(i--)
      	{			   
 			display_24c(sec/10,sec%10);
      	}
		if(write==1) 						//判断计时器是否计时一秒
       	{
	 		write=0;              			//清零
          	x24c08_write(2,sec);  			//在24c08的地址2中写入数据sec
       	}

	} 
    P0=0xff;
  	wela=1;
	wela=0;
}
