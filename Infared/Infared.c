#include <reg52.h>

#define uchar unsigned char 

#define Imax  14000               // 此处为晶振为11.0592时的取值, 
#define Imin  8000                // 如用其它频率的晶振时,
#define Inum1 1450                // 要改变相应的取值。
#define Inum2 700 
#define Inum3 3000 

sbit Duanxuan = P2^6;        
sbit Weixuan = P2^7;

// 段选 U1
uchar code DigitronTable[] =
{
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71
};

// 位选 U2
uchar code WeiTable[] =
{
    0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};

uchar Im[4] = {0x00,0x00,0x00,0x00};	// 遥控器取码保存于 Im[2]

uchar f;	// 遥控器启始码标志
uchar IrOK;		// 遥控器取码成功标志
unsigned long m,Tc;		// m 取码时定位数用，Tc 是 INT1 中断时 T0 时长，是确定码值的信号
uchar key;

void init();
void delay(uchar);
void display(uchar);
void Inf_Dispose();

void main(void)
{ 
	init();

	while(1)
	{
	    Inf_Dispose();            //红外接收处理
        display(key);                //数码管显示
    }
}

void init()
{
	EA = 1;
	
	IT1 = 1;	// INT1 下降沿中断
    EX1 = 1;

	TMOD = 0x01;                    // T0 方式 1，不需要中断   
	TH0  = 0x00;
	TL0  = 0x00;
    TR0  = 1;
    ET0 = 0;
}

void delay(uchar i)
{
    uchar j,k; 

    for(j = i;j > 0;j--)
    {
        for(k = 110;k > 0;k--);
    }  
}

void display(uchar num)
{
    Duanxuan = 1;
    P0 = DigitronTable[num/16];     // 段码
    Duanxuan = 0;
    P0 = 0xff;     // 消影
    Weixuan = 1;
    P0 = WeiTable[0];     // 位码
    Weixuan = 0;
    delay(3);
	
	Duanxuan = 1;
    P0 = DigitronTable[num%16];     // 段码
    Duanxuan = 0;
    P0 = 0xff;     // 消影
    Weixuan = 1;
    P0 = WeiTable[1];     // 位码
    Weixuan = 0;
    delay(3);
}

void intersvr1(void) interrupt 2 using 1	// INT1 中断程序
{
	Tc = TH0 * 256 + TL0;                      // 提取 INT1 中断时 T0 时长
	TH0 = 0x00; 
    TL0 = 0x00;                                   // T0 重新计时

	if((Tc > Imin) && (Tc < Imax))				// Tc 在 Imin 和 Imax 之间，说明找到遥控器开始有码传入
    { 
		m = 0;
        f = 1;		// 启始标志
		return;
    }

    if(f == 1)	
    {
		// 每次中断右移一位，如果 Tc>Inum1 最高位就加一位 1 进来，共取四个字节到 Im[0]~Im[3] 中
		// 只有 Im[2] 存的是键码值，Im[3] 是其反码，用来校验
        if(Tc > Inum1 && Tc < Inum3)	// Inum1 < Tc < Inum3 
	  	{
			Im[m / 8] = Im[m / 8] >> 1 | 0x80;
            m++; 
     	}
    	if(Tc > Inum2 && Tc < Inum1) 	// Inum2 < Tc < Inum1
        {
        	Im[m / 8] = Im[m / 8] >> 1; 	
            m++;                   
		}

		if(m == 32)		// 四个字节取完了 
	 	{
            m = 0;  
            f = 0;
       	    if(Im[2] ==~ Im[3]) 	// 二者按位反，说明读码正确
	        {
                IrOK =1 ;
		    }
            else 
            {
                IrOK = 0;   // 取码完成后判断读码是否正确
            }
	    }
	}	
}

void Inf_Dispose(void)
{
    if(IrOK == 1) 
    { 
        key = Im[2];
        IrOK = 0;	   
	}
}


