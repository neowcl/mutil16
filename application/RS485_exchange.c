#include "RS485_exchange.h"
#include "Bq7695202_drive.h"
#include "Usart_interface.h"
#include "GPIO_Par_Inter.h"
#include "Schedule.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>  // 用于 strtol



/*
0:SOI    0                 0x7E
1,2:VER   1                0x25   32 35
3,4:ADR   2                0x02   30 32
5,6:46H  CID1   3          0x46   34 36   磷酸铁锂
7,8:42H,44H   4            0x42    compute  0x,0x
9,10,11,12:Length   5,6    Compute  0x45(E)，0x30(0)，0x30(0),0x32(2)
13,14:lenid(02)   7        02      30 32
15,16,17,18:checksum  8,9  Compute  0x，0x，0x,0x
19:eoi   10                OD      OD
*/

static uint8_t Receive_Data[11]={0x7E,0x25,0x02,0x46,0x00,0xE0,0x02,0x02,0x00,0x00,EOI};
//static uint8_t Receive_Data[21]={0x7E,  0x32,0x35   ,0x30,0x32,   0x34,0x36,  \
   0x00,0x00,  0x00,0x00,0x00,0x00,  0x30,0x32, 0x00,0x00,0x00,0x00,  EOI};

/**
  * @brief  模拟量信息返回
  * @param  BatteryData* data 存储的信息
	* @param  uint8_t* frame 用于发送的数据帧信息（转化为ASCII后）
	* @param  uint16_t* length   发送信息的长度
  * @retval 无
  */
void RS485_Response_Data(void)
{
	uint16_t Re_Len=0;
	uint8_t response_frame[256];
	//如果DMA没有释放   //则需要等2ms的延时  
	////RS485状态是否为繁忙
	Build_Analog_Response(&BatData,response_frame,&Re_Len);
	USART1_SendString(response_frame,Re_Len);
	if(tx_busy==1)
	{
		Task_Wait_Trigger(3,RS485_Response_Data_Task);
	}
	//如果DMA已经释放
	else 
	{
		if(Rx_Message_Size(&Re_Len)==1)
		{
			//进行处理接收数据
			process_rs485_command(U0CB_Rx.RxDataOut->Start,Re_Len,&BatData,&AlarmData);
			Start_Receive_Message(); //代表处理完毕
		}
  }
}	
	 
	
	 
	 
	 
	 
	 
	 void Build_Analog_Response(BatteryData* data, uint8_t* frame, uint16_t* length){
	  uint16_t lenid=0;
	  uint8_t  lchksum=0;
	  uint16_t i=0; 
		uint16_t pos=1;
		uint16_t chksum=0;   
	  uint8_t  Current_Mode_A_Set;
	 // SOI    //起始标志位
    frame[0] = SOI;                     // SOI    //起始标志位
		////软件版本//VER  
	  HexTransToAscii(frame+pos,PROTOCOL_VER,&pos);//VER    //软件版本
	  // ADR    //地址
    HexTransToAscii(frame+pos,slave_address,&pos);		
		// CID1   //磷酸铁锂电池
		HexTransToAscii(frame+pos,CID1_BATTERY,&pos);
		// RTN    //0x00
		HexTransToAscii(frame+pos,0x00,&pos);
    
    // LENGTH计算（LENID=4+16*2+8*2+2*6=64字节）
	   //加入INFOflag为00H，则为65字节//则为65*2=130
    lenid = 130;
    lchksum = Calculate_Lcheksum(lenid);
		HexTransToAscii(frame+pos,(uint8_t)((lchksum << 4) | ((lenid >> 8) & 0x0F)),&pos);
		HexTransToAscii(frame+pos,(uint8_t)(lenid & 0xFF),&pos);
    // DATAINFO构建
    
    HexTransToAscii(frame+pos,0x00,&pos);             // INFOFLAG
    HexTransToAscii(frame+pos,slave_address,&pos);    // Command
    HexTransToAscii(frame+pos,16,&pos);               // 电池单体个数,16串
    
    // 填充单体电压（大端序）//第19
    for (i = 0; i < 16; i++) 
		{
			HexTransToAscii(frame+pos,((data->cell_voltages[i] >> 8) & 0xFF),&pos);
			HexTransToAscii(frame+pos,(data->cell_voltages[i] & 0xFF),&pos);
    }   
    HexTransToAscii(frame+pos,8,&pos);  // 温度传感器个数
		
    // 填充温度数据
    for (i = 0; i < 8; i++) 
		{
			HexTransToAscii(frame+pos,(uint8_t)((((uint8_t)((data->temperatures[i])*10+2730)) >> 8) & 0xFF),&pos);
			HexTransToAscii(frame+pos,(uint8_t)(((uint8_t)(data->temperatures[i]*10+2730)) & 0xFF),&pos);
    }
    
    // 填充其他模拟量（大端序）
		// 填充电流数据
		Current_Mode_A_Set=Current_Mode_Set;
		if(Current_Mode_A_Set==0)
		{
			HexTransToAscii(frame+pos,(((data->pack_current)<<(Current_Mode_A_Set+1))>> 8) & 0xFF,&pos);
		  HexTransToAscii(frame+pos,((data->pack_current)<<(Current_Mode_A_Set-1)) & 0xFF,&pos);
		}
		else if((Current_Mode_A_Set>=1)&&(Current_Mode_A_Set<=3))
		{
			HexTransToAscii(frame+pos,(((data->pack_current)>>(Current_Mode_A_Set-1))>> 8) & 0xFF,&pos);
		  HexTransToAscii(frame+pos,((data->pack_current)>>(Current_Mode_A_Set-1)) & 0xFF,&pos);
		}
		else
		{
		}
		// 填充电压数据
		HexTransToAscii(frame+pos,(data->pack_voltage >> 8),&pos);
		HexTransToAscii(frame+pos,data->pack_voltage & 0xFF,&pos);

		// 填充剩余容量数据
		HexTransToAscii(frame+pos,(data->remaining_capacity >> 8) & 0xFF,&pos);
		HexTransToAscii(frame+pos,data->remaining_capacity & 0xFF,&pos);
		
		// 自定义数据个数
		HexTransToAscii(frame+pos,3,&pos);
		
			// 填充FCC数据
		HexTransToAscii(frame+pos,(data->full_capacity >> 8) & 0xFF,&pos);
		HexTransToAscii(frame+pos,data->full_capacity & 0xFF,&pos);
		
    //填充循环数据
		HexTransToAscii(frame+pos,(data->cycle_count >> 8) & 0xFF,&pos);
		HexTransToAscii(frame+pos,data->cycle_count & 0xFF,&pos);
	
		//填充设计容量数据（POS为最终执行后的值）
		HexTransToAscii(frame+pos,(data->design_capacity >> 8) & 0xFF,&pos);
		HexTransToAscii(frame+pos,data->design_capacity & 0xFF,&pos);
		
    // 计算CHKSUM（从SOI到倒数第三字节）
    chksum = Calculate_Chksum(frame, pos); //
		HexTransToAscii(frame+pos,(chksum >> 8) & 0xFF,&pos);
		HexTransToAscii(frame+pos,chksum & 0xFF,&pos);
    frame[pos-1] = EOI;             // EOI
    *length = pos;
}












/**
  * @brief  进行警告信息进行返回
  * @param  alarms：需要传送的信息
  * @param  frame：  打包成需要发送到数组
  * @param  length：需要的发送长度
  * @retval 无
  */

void build_alarm_response(PackAlarmData* alarms, uint8_t* frame, uint16_t* length)
	{
	  uint16_t lenid=0;
	  uint8_t  lchksum=0;
	  uint16_t i=0; 
		uint16_t pos=1;
		uint16_t chksum=0;
		uint8_t* info = NULL;
	  // SOI    //起始标志位
    frame[0] = SOI; 
	  HexTransToAscii(frame+pos,PROTOCOL_VER,&pos);//VER    //软件版本
    // ADR    //地址
    HexTransToAscii(frame+pos,slave_address,&pos);		
		// CID1   //磷酸铁锂电池
		HexTransToAscii(frame+pos,CID1_BATTERY,&pos);
		// RTN    //0x00
		HexTransToAscii(frame+pos,0x00,&pos);
    
    // LENGTH计算（LENID=（15+1）*2=32字节）
    lenid = 32;
    lchksum = Calculate_Lcheksum(lenid);
    HexTransToAscii(frame+pos,(uint8_t)((lchksum << 4) | ((lenid >> 8) & 0x0F)),&pos);
		HexTransToAscii(frame+pos,(uint8_t)(lenid & 0xFF),&pos);
    
    HexTransToAscii(frame+pos,0x00,&pos);             // INFOFLAG
    HexTransToAscii(frame+pos,slave_address,&pos);    // Command
		info=&(alarms->Cell_Number);  //指向alarms->Cell_Number
		for(i=0;i<14;i++)
		{
     HexTransToAscii(frame+pos,info[i],&pos);    // Command
		}
		 // 计算CHKSUM（从SOI到倒数第三字节）
    chksum = Calculate_Chksum(frame, pos);
		HexTransToAscii(frame+pos,(chksum >> 8) & 0xFF,&pos);
		HexTransToAscii(frame+pos,chksum & 0xFF,&pos);
    *length = pos+1;
}

/*
0:SOI    0                 0x7E   
1,2:VER   1                0x25   32 35
3,4:ADR   2                0x02   30 32
5,6:46H  CID1   3          0x46   34 36   磷酸铁锂
7,8:42H,44H   4            0x42    compute  0x,0x
9,10,11,12:Length   5,6    Compute  0x，0x，0x,0x
13,14:lenid(02)   7        02      30 32
15,16,17,18:checksum  8,9  Compute  0x，0x，0x,0x
19:eoi   10                OD      OD
*/

void process_rs485_command(uint8_t* received_frame, uint16_t rx_len, 
                          BatteryData* battery, PackAlarmData* alarms) {
		uint8_t data_T[2]={0,0};
		uint16_t pos=0;              //无用
		uint8_t i=0;		
    uint16_t chksum=0;	
    uint8_t response_frame[256];
    uint16_t response_len = 0;		
    // 1. 基础校验  //字节长度为20
    if (rx_len !=20 || received_frame[0] != SOI || received_frame[rx_len-1] != EOI) {
        return; // 无效帧
    }
		for(i=1;i<=3;i++)
		{
			HexTransToAscii(data_T,Receive_Data[i],&pos);
			if((data_T[0]!=received_frame[i*2-1])||(data_T[1]!=received_frame[i*2]))
			{
				return;   //错误帧
			}
			pos=0;
		}
		for(i=5;i<=6;i++)
		{
			HexTransToAscii(data_T,Receive_Data[i],&pos);
			if((data_T[0]!=received_frame[i*2-1])||(data_T[1]!=received_frame[i*2]))
			{
				return;   //错误帧
			}
			pos=0;
		}
		
		// 3. 校验CHKSUM
		chksum=Calculate_Chksum(received_frame,15);   //计算数据1-14
		HexTransToAscii(data_T,((uint8_t)((chksum >> 8)& 0x00FF)),&pos);
		if((received_frame[15]!=data_T[0])||(received_frame[16]!=data_T[1]))
			{
				return;   //校验CHKSUM错误
			}
		HexTransToAscii(data_T,((uint8_t)(chksum & 0x00FF)),&pos);
		if((received_frame[17]!=data_T[0])||(received_frame[18]!=data_T[1]))
			{
				return;   //校验CHKSUM错误
			}

    // 4. 解析命令类型
		HexTransToAscii(data_T,CID1_BATTERY,&pos);
		if((received_frame[5]!=data_T[0])||(received_frame[6]!=data_T[1]))
		{
			return;   //校验CID1错误
		}	
    // 5. 根据CID2生成响应
    
		HexTransToAscii(data_T,CID2_Analog,&pos);
    if((data_T[0]==received_frame[7])\
			   &&(data_T[1]==received_frame[8]))
    {
			Build_Analog_Response(battery, response_frame, &response_len);
		}
		HexTransToAscii(data_T,CID2_Alarm,&pos);
    if((data_T[0]==received_frame[7])\
			   &&(data_T[1]==received_frame[8]))
	  {
			build_alarm_response(alarms, response_frame, &response_len);;
	  }
    // 6. 发送响应（需实现硬件层发送函数）
    if (response_len > 0) 
	  {
			//进行发送数据
     USART1_SendString(response_frame,strlen((const char *)response_frame));
    }
}

uint8_t Calculate_Lcheksum(uint16_t lenid) 
{
	uint8_t sum=0;
  sum = ((lenid >> 9) & 0x07) +  // D11-D9
           ((lenid >> 4) & 0x0F) +   // D7-D4
            (lenid & 0x0F);           // D3-D0
    return (~(sum % 16) + 1) & 0x0F;
}

uint16_t Calculate_Chksum(uint8_t* data, uint16_t length) 
{
    uint32_t sum = 0;
	  uint16_t i=0;
    for ( i = 1; i < length; i++) {
        sum += data[i];
    }
    return (~(sum % 65536) + 1) & 0xFFFF;
}

// 将 4-bit 的 hex 值转换为 ASCII 字符
char hexToAscii(uint8_t hex) {
    hex &= 0x0F;  // 确保只处理低 4 位
    if (hex <= 9) {
        return hex + '0';      // 0x0-0x9 -> '0'-'9'
    } else if (hex >= 0xA && hex <= 0xF) {
        return hex - 0xA + 'A'; // 0xA-0xF -> 'A'-'F'
    } else {
        return '?';            // 无效值返回 '?'
    }
}

void HexTransToAscii(uint8_t* frame_adrre,uint8_t hex,uint16_t* pos_t) 
	{
		 uint8_t c1,c2=0;
		// 处理 1 字节（2 个 nibble）
		 uint8_t nibble1 = (hex >> 4) & 0x0F;  // 高 4 位
		 uint8_t nibble2 = hex & 0x0F;         // 低 4 位
		 c1 = hexToAscii(nibble1);
		 c2 = hexToAscii(nibble2);
		 *frame_adrre=c1;
		 *(frame_adrre+1)=c2;
		 *pos_t=*pos_t+2;
  }

char hexToAsciiChar(unsigned char hexValue) {
    // 处理数字 0-9
    if (hexValue >= 0x30 && hexValue <= 0x39) {
        return hexValue;  // 0x30-0x39 直接对应 '0'-'9'
    }
    // 处理大写字母 A-F
    else if (hexValue >= 0x41 && hexValue <= 0x46) {
        return hexValue;  // 0x41-0x46 直接对应 'A'-'F'
    }
    // 如果不是有效的十六进制ASCII字符，返回 '\0'（空字符）
    else {
        return '\0';
    } 
	}


//// 将16进制字符串转换为ASCII字符
//char hexStringToAsciiChar(const char* hexStr) {
//    unsigned char hexValue = (unsigned char)strtol(hexStr, NULL, 16);
//    return hexToAsciiChar(hexValue);
//}


//// 合并两个ASCII字符为一个16进制数
//unsigned char mergeAsciiToHex(char c1, char c2) {
//    unsigned char highNibble, lowNibble;

//    // 转换第一个字符为高4位
//    if (c1 >= '0' && c1 <= '9') {
//        highNibble = (c1 - '0') << 4;
//    } else if (c1 >= 'A' && c1 <= 'F') {
//        highNibble = (c1 - 'A' + 0xA) << 4;
//    } 
//		else 
//	 {
//        highNibble = 0;  // 无效字符默认为0
//    }

//    // 转换第二个字符为低4位
//    if (c2 >= '0' && c2 <= '9') {
//        lowNibble = c2 - '0';
//    } else if (c2 >= 'A' && c2 <= 'F') {
//        lowNibble = c2 - 'A' + 0xA;
//    } 
//		else
//		{
//        lowNibble = 0;  // 无效字符默认为0
//    }

//    return highNibble | lowNibble;
//}


//unsigned char processTwoHexValues(unsigned char hex1, unsigned char hex2) {
//    // 转换为ASCII字符
//	  unsigned char mergedHex=0;
//	  char ascii1 =0;
//	  char ascii2 =0;
//    ascii1 = hexToAsciiChar(hex1);
//    ascii2 = hexToAsciiChar(hex2);
//    // 合并为16进制数
//    mergedHex = mergeAsciiToHex(ascii1, ascii2);
//    return mergedHex;
//    // 输出结果
//}


//// 合并两个ASCII字符为一个16进制数
//unsigned char mergeAsciiToHex(char c1, char c2) {
//    unsigned char highNibble, lowNibble;

//    // 转换第一个字符为高4位
//    if (c1 >= '0' && c1 <= '9') {
//        highNibble = (c1 - '0') << 4;
//    } else if (c1 >= 'A' && c1 <= 'F') {
//        highNibble = (c1 - 'A' + 0xA) << 4;
//    }else {
//        highNibble = 0;  // 无效字符默认为0
//    }

//    // 转换第二个字符为低4位
//    if (c2 >= '0' && c2 <= '9') {
//        lowNibble = c2 - '0';
//    } else if (c2 >= 'A' && c2 <= 'F') {
//        lowNibble = c2 - 'A' + 0xA;
//    }  else {
//        lowNibble = 0;  // 无效字符默认为0
//    }

//    return highNibble | lowNibble;
//}
