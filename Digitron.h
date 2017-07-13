// 段选 U1
uchar code DigitronTable[] =
{
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71
};

// 位选 U2
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
    while(temp!=0)     // 求位数
    {
         n++;
         temp/=10;
    }

    temp = num;
    i = n-1;
    while(temp!=0)     // 取各位，wei[0] 最高位
    {
         wei[i] = temp % 10;     // 取当前个位
         i--;
         temp/=10;     // 去掉最后一位
    }

    for(i=0;i<n;i++)     // 显示各位，最左边数码管最高位
    {
        Duanxuan = 1;
        P0 = DigitronTable[wei[i]];     // 段码
        Duanxuan = 0;
        P0 = 0xff;     // 消影
        Weixuan = 1;
        P0 = WeiTable[i];     // 位码
        Weixuan = 0;
        delay(3);
    }
}
