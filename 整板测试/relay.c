/*此程序是针对uPD6121系列遥控器的取码程序，解码值在Im[2]中，当IrOK=1时解码有效*/
/******************************************************************************/
/* 项目名称  : TX-1C扩展板 红外遥控器控制继电器                               */
/* 主控芯片  : STC89C52                                                       */
/* 文件名称  : Inf_Relay                                                      */
/* 文件功能  : 主函数                                                         */
/* 文件版权  : 北京海克智动科技开发有限公司                                   */
/* 文件版本  :                                                                */
/******************************************************************************/
/**********************************包含头文件**********************************/
#include <config.h>
/********************************定义变量和数组********************************/
unsigned long relay_m,relay_Tc;
/******************************************************************************/
/* 函数名称  : Inf_Dispose                                                    */
/* 函数描述  : 红外接收处理函数                                               */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
void relay_Inf_Dispose(void)
{
    if(IrOK == 1) 
    { 
        if(Im[2] == 0x44)     //遥控器OK键按下 控制继电器开关
        {
            relay =~ relay;
        }
        IrOK = 0;	   
	}
}
/******************************************************************************/
/* 函数名称  : main                                                           */
/* 函数描述  : 主函数                                                         */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
void relay_main(void)
{ 
	system_init();
	EA = 1;
	IT1 = 1;
    EX1 = 1;
	TMOD=0x21;  
	TH0 = 0;
    TL0 = 0;
	TR0 = 1;
    relay = 0;
	while(message=='e')
	{
	    relay_Inf_Dispose();            //红外接收处理
    }
}
/******************************************************************************/