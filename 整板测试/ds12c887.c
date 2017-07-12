/******************************************************************************/
/* 项目名称  : TX-1C扩展板 DS12C887实时时钟                                   */
/* 主控芯片  : STC89C52                                                       */
/* 文件名称  : RTC_DS12C887                                                   */
/* 文件功能  : DS12C887实时时钟操作                                           */
/* 文件版权  : 北京海克智动科技开发有限公司                                   */
/* 文件版本  :                                                                */
/******************************************************************************/
/**********************************包含头文件**********************************/
#include <config.h>
bit ds12887_flag1,ds12887_flag_ri;//定义两个位变量
uchar ds12887_count,s1num,ds12887_flag,t0_num;//其它变量定义
char miao,shi,fen,year,month,day,week,amiao,afen,ashi;
uchar code ds12887_table[]=" 20  -  -      ";//液晶固定显示内容
uchar code ds12887_table1[]="      :  :  ";
void write_ds(uchar,uchar);//函数申明
void set_alarm(uchar,uchar,uchar);void read_alarm();
uchar read_ds(uchar);void set_time();

void ds12887_delay(uint z)//延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
} 
void ds12887_init()									//初始化函数
{
	uchar num;
	EA=1;											//打开总中断
	EX1=1;											//开外部中断1
	IT1=1;											//设置负跳变沿触发中断
	ds12887_flag1=0;								//变量初始化
	t0_num=0;
	s1num=0;
	week=1;
	lcden=0;
	rd=0;
	write_ds(0x0A,0x20);							//打开振荡器
	write_ds(0x0B,0x26);							//设置24小时模式，数据二进制格式
	set_time();										//设置上电默认时间
	lcd_write_com(0x38);							//1602液晶初始化
	delay_1602(20);
	lcd_write_com(0x0c);
	delay_1602(20);
	lcd_write_com(0x06);
	delay_1602(20);
	lcd_write_com(0x01);
	delay_1602(20);
	lcd_write_com(0x80);
	delay_1602(20);
	for(num=0;num<15;num++)							//写入液晶固定部分显示
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
void write_sfm(uchar add,char date)					//1602液晶刷新时分秒函数4为时，7为分，10为秒
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	lcd_write_com(0x80+0x40+add);
	lcd_write_date(0x30+shi);
	lcd_write_date(0x30+ge);
}
void write_nyr(uchar add,char date)					//1602液晶刷新年月日函数3为年，6为分，9为秒
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	lcd_write_com(0x80+add);
	lcd_write_date(0x30+shi);
	lcd_write_date(0x30+ge);
}
void write_week(char we)							//写液晶星期显示函数
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
void write_ds(uchar add,uchar date)					//写12C887函数
{
	dscs=0;
	dsas=1;
	dsds=1;
	dsrw=1;
	P0=add;											//先写地址
	dsas=0;
	dsrw=0;
	P0=date;										//再写数据
	dsrw=1;
	dsas=1;
	dscs=1;				
}

uchar read_ds(uchar add) 							//读12C887函数
{
 	uchar ds_date;
	dsas=1;
	dsds=1;
	dsrw=1;
	dscs=0;
	P0=add;											//先写地址
	dsas=0;
	dsds=0;
	P0=0xff;
	ds_date=P0;										//再读数据
	dsds=1;
	dsas=1;
	dscs=1;
	return ds_date;	
}
/*---首次操作12C887时给予寄存器初始化---*/
void set_time()										//首次上电初始化时间函数
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
void ds12c887_main()//主函数
{
	system_init();
	ds12887_init();//调用初始化函数
	while(message=='a')
	{
		year=read_ds(9);//读取12C887数据
		month=read_ds(8);									  
		day=read_ds(7);
		week=read_ds(6);
		shi=read_ds(4);				 
		fen=read_ds(2);
		miao=read_ds(0);	
		write_sfm(10,miao);//送液晶显示
		write_sfm(7,fen);
		write_sfm(4,shi);
		//write_week(week);
		write_nyr(2,year);
		write_nyr(5,month);
		write_nyr(8,day);
	}
}
/*void exter() interrupt 2//外部中断1服务程序
{	
	uchar c; //进入中断表示闹钟时间到，
	ds12887_flag_ri=1; //设置标志位，用以大程序中报警提示
	c=read_ds(0x0c);//读取12C887的C寄存器表示响应了中断
} */



