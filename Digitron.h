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

void display(uint num)
{
    uint temp = num;
    uchar i,n;
    uchar wei[6];

    n = 0;
    while(temp!=0)     // ��λ��
    {
         n++;
         temp/=10;
    }

    temp = num;
    i = n-1;
    while(temp!=0)     // ȡ��λ��wei[0] ���λ
    {
         wei[i] = temp % 10;     // ȡ��ǰ��λ
         i--;
         temp/=10;     // ȥ�����һλ
    }

    for(i=0;i<n;i++)     // ��ʾ��λ���������������λ
    {
        Duanxuan = 1;
        P0 = DigitronTable[wei[i]];     // ����
        Duanxuan = 0;
        P0 = 0xff;     // ��Ӱ
        Weixuan = 1;
        P0 = WeiTable[i];     // λ��
        Weixuan = 0;
        delay(3);
    }
}
