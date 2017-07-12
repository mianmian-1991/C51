#include <reg52.h>

#define uchar unsigned char 

#define Imax  14000               // �˴�Ϊ����Ϊ11.0592ʱ��ȡֵ, 
#define Imin  8000                // ��������Ƶ�ʵľ���ʱ,
#define Inum1 1450                // Ҫ�ı���Ӧ��ȡֵ��
#define Inum2 700 
#define Inum3 3000 

sbit Duanxuan = P2^6;        
sbit Weixuan = P2^7;

// ��ѡ U1
uchar code DigitronTable[] =
{
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71
};

// λѡ U2
uchar code WeiTable[] =
{
    0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf
};

uchar Im[4] = {0x00,0x00,0x00,0x00};	// ң����ȡ�뱣���� Im[2]

uchar f;	// ң������ʼ���־
uchar IrOK;		// ң����ȡ��ɹ���־
unsigned long m,Tc;		// m ȡ��ʱ��λ���ã�Tc �� INT1 �ж�ʱ T0 ʱ������ȷ����ֵ���ź�
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
	    Inf_Dispose();            //������մ���
        display(key);                //�������ʾ
    }
}

void init()
{
	EA = 1;
	
	IT1 = 1;	// INT1 �½����ж�
    EX1 = 1;

	TMOD = 0x01;                    // T0 ��ʽ 1������Ҫ�ж�   
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
    P0 = DigitronTable[num/16];     // ����
    Duanxuan = 0;
    P0 = 0xff;     // ��Ӱ
    Weixuan = 1;
    P0 = WeiTable[0];     // λ��
    Weixuan = 0;
    delay(3);
	
	Duanxuan = 1;
    P0 = DigitronTable[num%16];     // ����
    Duanxuan = 0;
    P0 = 0xff;     // ��Ӱ
    Weixuan = 1;
    P0 = WeiTable[1];     // λ��
    Weixuan = 0;
    delay(3);
}

void intersvr1(void) interrupt 2 using 1	// INT1 �жϳ���
{
	Tc = TH0 * 256 + TL0;                      // ��ȡ INT1 �ж�ʱ T0 ʱ��
	TH0 = 0x00; 
    TL0 = 0x00;                                   // T0 ���¼�ʱ

	if((Tc > Imin) && (Tc < Imax))				// Tc �� Imin �� Imax ֮�䣬˵���ҵ�ң������ʼ���봫��
    { 
		m = 0;
        f = 1;		// ��ʼ��־
		return;
    }

    if(f == 1)	
    {
		// ÿ���ж�����һλ����� Tc>Inum1 ���λ�ͼ�һλ 1 ��������ȡ�ĸ��ֽڵ� Im[0]~Im[3] ��
		// ֻ�� Im[2] ����Ǽ���ֵ��Im[3] ���䷴�룬����У��
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

		if(m == 32)		// �ĸ��ֽ�ȡ���� 
	 	{
            m = 0;  
            f = 0;
       	    if(Im[2] ==~ Im[3]) 	// ���߰�λ����˵��������ȷ
	        {
                IrOK =1 ;
		    }
            else 
            {
                IrOK = 0;   // ȡ����ɺ��ж϶����Ƿ���ȷ
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


