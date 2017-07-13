void init_Serial()
{
     TMOD = 0x20;     // T1 方式 2
     TH1 = 0xfd;     // 波特率9600 bps
     TL1 = 0xfd;
     TR1 = 1;     // 开始计时
     SM0 = 0;     // 串口方式 1
     SM1 = 1;
     REN = 1;     // 允许串口接收
     EA = 1;     // 总中断允许
     ES = 1;     // 串口中断允许
}

void recieve_Serial() interrupt 4     // 串口接收中断函数
{
     RI = 0;     // 手动清除中断标识位 RI
     content = SBUF;     // 读取字节
}

void send_Serial(uchar *content)
{
     uint i = 0;
     ES = 0;     // 关串口中断，因为发送完也会进入中断，我们要避免
     while(content[i]!='\0')     // 直到字符串结束
     {
          SBUF = content[i];     // 发送一个字节
          while(TI==0);     // 等到 TI=1 发送结束
          TI = 0;     // 手动清除中断标识位 TI
          i++;
     }
     ES = 1;
}
