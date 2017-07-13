void init_Serial()
{
     TMOD = 0x20;     // T1 ��ʽ 2
     TH1 = 0xfd;     // ������9600 bps
     TL1 = 0xfd;
     TR1 = 1;     // ��ʼ��ʱ
     SM0 = 0;     // ���ڷ�ʽ 1
     SM1 = 1;
     REN = 1;     // �����ڽ���
     EA = 1;     // ���ж�����
     ES = 1;     // �����ж�����
}

void recieve_Serial() interrupt 4     // ���ڽ����жϺ���
{
     RI = 0;     // �ֶ�����жϱ�ʶλ RI
     content = SBUF;     // ��ȡ�ֽ�
}

void send_Serial(uchar *content)
{
     uint i = 0;
     ES = 0;     // �ش����жϣ���Ϊ������Ҳ������жϣ�����Ҫ����
     while(content[i]!='\0')     // ֱ���ַ�������
     {
          SBUF = content[i];     // ����һ���ֽ�
          while(TI==0);     // �ȵ� TI=1 ���ͽ���
          TI = 0;     // �ֶ�����жϱ�ʶλ TI
          i++;
     }
     ES = 1;
}
