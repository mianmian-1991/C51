sbit SDA = P2^0;
sbit SCL = P2^1;

// 初始化
void initE2PROM()     // 双双拉高，准备启动
{
    SDA = 1;    // 注意先拉高 SDA，否则可能检测到 SDA 上升沿变 stop 信号
    delay();
    SCL = 1;
    delay();
}

// 启动信号
void start()    // SDA 下降沿（SCL 高电平期间）
{
    SDA = 1;
    delay();
    SCL = 1;    // 初始准备
    delay();
    SDA = 0;    // SDA 下降沿
    delay();     // SCL 不用恢复低电平？
}

// 终止信号
void stop()        // SDA 上升沿（SCL 高电平期间）
{
    SDA = 0;
    delay();
    SCL = 1;    // 初始准备
    delay();
    SDA = 1;    // SDA 上升沿
    delay();
}

// 等待从机应答
void respons()        // 检测 SDA 被从机拉低（SCL 高电平期间），每次写字节以后都要等应答以确认接收
{
    uchar i;

    SCL = 1;    // 初始准备
    delay();
    while((SDA==1)&&(i++<250));        // 防止没收到应答，设定最长时限
    SCL = 0;    // SCL 恢复低电平
    delay();
}

// 发送字节
void write_byte(uchar byte2send)     // SCL 高电平期间 SDA 稳定不变
{
    uchar i;

    for(i=0;i<8;i++)    // 一个字节分 8 位发送
    {
        byte2send<<=1;        // 一位位将最高位送至 CY
        SCL = 0;    // 先拉低时钟，数据才能变化
        delay();
        SDA = CY;   
        delay();
        SCL = 1;    // SCL 高电平送出数据
        delay();
    }

    SCL = 0;    // SCL 恢复低电平
    delay();
    SDA = 1;    // ？
    delay();
}

// 接收字节
uchar read_byte()    // SCL 高电平期间 SDA 稳定不变
{
    uchar i, recieve;

    SCL = 0;
    delay();
    SDA = 1;    // ？
    delay();

    for(i=0;i<8;i++)
    {
        SCL = 1;    // SCL 高电平期间 SDA 稳定不变
        delay();
        recieve = (recieve<<1) | SDA;    // 最低位接收 SDA，然后一步步左移
        SCL = 0;    // SCL 恢复低电平
        delay();
    }

    return recieve;
}

void write(uchar address, uchar datas)
{
    start();     // 启动信号
    write_byte(0xa0);    // 写-控制字，器件 1010，A2A1A0 = 000，RW = 0
    respons();
    write_byte(address);     // 片内地址
    respons();
    write_byte(datas);     // 写数据
    respons();
    stop();     // 终止信号
}

uchar read(uchar address)
{
    uchar datas;

    start();     // 启动信号
    write_byte(0xa0);    // 写-控制字，器件 1010，A2A1A0 = 000，RW = 0
    respons();
    write_byte(address);     // 片内地址
    respons();
    start();     // 启动信号
    write_byte(0xa1);    // 读-控制字，器件 1010，A2A1A0 = 000，RW = 1
    respons();
    datas = read_byte();     // 读数据
    stop();     // 终止信号

    return datas;
}
