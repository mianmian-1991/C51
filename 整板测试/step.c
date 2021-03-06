/*此程序是针对uPD6121系列遥控器的取码程序，解码值在Im[2]中，当IrOK=1时解码有效*/
/******************************************************************************/
/* 项目名称  : TX-1C扩展板 红外遥控器控制步进电机                             */
/* 主控芯片  : STC89C52                                                       */
/* 文件名称  : Inf_StepMotor                                                  */
/* 文件功能  : 主函数                                                         */
/* 文件版权  : 北京海克智动科技开发有限公司                                   */
/* 文件版本  :                                                                */
/******************************************************************************/
/**********************************包含头文件**********************************/
#include <config.h>
/********************************定义变量和数组********************************/
uchar Im[4] = {0x00,0x00,0x00,0x00};
uchar f, IrOK;
uint Tc;
uchar code step_table1[] = {0x01,0x02,0x04,0x08,0x08,0x04,0x02,0x01};//电机4拍拍数
uchar step_table2[] = {0x00};
uchar maichong = 0,table_begin = 0;       //maichong步进电机速度档4为最慢 1为最快
                                          //table_begin是table1数组开始位置
                                          //table_begin=0正转 table_begin=4反转
                                          //table1[0]-[3]为正转拍数
                                          //table1[4]-[7]为反转拍数
uchar Start_Flag = 0;                     //启动标志 0为停止 1为启动
/******************************************************************************/
/* 函数名称  : delay                                                          */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
void step_delay(uchar i)
{
    uchar j,k; 
    for(j = i;j > 0;j--)
    {
        for(k = 125;k > 0;k--);
    }  
}
/******************************************************************************/
/* 函数名称  : display                                                        */
/* 函数描述  : 显示函数函数                                                   */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
void step_display()
{ 
    dula = 0;
    if(maichong == 0)                    //开机maichong=0 显示0
    {   
	    P0=seg_table[0];
	    dula = 1;
	    dula = 0;
	    
	    P0 = 0xfd;
	    wela = 1;
	    wela = 0;
	    step_delay(5);
    }
    else                     	             //遥控器调整档位后maichong不为0
    {     
	    P0 = seg_table[5 - maichong];        //显示档位maichong=1 对应4档 
	    dula = 1;
	    dula = 0;
	   
        wela = 0;
	    P0 = 0xfd;
	    wela = 1;
	    wela = 0;
	    step_delay(10);

		P0 = step_table2[0];                  //反转时显示"-"
	    dula = 1;
		dula = 0;

	    wela = 0;
	    P0 = 0xfe;
	    wela = 1;
	    wela = 0;
	    step_delay(10);
    }
}
/******************************************************************************/
/* 函数名称  : Motor_Driver                                                   */
/* 函数描述  : 电机驱动函数                                                   */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
void Motor_Driver(void)
{
    uchar i,j;
    for(j= 0 + table_begin;j < 4 + table_begin;j++)  
    {
        P1 = (step_table1[j]&0x0f)|(P1&0xf0);
        for(i = 0;i < maichong;i++)
	    {
           step_display();
	    }
    }
}
/******************************************************************************/
/* 函数名称  : Inf_Dispose                                                    */
/* 函数描述  : 红外接收处理函数                                               */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */ 
/* 返回值    : 无                                                             */
/******************************************************************************/
void Inf_Dispose(void)
{
    if(IrOK == 1) 
    { 
        switch(Im[2])   
        {
            case 0x0c:                      //遥控器1键按下 调为1档
                maichong = 4;
            break;

            case 0x18:                      //遥控器2键按下 调为2档
                maichong = 3;
            break;

            case 0x5e:                      //遥控器3键按下 调为3档
                maichong = 2;
            break;

            case 0x08:                      //遥控器4键按下 调为4档
                maichong = 1;
            break;

            case 0x44:                      //遥控器 开始/停止 键按下 启动停止控制
                Start_Flag =~  Start_Flag;
            break;

            case 0x43:                      //遥控器 |<< 键按下 正转
                if( maichong != 0)          //不是0档的时候设置正反转
                {
                    table_begin = 0;
                    step_table2[0] = 0;          //数码管不显示 
                }     
            break;

            case 0x40:                      //遥控器 >>| 键按下 反转
  
                if( maichong != 0)          //不是0档的时候设置正反转
                {
                    table_begin = 4;
                    step_table2[0] = 0x40;       //"-"码      
                }  
            break;

            default:
            break;
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
void step_main(void)
{ 
	system_init();
	step_m = 0;
	relay = 0;
    f = 0;
	EA = 1;
	IT1 = 1;
	ES = 1;
    EX1 = 1;
	TMOD=0x21;  
	TH0 = 0;
    TL0 = 0;
	TR0 = 1;
	diola = 1;
	while(message=='b')
	{
	    Inf_Dispose();            //红外接收处理
        if(Start_Flag)            //如果允许电机启动 
        {
            Motor_Driver();       //电机驱动
        }
        else                      //如果不允许电机启动
        {
            P1 &= 0xf0;            //不给电机输出脉冲
            step_display();       //显示
        }  
    }
}
/******************************************************************************/
