#include <reg52.h>

#define uchar unsigned char 

#define Imax  14000               // �˴�Ϊ����Ϊ11.0592ʱ��ȡֵ, 
#define Imin  8000                // ��������Ƶ�ʵľ���ʱ,
#define Inum1 1450                // Ҫ�ı���Ӧ��ȡֵ��
#define Inum2 700 
#define Inum3 3000 

sbit Duanxuan = P2^6;        
sbit Weixuan = P2^7;
sbit pwm = P1^7 ;                 // PWM�ź����

uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //����ܶ���

uchar Im[4] = {0x00,0x00,0x00,0x00};	// ң����ȡ�뱣���� Im[2]

uchar f;	// ң������ʼ���־
uchar IrOK;		// ң����ȡ��ɹ���־
uchar PulseWidth = 0;             // ����ֵ
uchar StartFlag = 0;              // ����/ֹͣ ��־λ��0 ֹͣ��1 ����
uchar count;                      // 0.5ms ������ʶ
unsigned long m,Tc;		// m ȡ��ʱ��λ���ã�Tc �� INT1 �ж�ʱ T0 ʱ������ȷ����ֵ���ź�

void init();
void delay(uchar);
void display();
void Inf_Dispose();

void main(void)
{ 
	init();

	while(1)
	{
	    Inf_Dispose();            //������մ���
        display();                //�������ʾ
    }
}

void init()
{
	m = 0;
    f = 0;    
    PulseWidth = 0;
    count = 0; 
    pwm = 0;

	EA = 1;		// ���ж�����
	
	IT1 = 1;	// INT1 �½�����Ч
    EX1 = 1;	// INT1 �ж�����
	
	TMOD = 0x11;   // T1 �� T0 ��Ϊ��ʽ 1��T0 ������ȡ���룬T1 �������� PWM����ʵҲ���Զ��� T0��������ʹ�ú�����ڼ����Ͳ�ת��
	TH0  = 0x00;
	TL0  = 0x00;
	TH1  = 0xfe;
	TL1  = 0x33;	//11.0592MZ����0.5ms
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
    P0 = table[PulseWidth/10];             //��ʾ����ֵ��λ
    Duanxuan = 1;
    Duanxuan = 0;

    Weixuan = 0;
    P0 = 0xfe;
    Weixuan = 1;
    Weixuan = 0;
    delay(5);
}

void intersvr1(void) interrupt 2 using 1	// INT1 �жϳ���
{
	Tc = TH0 * 256 + TL0;                      // ��ȡ INT1 �ж�ʱ T0 ʱ��
	TH0 = 0; 
    TL0 = 0;                                   // T0 ���¼�ʱ

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
        switch(Im[2])   
        {
            case 0x44:                   // 0100 0100 ң���� ��ʼ/ֹͣ ������ ����ֹͣ����
                StartFlag =~ StartFlag;		// ��ʼ/ֹͣ ״̬�л�
                if(StartFlag)            // �л�����ʼ
                {
                    if(PulseWidth)       // ע�⵱����ֵ��Ϊ 0 ʱ�ſ�������
                    {
                        ET0 = 1;	// T0 �ж�����
                    }
                }
                else                     //ֹͣ
                {
                    ET0 = 0;	// T0 �жϹر�
                    pwm = 0;	// PWM ʼ�յ͵�ƽ
                }
            	break;

            case 0x09:                   // 0000 1001 ң���� - ������ ����ֵ��10
                PulseWidth += 10;                   
                count=0;                 
                if(PulseWidth==60)              
                {
                    PulseWidth = 50;        // ��� 50        
                }
            break;

            case 0x15:                   // 0001 0101 ң���� + ������ ����ֵ��10
                PulseWidth -= 10;                   
                count=0;
                if(PulseWidth == 0)
                {
                    PulseWidth = 10;        // ��С 10    
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

void Time1() interrupt 3        // T1 �жϳ���
{
	TH1  = 0xfe;                    // ��װ��ֵ��50ms
	TL1  = 0x33;
    
    count++;		// ������ߵ�ƽ��ͬʱ����
    if(count == PulseWidth)         // ��������ֵ����ʼ����͵�ƽ                
    {
        pwm = 0;
    }

    if(count == 60)	//	30ms ����
    {
        pwm = 1;                    // ��һ�����ڿ�ʼ����ߵ�ƽ
        count = 0;
    }   
}
