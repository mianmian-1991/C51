// 此处为晶振为 11.0592 且初值为 0 时的取值，如用其它频率的晶振，要改变相应的取值。
#define Imax  14000             
#define Imin  8000                
#define Inum1 1450                
#define Inum2 700
#define Inum3 3000

uchar Im[4] = {0x00,0x00,0x00,0x00};    // 遥控器取码，键码保存于 Im[2] ，Im[3] 是其反码用于校正

uchar Ir_begin;    // 遥控器启始码标志
uchar IrOK;        // 遥控器取码成功标志
unsigned long m,Tc;        // m 取码时定位数用，Tc 是 INT1 中断时 T0 时长，用以确定传入 1/0 

void init_Infrared()
{
    EA = 1;

    IT1 = 1;    // INT1 下降沿中断
    EX1 = 1;

    TMOD = 0x01;                    // T0 方式 1，不需要中断   
    TH0  = 0x00;
    TL0  = 0x00;
    TR0  = 1;
    ET0 = 0;
}

void Inf_get(void) interrupt 2    // INT1 中断程序 ，取键码
{
    Tc = TH0 * 256 + TL0;                      // 提取 INT1 中断时 T0 时长
    TH0 = 0;
    TL0 = 0;                                   // T0 重新计时

    if((Tc > Imin) && (Tc < Imax))                // Tc 在 Imin 和 Imax 之间，说明遥控器开始有码传入
    {
        m = 0;
        Ir_begin = 1;        // 启始标志
        return;
    }

    if(Ir_begin == 1)   
    {
        // 每次中断右移一位，如果 Tc>Inum1 最高位就加一位 1 进来，否则加 0，共取四个字节到 Im[0]~Im[3] 中
        // 只有 Im[2] 存的是键码值，Im[3] 是其反码，用来校验
        if(Tc > Inum1 && Tc < Inum3)    // Inum1 < Tc < Inum3
          {
            Im[m / 8] = Im[m / 8] >> 1 | 0x80;
            m++;
         }
        if(Tc > Inum2 && Tc < Inum1)     // Inum2 < Tc < Inum1
        {
            Im[m / 8] = Im[m / 8] >> 1;     
            m++;                   
        }

        if(m == 32)        // 四个字节取完了
         {
            m = 0; 
            Ir_begin = 0;
               if(Im[2] ==~ Im[3])     // 二者按位反，说明读码正确 ，完毕
            {
                IrOK =1 ;
            }
            else
            {
                IrOK = 0;
            }
        }
    }   
}

