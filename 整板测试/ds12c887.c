/******************************************************************************/
/* ��Ŀ����  : TX-1C��չ�� DS12C887ʵʱʱ��                                   */
/* ����оƬ  : STC89C52                                                       */
/* �ļ�����  : RTC_DS12C887                                                   */
/* �ļ�����  : DS12C887ʵʱʱ�Ӳ���                                           */
/* �ļ���Ȩ  : ���������Ƕ��Ƽ��������޹�˾                                   */
/* �ļ��汾  :                                                                */
/******************************************************************************/
/**********************************����ͷ�ļ�**********************************/
#include <config.h>
bit ds12887_flag1,ds12887_flag_ri;//��������λ����
uchar ds12887_count,s1num,ds12887_flag,t0_num;//������������
char miao,shi,fen,year,month,day,week,amiao,afen,ashi;
uchar code ds12887_table[]=" 20  -  -      ";//Һ���̶���ʾ����
uchar code ds12887_table1[]="      :  :  ";
void write_ds(uchar,uchar);//��������
void set_alarm(uchar,uchar,uchar);void read_alarm();
uchar read_ds(uchar);void set_time();

void ds12887_delay(uint z)//��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
} 
void ds12887_init()									//��ʼ������
{
	uchar num;
	EA=1;											//�����ж�
	EX1=1;											//���ⲿ�ж�1
	IT1=1;											//���ø������ش����ж�
	ds12887_flag1=0;								//������ʼ��
	t0_num=0;
	s1num=0;
	week=1;
	lcden=0;
	rd=0;
	write_ds(0x0A,0x20);							//������
	write_ds(0x0B,0x26);							//����24Сʱģʽ�����ݶ����Ƹ�ʽ
	set_time();										//�����ϵ�Ĭ��ʱ��
	lcd_write_com(0x38);							//1602Һ����ʼ��
	delay_1602(20);
	lcd_write_com(0x0c);
	delay_1602(20);
	lcd_write_com(0x06);
	delay_1602(20);
	lcd_write_com(0x01);
	delay_1602(20);
	lcd_write_com(0x80);
	delay_1602(20);
	for(num=0;num<15;num++)							//д��Һ���̶�������ʾ
	{
		lcd_write_date(ds12887_table[num]);
		//delay_1602(100);
		ds12887_delay(10);
	}
	lcd_write_com(0x80+0x40);
	for(num=0;num<11;num++)
	{
		lcd_write_date(ds12887_table1[num]);
		//delay_1602(100);
		ds12887_delay(10);
	}
}
void write_sfm(uchar add,char date)					//1602Һ��ˢ��ʱ���뺯��4Ϊʱ��7Ϊ�֣�10Ϊ��
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	lcd_write_com(0x80+0x40+add);
	lcd_write_date(0x30+shi);
	lcd_write_date(0x30+ge);
}
void write_nyr(uchar add,char date)					//1602Һ��ˢ�������պ���3Ϊ�꣬6Ϊ�֣�9Ϊ��
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	lcd_write_com(0x80+add);
	lcd_write_date(0x30+shi);
	lcd_write_date(0x30+ge);
}
void write_week(char we)							//дҺ��������ʾ����
{
	lcd_write_com(0x80+12);
	switch(we)
	{
		case 1:	lcd_write_date('M');ds12887_delay(5);
				lcd_write_date('O');ds12887_delay(5);
				lcd_write_date('N');
				break;
		case 2:	lcd_write_date('T');ds12887_delay(5);
				lcd_write_date('U');ds12887_delay(5);
				lcd_write_date('E');
				break;
		case 3:	lcd_write_date('W');ds12887_delay(5);
				lcd_write_date('E');ds12887_delay(5);
				lcd_write_date('D');
				break;
		case 4:	lcd_write_date('T');ds12887_delay(5);
				lcd_write_date('H');ds12887_delay(5);
				lcd_write_date('U');
				break;
		case 5:	lcd_write_date('F');ds12887_delay(5);
				lcd_write_date('R');ds12887_delay(5);
				lcd_write_date('I');
				break;
		case 6:	lcd_write_date('S');ds12887_delay(5);
				lcd_write_date('A');ds12887_delay(5);
				lcd_write_date('T');
				break;
		case 7:	lcd_write_date('S');ds12887_delay(5);
				lcd_write_date('U');ds12887_delay(5);
				lcd_write_date('N');
				break;
	}
}
void write_ds(uchar add,uchar date)					//д12C887����
{
	dscs=0;
	dsas=1;
	dsds=1;
	dsrw=1;
	P0=add;											//��д��ַ
	dsas=0;
	dsrw=0;
	P0=date;										//��д����
	dsrw=1;
	dsas=1;
	dscs=1;				
}

uchar read_ds(uchar add) 							//��12C887����
{
 	uchar ds_date;
	dsas=1;
	dsds=1;
	dsrw=1;
	dscs=0;
	P0=add;											//��д��ַ
	dsas=0;
	dsds=0;
	P0=0xff;
	ds_date=P0;										//�ٶ�����
	dsds=1;
	dsas=1;
	dscs=1;
	return ds_date;	
}
/*---�״β���12C887ʱ����Ĵ�����ʼ��---*/
void set_time()										//�״��ϵ��ʼ��ʱ�亯��
{
	write_ds(0,0);
	write_ds(1,0);
	write_ds(2,0);
	write_ds(3,0);
	write_ds(4,0);
	write_ds(5,0);
	write_ds(6,0);
	write_ds(7,0);
	write_ds(8,0);
	write_ds(9,0);	
}
void ds12c887_main()//������
{
	system_init();
	ds12887_init();//���ó�ʼ������
	while(message=='a')
	{
		year=read_ds(9);//��ȡ12C887����
		month=read_ds(8);									  
		day=read_ds(7);
		week=read_ds(6);
		shi=read_ds(4);				 
		fen=read_ds(2);
		miao=read_ds(0);	
		write_sfm(10,miao);//��Һ����ʾ
		write_sfm(7,fen);
		write_sfm(4,shi);
		//write_week(week);
		write_nyr(2,year);
		write_nyr(5,month);
		write_nyr(8,day);
	}
}
/*void exter() interrupt 2//�ⲿ�ж�1�������
{	
	uchar c; //�����жϱ�ʾ����ʱ�䵽��
	ds12887_flag_ri=1; //���ñ�־λ�����Դ�����б�����ʾ
	c=read_ds(0x0c);//��ȡ12C887��C�Ĵ�����ʾ��Ӧ���ж�
} */



