#include <reg52.h>

#define uchar unsigned char 

#define Imax  14000               // 此处为晶振为11.0592时的取值, 
#define Imin  8000                // 如用其它频率的晶振时,
#define Inum1 1450                // 要改变相应的取值。
#define Inum2 700 
#define Inum3 3000 

sbit Duanxuan = P2^6;        
sbit Weixuan = P2^7;
sbit pwm = P1^7 ;                 // PWM信号输出

uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //数码管段码

uchar Im[4] = {0x00,0x00,0x00,0x00};	// 遥控器取码保存于 Im[2]

uchar f;	// 遥控器启始码标志
uchar IrOK;		// 遥控器取码成功标志
uchar PulseWidth = 0;             // 脉宽值
uchar StartFlag = 0;              // 启动/停止 标志位：0 停止，1 启动
uchar count;                      // 0.5ms 次数标识
unsigned long m,Tc;		// m 取码时定位数用，Tc 是 INT1 中断时 T0 时长，是确定码值的信号

void init();
void delay(uchar);
void display();
void Inf_Dispose();

void main(void)
{ 
	init();

	while(1)
	{
	    Inf_Dispose();            //红外接收处理
        display();                //数码管显示
    }
}

void init()
{
	m = 0;
    f = 0;    
    PulseWidth = 0;
    count = 0; 
    pwm = 0;

	EA = 1;		// 总中断允许
	
	IT1 = 1;	// INT1 下降沿有效
    EX1 = 1;	// INT1 中断允许
	
	TMOD = 0x11;   // T1 和 T0 均为方式 1，T0 用来获取键码，T1 用来制造 PWM，其实也可以都用 T0，但那样使用红外的期间电机就不转了
	TH0  = 0x00;
	TL0  = 0x00;
	TH1  = 0xfe;
	TL1  = 0x33;	//11.0592MZ晶振，0.5ms
	ET1 = 1;
    ET0 = 0;
		             
    TR0 = 1;
	TR1 = 1;
}

void delay(uchar i)
{
    uchar j,k; 

    for(j = i;j > 0;j--)
    {
        for(k = 110;k > 0;k--);
    }  
}

void display(void)
{ 
    Duanxuan = 0;
    P0 = table[PulseWidth/10];             //显示脉宽值高位
    Duanxuan = 1;
    Duanxuan = 0;

    Weixuan = 0;
    P0 = 0xfe;
    Weixuan = 1;
    Weixuan = 0;
    delay(5);
}

void intersvr1(void) interrupt 2 using 1	// INT1 中断程序
{
	Tc = TH0 * 256 + TL0;                      // 提取 INT1 中断时 T0 时长
	TH0 = 0; 
    TL0 = 0;                                   // T0 重新计时

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
        switch(Im[2])   
        {
            case 0x44:                   // 0100 0100 遥控器 开始/停止 键按下 启动停止控制
                StartFlag =~ StartFlag;		// 开始/停止 状态切换
                if(StartFlag)            // 切换到开始
                {
                    if(PulseWidth)       // 注意当脉宽值不为 0 时才可以启动
                    {
                        ET0 = 1;	// T0 中断允许
                    }
                }
                else                     //停止
                {
                    ET0 = 0;	// T0 中断关闭
                    pwm = 0;	// PWM 始终低电平
                }
            	break;

            case 0x09:                   // 0000 1001 遥控器 - 键按下 脉宽值加10
                PulseWidth += 10;                   
                count=0;                 
                if(PulseWidth==60)              
                {
                    PulseWidth = 50;        // 最大 50        
                }
            break;

            case 0x15:                   // 0001 0101 遥控器 + 键按下 脉宽值减10
                PulseWidth -= 10;                   
                count=0;
                if(PulseWidth == 0)
                {
                    PulseWidth = 10;        // 最小 10    
                } 
                if(PulseWidth == 246)
                {
                    PulseWidth = 0;
                }               
            break;

            default:
            break;
        }
        IrOK = 0;	   
	}
}

void Time1() interrupt 3        // T1 中断程序
{
	TH1  = 0xfe;                    // 重装初值，50ms
	TL1  = 0x33;
    
    count++;		// 先输出高电平，同时计数
    if(count == PulseWidth)         // 到达脉宽值，开始输出低电平                
    {
        pwm = 0;
    }

    if(count == 60)	//	30ms 周期
    {
        pwm = 1;                    // 下一个周期开始输出高电平
        count = 0;
    }   
}
