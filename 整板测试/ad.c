#include <config.h>
void delay_ad(uchar i)						//延时程序
{
	uchar j,k;
    for(j=i;j>0;j--)
    	for(k=125;k>0;k--);
}
void display(uchar bai_c, sh_c, g_c)		//显示程序
{
	dula=0;
	P0=seg_table[bai_c];					//显示百位
	dula=1;
	dula=0;
	wela=0;
	P0=0x7e;
	wela=1;
	wela=0;
	delay_ad(10);

	dula=0;
	P0=seg_table[sh_c];						//显示十位
	dula=1;
	dula=0;
	wela=0;
	P0=0x7d;
	wela=1;
	wela=0;
	delay_ad(10);
		
	dula=0;
	P0=seg_table[g_c];						//显示个位
	dula=1;
	dula=0;
	wela=0;
	P0=0x7b;
	wela=1;
	wela=0;
	delay_ad(10);
}
void ad_main()
{
	uchar a,b,A1,A2,A2t,A3,adval;
    b=0xf0;
	system_init();
    while(message=='3')
  	{
	    wela=1;
	    P0=0;                       //选通ADCS
	    adwr=0;					    //AD写入（随便写个什么都行，主要是为了启动AD转换）
	    _nop_();
	    adwr=1;
	    P0=0xff;                    //关闭ADCS
	
	    wela=0;                     //关闭有AD片选信号锁存器的锁存端以防止在操作数码管时使AD的片选发生变化
	    for(a=30;a>0;a--)        //需要注意的是ADC0804在写和读之间的时间间隔要足够长否则无法读出数据
	    {                          //这里把显示部分放这里的原因也是为了增加写读之间的时间间隔                                                                                                                                                                                                                           
	    	display(A1,A2,A3);
	    }	//送去显示各位。
		wela=1;                    //重新打开有AD片选信号锁存器的锁存端
	    P1=0xff;                    //读取P1口之前先给其写全1
	    P0=0;                       //选通ADCS
	    adrd=0;                     //AD读使能
	    adval=P1;				  //AD数据读取赋给P1口
	    adrd=1;
	    P0=0xff;                     //关闭ADCS
	    adwr=0;
	    P1=adval;                    //同时把AD的值送八个发光二极显示
	    A1=adval/100;		//分出百，十，和个位
	    A2t=adval%100;
	    A2=A2t/10;
	    A3=A2t%10;
	}
}

