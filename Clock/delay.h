void delayms (unsigned int xms)   // ��ʱԼ xms ���루��� unsigned int��
{
     unsigned int i, j;
     for (i=xms; i>0; i--)
          for (j=110; j>0; j--);
}

void delay ()   // ��ʱ 4-5 ΢�룬���� I2C ����
{ ; ; }
