#include <config.h>
void delay_ad(uchar i)						//��ʱ����
{
	uchar j,k;
    for(j=i;j>0;j--)
    	for(k=125;k>0;k--);
}
void display(uchar bai_c, sh_c, g_c)		//��ʾ����
{
	dula=0;
	P0=seg_table[bai_c];					//��ʾ��λ
	dula=1;
	dula=0;
	wela=0;
	P0=0x7e;
	wela=1;
	wela=0;
	delay_ad(10);

	dula=0;
	P0=seg_table[sh_c];						//��ʾʮλ
	dula=1;
	dula=0;
	wela=0;
	P0=0x7d;
	wela=1;
	wela=0;
	delay_ad(10);
		
	dula=0;
	P0=seg_table[g_c];						//��ʾ��λ
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
	    P0=0;                       //ѡͨADCS
	    adwr=0;					    //ADд�루���д��ʲô���У���Ҫ��Ϊ������ADת����
	    _nop_();
	    adwr=1;
	    P0=0xff;                    //�ر�ADCS
	
	    wela=0;                     //�ر���ADƬѡ�ź���������������Է�ֹ�ڲ��������ʱʹAD��Ƭѡ�����仯
	    for(a=30;a>0;a--)        //��Ҫע�����ADC0804��д�Ͷ�֮���ʱ����Ҫ�㹻�������޷���������
	    {                          //�������ʾ���ַ������ԭ��Ҳ��Ϊ������д��֮���ʱ����                                                                                                                                                                                                                           
	    	display(A1,A2,A3);
	    }	//��ȥ��ʾ��λ��
		wela=1;                    //���´���ADƬѡ�ź��������������
	    P1=0xff;                    //��ȡP1��֮ǰ�ȸ���дȫ1
	    P0=0;                       //ѡͨADCS
	    adrd=0;                     //AD��ʹ��
	    adval=P1;				  //AD���ݶ�ȡ����P1��
	    adrd=1;
	    P0=0xff;                     //�ر�ADCS
	    adwr=0;
	    P1=adval;                    //ͬʱ��AD��ֵ�Ͱ˸����������ʾ
	    A1=adval/100;		//�ֳ��٣�ʮ���͸�λ
	    A2t=adval%100;
	    A2=A2t/10;
	    A3=A2t%10;
	}
}

