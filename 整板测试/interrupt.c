#include <config.h>
/******************************************************************************/
/* 函数名称  : Time0_Int                                                      */
/* 函数描述  : 定时器0中断函数                                                */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
unsigned long step_m;
void Time0_Int() interrupt 1        //中断程序
{
	//P1 &= ~(1<<7);
	if(message=='c')
	{
		TH0  = 0xfe;                    //重新赋值
		TL0  = 0x33;
	    dc_count++;
	    if(dc_count == PulseWidth)         //对应的脉宽值输出低电平                
	    {
	        dc_motor = 0;
	    }
	    if(dc_count == 60)//30ms周期到达后
	    {
	        dc_motor = 1;           //输出高电平
	        dc_count = 0;
	    }
	}
	else if(message=='d')
	{
		TH0  = 0xfe;                    //重新赋值
		TL0  = 0x33;
	    
	    helm_count++;
	    if(helm_count == helm_jd)                 //对应的角度输出低电平                
	    {
	        helm_motor = 0;
	    }
	
	    if(helm_count == 40)                 //20ms周期到达后
	    {
	        helm_motor = 1;                    //输出高电平
	        helm_count = 0;
	    }     
	} 
}
/******************************************************************************/
/* 函数名称  : intersvr1                                                      */
/* 函数描述  : 外部中断解码程序                                               */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
void intersvr1(void) interrupt 2 
{
	Tc = TH0 * 256 + TL0;                      //提取中断时间间隔时长
	TH0 = 0; 
    TL0 = 0;                                   //定时中断重新置零

	if((Tc > Imin) && (Tc < Imax))
    { 
		step_m = 0;
        f = 1;
		return;
    }                                          //找到启始码

    if(f == 1)
    {
        if(Tc > Inum1 && Tc < Inum3) 
	  	{
			Im[step_m / 8] = Im[step_m / 8] >> 1 | 0x80;
            step_m++; 
     	}
    	if(Tc > Inum2 && Tc < Inum1) 
        {
        	Im[step_m / 8] = Im[step_m / 8] >> 1; 
            step_m++;                              //取码
		}
		if(step_m == 32) 
	 	{
            step_m = 0;  
            f = 0;
       	    if(Im[2] ==~ Im[3]) 
	        {
                IrOK =1 ; 
		    }
            else 
            {
                IrOK = 0;   //取码完成后判断读码是否正确
            }
	    }
	}	
}