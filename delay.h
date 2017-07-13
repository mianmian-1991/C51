void delayms (unsigned int xms)   // 延时约 xms 毫秒（针对 unsigned int）
{
     unsigned int i, j;
     for (i=xms; i>0; i--)
          for (j=110; j>0; j--);
}

void delay ()   // 延时 4-5 微秒，用于 I2C 总线
{ ; ; }
