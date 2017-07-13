#define COMMAND 1
#define DATA 0

sbit LCD_1602_E = P3^4;
sbit LCD_1602_RS = P3^5;

sbit LCD_12864_E = P3^4;
sbit LCD_12864_RS = P3^5;
sbit LCD_12864_RW = P3^6;
sbit LCD_12864_PSB = P3^7;

void write_1602(uchar com_data, bit flag)
{
    if(flag== COMMAND)
        LCD_1602_RS = 0;        // 指令模式
    else
        LCD_1602_RS = 1;        // 数据模式
    LCD_1602_E = 0;
    P0 = com_data;        // 送到 P0 口
    delay(5);
    LCD_1602_E = 1;        // 使能，送入 RAM
    delay(5);
    LCD_1602_E = 0;
}

void write_12864(uchar com_data, bit flag)
{
    if(flag== COMMAND)
        LCD_12864_RS = 0;        // 指令模式
    else
        LCD_12864_RS = 1;        // 数据模式
    LCD_12864_RW = 0;
    LCD_12864_E = 0;
    P0 = com_data;        // 送到 P0 口
    delay(5);
    LCD_12864_E = 1;        // 使能，送入 RAM
    delay(5);
    LCD_12864_E = 0;
}

void draw_12864_GDRAM(uchar *image)
{
     uint y, yi, xi;
     write_12864(COMMAND, 0x34);     // 扩展指令集，暂时关闭 GDRAM 显示

     // 上半屏：y 0-31，x 0x80-0x87（等同于 DDRAM 前两行）
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi 是 y 地址增量，32 行，每个循环写一行
     {
          write_12864(COMMAND, y+yi);     // y 地址，每次加 1
          write_12864(COMMAND, 0x80);     // 每写一行 x 总是从行首 0x80 开始，x 地址不用手动加 1
          for(xi=0;xi<16;xi++)     // xi 是 x 地址增量的两倍，8 列，每列 2 个字节，每个循环写一个字节
          {
               write_12864(DATA, *image++);
          }
     }
     
     // 下半屏：y 0-31，x 0x88-0x8F（等同于 DDRAM 前两行）
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi 是 y 地址增量，32 行，每个循环写一行
     {
          write_12864(COMMAND, y+yi);     // y 地址，每次加 1
          write_12864(COMMAND, 0x88);     // 每写一行 x 总是从行首 0x88 开始，x 地址不用手动加 1
          for(xi=0;xi<16;xi++)     // xi 是 x 地址增量的两倍，8 列，每列 2 个字节，每个循环写一个字节
          {
               write_12864(DATA, *image++);
          }
     }

     write_12864(COMMAND, 0x36);     // 打开 GDRAM 显示
     write_12864(COMMAND, 0x30);     // 回基本指令集
}

