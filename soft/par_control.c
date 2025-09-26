#include "par_control.h"
#include "can_api.h"
#include "relay_switch_fuzhi.h"
#include "res_ADJ_MCP41010.h"    //注意名字应当去更改

extern uint8_t  RMS1_Rally[4];   //记录发送来的指令
//0: 继电器控制
//1.2:电压控制
//3  :数据上传速率


void con_self_init(void)
{
	  uint16_t temp1=0;
  	float temp2=0.0;
		if(RMS1_Rally[0]==0xFF)
		{
				relay1_switch_condition(on);
		}
		else if(RMS1_Rally[0]==0x00)
		{
		relay1_switch_condition(off);
		}
		

     temp1=((RMS1_Rally[2]<<8)&0xFF00)|(RMS1_Rally[1]);//电压的值
		//数值是十六进制,转化为10进制时范围应当是1500-4500  0x05DC----1194
	   temp2=	(float)(temp1/1000.0);   
		 RES_ADJ(temp2);//写入函数,电压调节函数	

////////////////////////还缺一段,就是上传速率或者采集的速率.

		
	   
}





