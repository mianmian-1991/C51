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
        LCD_1602_RS = 0;        // ָ��ģʽ
    else
        LCD_1602_RS = 1;        // ����ģʽ
    LCD_1602_E = 0;
    P0 = com_data;        // �͵� P0 ��
    delay(5);
    LCD_1602_E = 1;        // ʹ�ܣ����� RAM
    delay(5);
    LCD_1602_E = 0;
}

void write_12864(uchar com_data, bit flag)
{
    if(flag== COMMAND)
        LCD_12864_RS = 0;        // ָ��ģʽ
    else
        LCD_12864_RS = 1;        // ����ģʽ
    LCD_12864_RW = 0;
    LCD_12864_E = 0;
    P0 = com_data;        // �͵� P0 ��
    delay(5);
    LCD_12864_E = 1;        // ʹ�ܣ����� RAM
    delay(5);
    LCD_12864_E = 0;
}

void draw_12864_GDRAM(uchar *image)
{
     uint y, yi, xi;
     write_12864(COMMAND, 0x34);     // ��չָ�����ʱ�ر� GDRAM ��ʾ

     // �ϰ�����y 0-31��x 0x80-0x87����ͬ�� DDRAM ǰ���У�
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi �� y ��ַ������32 �У�ÿ��ѭ��дһ��
     {
          write_12864(COMMAND, y+yi);     // y ��ַ��ÿ�μ� 1
          write_12864(COMMAND, 0x80);     // ÿдһ�� x ���Ǵ����� 0x80 ��ʼ��x ��ַ�����ֶ��� 1
          for(xi=0;xi<16;xi++)     // xi �� x ��ַ������������8 �У�ÿ�� 2 ���ֽڣ�ÿ��ѭ��дһ���ֽ�
          {
               write_12864(DATA, *image++);
          }
     }
     
     // �°�����y 0-31��x 0x88-0x8F����ͬ�� DDRAM ǰ���У�
     y = 0x80;
     for(yi=0;yi<32;yi++)     // yi �� y ��ַ������32 �У�ÿ��ѭ��дһ��
     {
          write_12864(COMMAND, y+yi);     // y ��ַ��ÿ�μ� 1
          write_12864(COMMAND, 0x88);     // ÿдһ�� x ���Ǵ����� 0x88 ��ʼ��x ��ַ�����ֶ��� 1
          for(xi=0;xi<16;xi++)     // xi �� x ��ַ������������8 �У�ÿ�� 2 ���ֽڣ�ÿ��ѭ��дһ���ֽ�
          {
               write_12864(DATA, *image++);
          }
     }

     write_12864(COMMAND, 0x36);     // �� GDRAM ��ʾ
     write_12864(COMMAND, 0x30);     // �ػ���ָ�
}

