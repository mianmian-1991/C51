sbit SDA = P2^0;
sbit SCL = P2^1;

// ��ʼ��
void initE2PROM()     // ˫˫���ߣ�׼������
{
    SDA = 1;    // ע�������� SDA��������ܼ�⵽ SDA �����ر� stop �ź�
    delay();
    SCL = 1;
    delay();
}

// �����ź�
void start()    // SDA �½��أ�SCL �ߵ�ƽ�ڼ䣩
{
    SDA = 1;
    delay();
    SCL = 1;    // ��ʼ׼��
    delay();
    SDA = 0;    // SDA �½���
    delay();     // SCL ���ûָ��͵�ƽ��
}

// ��ֹ�ź�
void stop()        // SDA �����أ�SCL �ߵ�ƽ�ڼ䣩
{
    SDA = 0;
    delay();
    SCL = 1;    // ��ʼ׼��
    delay();
    SDA = 1;    // SDA ������
    delay();
}

// �ȴ��ӻ�Ӧ��
void respons()        // ��� SDA ���ӻ����ͣ�SCL �ߵ�ƽ�ڼ䣩��ÿ��д�ֽ��Ժ�Ҫ��Ӧ����ȷ�Ͻ���
{
    uchar i;

    SCL = 1;    // ��ʼ׼��
    delay();
    while((SDA==1)&&(i++<250));        // ��ֹû�յ�Ӧ���趨�ʱ��
    SCL = 0;    // SCL �ָ��͵�ƽ
    delay();
}

// �����ֽ�
void write_byte(uchar byte2send)     // SCL �ߵ�ƽ�ڼ� SDA �ȶ�����
{
    uchar i;

    for(i=0;i<8;i++)    // һ���ֽڷ� 8 λ����
    {
        byte2send<<=1;        // һλλ�����λ���� CY
        SCL = 0;    // ������ʱ�ӣ����ݲ��ܱ仯
        delay();
        SDA = CY;   
        delay();
        SCL = 1;    // SCL �ߵ�ƽ�ͳ�����
        delay();
    }

    SCL = 0;    // SCL �ָ��͵�ƽ
    delay();
    SDA = 1;    // ��
    delay();
}

// �����ֽ�
uchar read_byte()    // SCL �ߵ�ƽ�ڼ� SDA �ȶ�����
{
    uchar i, recieve;

    SCL = 0;
    delay();
    SDA = 1;    // ��
    delay();

    for(i=0;i<8;i++)
    {
        SCL = 1;    // SCL �ߵ�ƽ�ڼ� SDA �ȶ�����
        delay();
        recieve = (recieve<<1) | SDA;    // ���λ���� SDA��Ȼ��һ��������
        SCL = 0;    // SCL �ָ��͵�ƽ
        delay();
    }

    return recieve;
}

void write(uchar address, uchar datas)
{
    start();     // �����ź�
    write_byte(0xa0);    // д-�����֣����� 1010��A2A1A0 = 000��RW = 0
    respons();
    write_byte(address);     // Ƭ�ڵ�ַ
    respons();
    write_byte(datas);     // д����
    respons();
    stop();     // ��ֹ�ź�
}

uchar read(uchar address)
{
    uchar datas;

    start();     // �����ź�
    write_byte(0xa0);    // д-�����֣����� 1010��A2A1A0 = 000��RW = 0
    respons();
    write_byte(address);     // Ƭ�ڵ�ַ
    respons();
    start();     // �����ź�
    write_byte(0xa1);    // ��-�����֣����� 1010��A2A1A0 = 000��RW = 1
    respons();
    datas = read_byte();     // ������
    stop();     // ��ֹ�ź�

    return datas;
}
