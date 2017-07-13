// �˴�Ϊ����Ϊ 11.0592 �ҳ�ֵΪ 0 ʱ��ȡֵ����������Ƶ�ʵľ���Ҫ�ı���Ӧ��ȡֵ��
#define Imax  14000             
#define Imin  8000                
#define Inum1 1450                
#define Inum2 700
#define Inum3 3000

uchar Im[4] = {0x00,0x00,0x00,0x00};    // ң����ȡ�룬���뱣���� Im[2] ��Im[3] ���䷴������У��

uchar Ir_begin;    // ң������ʼ���־
uchar IrOK;        // ң����ȡ��ɹ���־
unsigned long m,Tc;        // m ȡ��ʱ��λ���ã�Tc �� INT1 �ж�ʱ T0 ʱ��������ȷ������ 1/0 

void init_Infrared()
{
    EA = 1;

    IT1 = 1;    // INT1 �½����ж�
    EX1 = 1;

    TMOD = 0x01;                    // T0 ��ʽ 1������Ҫ�ж�   
    TH0  = 0x00;
    TL0  = 0x00;
    TR0  = 1;
    ET0 = 0;
}

void Inf_get(void) interrupt 2    // INT1 �жϳ��� ��ȡ����
{
    Tc = TH0 * 256 + TL0;                      // ��ȡ INT1 �ж�ʱ T0 ʱ��
    TH0 = 0;
    TL0 = 0;                                   // T0 ���¼�ʱ

    if((Tc > Imin) && (Tc < Imax))                // Tc �� Imin �� Imax ֮�䣬˵��ң������ʼ���봫��
    {
        m = 0;
        Ir_begin = 1;        // ��ʼ��־
        return;
    }

    if(Ir_begin == 1)   
    {
        // ÿ���ж�����һλ����� Tc>Inum1 ���λ�ͼ�һλ 1 ����������� 0����ȡ�ĸ��ֽڵ� Im[0]~Im[3] ��
        // ֻ�� Im[2] ����Ǽ���ֵ��Im[3] ���䷴�룬����У��
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

        if(m == 32)        // �ĸ��ֽ�ȡ����
         {
            m = 0; 
            Ir_begin = 0;
               if(Im[2] ==~ Im[3])     // ���߰�λ����˵��������ȷ �����
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

