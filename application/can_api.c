#include  "can_api.h"
#include "can_interface.h"
#include "relay_switch_fuzhi.h"
#include  "res_ADJ_MCP41010.h"
extern FlagStatus BSC_Data_Req;
extern uint8_t  RMS1_Rally[4];   //记录发送来的指令
extern uint8_t code_res;
extern VolAdj_Relay_Mode relay_mode;
can_trans_message   can0_MSG1;




/*
void can0_transmit_MSG1(void)    // 0X0001XA01
{
	if(BSC_Data_Req==RESET)
	{
can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &can0_MSG1);
can0_MSG1.tx_dlen=MSG1_Stren;
can0_MSG1.tx_ff=CAN_FF_EXTENDED;             //是扩展帧
can0_MSG1.tx_ft=CAN_FT_DATA;
		
if(RMS1_Rally[2]==0xFF)  //不为初态
{
	can0_MSG1.tx_data[1]|=Relay_Off;  //不为初态
}
else if(RMS1_Rally[2]==0x00)
{
can0_MSG1.tx_data[1]|=Relay_On;  //不为初态
}
if(????????)                    /////需要一个标志位   来代表通道稳定.
{
	can0_MSG1.tx_data[1]|=Chanel_Stable;  //通道稳定
}
else(????????)
{
can0_MSG1.tx_data[1]|=Chanel_Instable;  //通道不稳
}
		

////measure_dianya   被处理后,十进制范围是1500-4500.
can0_MSG1.tx_data[2]=(uint8_t)(measure_dianya&(0x00FF));
can0_MSG1.tx_data[3]=(uint8_t)((measure_dianya&(0xFF00)>>8);
////measure_dianliu   被处理后,十进制范围是0000-2000ma
can0_MSG1.tx_data[4]=(uint8_t)(measure_dianliu&(0x00FF));
can0_MSG1.tx_data[5]=(uint8_t)((measure_dianliu&(0xFF00)>>8);
//电位器数值进行写入传送
can0_MSG1.tx_data[6]=(uint8_t)(code_res);
can0_MSG1.tx_data[7]=(uint8_t)(relay_mode);
can_message_transmit_m_d(F103_To_F105,&can0_MSG1);
	}
}

*/





/*
对于MSG1的信息进行处理,主要应用于it.c的程序中
*/
 uint8_t  RMS1_Rally[4];
void RMS1_Deal_It(can_receive_MSG_struct  *RMS1_data)   //0x0000x110处理
{
	uint16_t num_shun=0;
	uint16_t temp1=0;
	float temp2=0.0;
	for(num_shun=0;num_shun<=7;num_shun++)
			{
				switch(num_shun)
				{
				case(0):
				{
					if(	RMS1_data->rx_data[0]==ID_Chanel)
					{
					break;
					}
					else
					{
						return;
					}

				}
				case(1):
				{
					if(RMS1_data->rx_data[1]==0xFF)  //继电器控制位有效
					{
						       ///////写入函数1,有关于继电器控制
	        RMS1_data->rx_data[2]=RMS1_Rally[0];
						if(RMS1_data->rx_data[1]==0xFF)
						{
						relay1_switch_condition(on);
						}
						else if(RMS1_data->rx_data[1]==0x00)
						{
						relay1_switch_condition(off);

						}
					}
          break; 
				}
					case(3):  //进行第三个字节识别
				{
					if(RMS1_data->rx_data[3]==0xFF)  //电压控制位有效
					{
				 RMS1_data->rx_data[4]=RMS1_Rally[1];
         RMS1_data->rx_data[5]=RMS1_Rally[2];
         temp1=(RMS1_data->rx_data[5]<<8)|(RMS1_data->rx_data[4]);//电压的值
						//数值是十六进制,转化为10进制时范围应当是1500-4500  0x05DC----1194
				 temp2=	(float)(temp1/1000.0);   
				 RES_ADJ(temp2);//写入函数,电压调节函数					     	
					}
          break; 
				}
				
				case(6):  //进行第6个字节识别
				{
					if(RMS1_data->rx_data[6]==0xFF)  //电压控制位有效
					{
				 RMS1_data->rx_data[7]=RMS1_Rally[3];
					             //主要通过函数3  对cs1234进行模式选择的定义
					}
          break; 
				}
			}
			}
	
}

FlagStatus   BSC_Data_Req;
uint8_t  RMS1_Rally[4];
void  RMS2_Deal_It(can_receive_MSG_struct  *RMS2_data)   //0x00000011
{
	uint16_t temp1=0;
	uint16_t num_shun=0;
		float temp2=0.0;
	for(num_shun=0;num_shun<=4;num_shun++)
			{
				switch(num_shun)
				{
				case(0):
				{
					if(	RMS2_data->rx_data[0]==ID_Chanel)
							break;
					else
						return;
				}
				
				case(1):   ////进行电压全局控制
				{
				if(	RMS2_data->rx_data[1]==0xFF)
				{
					RMS2_data->rx_data[2]=RMS1_Rally[1];
         RMS2_data->rx_data[3]=RMS1_Rally[2];
         temp1=(RMS2_data->rx_data[3]<<8)|(RMS2_data->rx_data[2]);//电压的值
						//数值是十六进制,转化为10进制时范围应当是1500-4500  0x05DC----1194
				 temp2=	(float)(temp1/1000.0);   
				 RES_ADJ(temp2);//写入函数,电压调节函数		
				}
          break; 
			  }
				
				case(3):
				{
				  if(	RMS2_data->rx_data[3]==0xFF)
				 {
					 if(RMS2_data->rx_data[4]==0xFF)
					 {
						BSC_Data_Req=SET; ///写入上传BSC模块信息的函数
					 }
					else if(RMS2_data->rx_data[4]==0x00)
					{
						BSC_Data_Req=RESET; ///写入上传BSC模块信息的函数
					}
					break;
						
				 }
			 }
		
			}
 		}
}








FlagStatus   BSC_Data_Req;
void  RMS3_Deal_It(can_receive_MSG_struct  *RMS3_data)   //0x0000x110处理
{
	uint16_t num_shun=0;
	for(num_shun=0;num_shun<=1;num_shun++)
			{
				switch(num_shun)
				{
				case(0):
				{
					if(	RMS3_data->rx_data[0]==ID_Chanel)
							break;
					else
						return;
				}
				
				case(1):
				{
				if(	RMS3_data->rx_data[1]==0xFF)
					BSC_Data_Req=SET;
					//设置一个开关能够保证是否需要发送
			  else if(RMS3_data->rx_data[1]==0x00)
					BSC_Data_Req=RESET;
          break; 
			}
		
			}
 		}
}










