#include   "Can_Exchange.h"
#include   "Bq7695202_drive.h"
#include   "GPIO_Par_Inter.h"
#include   "string.h"



void CAN_Send_Analog_Data(void)
{
	CAN_SendCellVoltages();
	CAN_SendTemperatures();
	CAN_SendPackInfo();
	CAN_SendPackConfig();
	CAN_SendTempAlarms();
	CAN_SendCellAlarms();
	CAN_SendComprehensiveAlarms();
	CAN_SendControlFaultAlarms();
}



// 发送电池单体电压数据 (0x220-0x223)
void CAN_SendCellVoltages(void) {
    CanTxMsg TxMessage;
    uint32_t frame_id = 0x0220;
    uint8_t time_out = 0x0F; // 设置超时计数器
	  uint8_t i=0;
	  uint8_t TransmitMailbox =0;
   	uint8_t j=0;
	  uint8_t cell_idx=0;
    // 每个CAN帧发送4个电池电压，共需要发送 ceil(16/4)=4帧
    for (i = 0; i < 4; i++) {
        TxMessage.StdId = frame_id + i;
        TxMessage.ExtId = 0x00;
        TxMessage.IDE = CAN_ID_STD;
        TxMessage.RTR = CAN_RTR_DATA;
        TxMessage.DLC = 8;
        
        // 填充4个电池电压数据
        for (j = 0; j < 4; j++) {
            cell_idx = i * 4 + j;
            if (cell_idx < BatData.Cell_Number) {
                TxMessage.Data[j*2] = (uint8_t)((BatData.cell_voltages[cell_idx] >> 8)&0x00FF);   // 高字节
                TxMessage.Data[j*2+1] = (uint8_t)(BatData.cell_voltages[cell_idx] & 0x00FF); // 低字节
            } else {
                // 无数据填充0
                TxMessage.Data[j*2] = 0x00;
                TxMessage.Data[j*2+1] = 0x00;
            }
        }
        
        // 发送消息
				time_out=0XFF;
        TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
        while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
				{
					{
							if (time_out-- == 0) 
							{
									// 超时处理：报错、恢复CAN状态、或进入安全模式
									//Error_Handler(); 
									break;
							}
					}
				}
    }
}

// 发送温度数据 (0x224-0x225)
void CAN_SendTemperatures(void) {
    CanTxMsg TxMessage;
	  uint8_t i=0;
    uint32_t frame_id = 0x224;
    uint8_t j=0;
	  uint8_t timeout = 0xFF; // 设置超时计数器
	  uint8_t TransmitMailbox=0;
    // 每个CAN帧发送4个温度，共需要发送 ceil(8/4)=2帧
    for ( i = 0; i < 2; i++) {
        TxMessage.StdId = frame_id + i;
        TxMessage.ExtId = 0x00;
        TxMessage.IDE = CAN_ID_STD;
        TxMessage.RTR = CAN_RTR_DATA;
        TxMessage.DLC = 8;
        
        // 填充4个温度数据
        for (j = 0; j < 4; j++) {
         TxMessage.Data[j*2] = (uint8_t)((((uint16_t)(BatData.temperatures[i]*10+500)) >> 8)&0x00FF);   // 高字节
         TxMessage.Data[j*2+1] = (uint8_t)(((uint16_t)(BatData.temperatures[i]*10+500)) & 0x00FF); // 低字节  //偏移500
        }
        // 发送消息
				  timeout = 0xFF;
        TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
        while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
			  {
					{
							if (timeout-- == 0) 
							{
									// 超时处理：报错、恢复CAN状态、或进入安全模式
									//Error_Handler(); 
									break;
							}
					}
				}
    }
}

// 发送电池组信息 (0x226)
void CAN_SendPackInfo(void) {
    CanTxMsg TxMessage;
    uint8_t timeout = 0xFF; // 设置超时计数器
  	uint8_t TransmitMailbox=0;
	  uint8_t Current_Mode_A_Set=0;
    TxMessage.StdId = 0x226;
    TxMessage.ExtId = 0x00;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 8;
	  Current_Mode_A_Set=Current_Mode_Set;
    if(Current_Mode_A_Set==0)
		{
			TxMessage.Data[0] = (uint8_t)(((((BatData.pack_current)<<(Current_Mode_A_Set+1))+30000) >> 8)& 0x00FF);
			TxMessage.Data[1] = (uint8_t)((((BatData.pack_current)<<(Current_Mode_A_Set+1))+30000) & 0x00FF);
		}
		else if((Current_Mode_A_Set>=1)&&(Current_Mode_A_Set<=3))
		{
			TxMessage.Data[0] = (uint8_t)(((((BatData.pack_current)>>(Current_Mode_A_Set-1))+30000) >> 8)& 0x00FF);
      TxMessage.Data[1] = (uint8_t)((((BatData.pack_current)>>(Current_Mode_A_Set-1))+30000) & 0x00FF);
		}
		else
		{
		}
    
    // 总电压 (0.01V/bit)
    TxMessage.Data[2] = (uint8_t)(((BatData.pack_voltage/10) >> 8)& 0x00FF);
    TxMessage.Data[3] = (uint8_t)((BatData.pack_voltage/10) & 0x00FF);
    
    // 剩余容量 (0.01Ah/bit)
    TxMessage.Data[4] = (uint8_t)((BatData.remaining_capacity >> 8)&0x00FF);
    TxMessage.Data[5] = (uint8_t)((BatData.remaining_capacity  & 0xFF)&0x00FF);
    
    // 循环次数 (1cycle/bit)
    TxMessage.Data[6] = (uint8_t)((BatData.cycle_count >> 8)&0x00FF);
    TxMessage.Data[7] = (uint8_t)(BatData.cycle_count & 0x00FF);
      timeout = 0xFF;
    TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
    while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
			{
					{
							if (timeout-- == 0) 
							{
									// 超时处理：报错、恢复CAN状态、或进入安全模式
									//Error_Handler(); 
									break;
							}
					}
				}
}



// 发送电池组配置信息 (0x227)
void CAN_SendPackConfig(void) {
    CanTxMsg TxMessage;
    uint8_t timeout = 0xFF; // 设置超时计数器
	  uint8_t TransmitMailbox;
    TxMessage.StdId = 0x227;
    TxMessage.ExtId = 0x00;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 8;
    
    // 设计容量 (10mAh/bit)
    TxMessage.Data[0] = (uint8_t)(BatData.design_capacity >> 8);
    TxMessage.Data[1] = (uint8_t)(BatData.design_capacity & 0xFF);
    
    // 电池单体个数 (1串/bit)
    TxMessage.Data[2] = BatData.Cell_Number;
    
    // 命令和随机数
    TxMessage.Data[3] = BatData.Command;
    TxMessage.Data[4] = BatData.Ramdom_Number;
    
    // 保留字节
    TxMessage.Data[5] = 0x00;
    TxMessage.Data[6] = 0x00;
    TxMessage.Data[7] = 0x00;
      timeout = 0xFF;
    TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
    while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
			{
					{
							if (timeout-- == 0) 
							{
									// 超时处理：报错、恢复CAN状态、或进入安全模式
									//Error_Handler(); 
									break;
							}
					}
				}
}


/*      告警类信息发送    */


// 发送电池单体电压告警信息 (0x2n8-0x2n9)
void CAN_SendCellAlarms(void) {
    CanTxMsg TxMessage;
    uint32_t frame_id_base = 0x228; // 根据实际n值替换
    uint8_t timeout = 0xFF; // 设置超时计数器
  	uint8_t TransmitMailbox=0;
   	uint8_t i=0;
	  uint8_t j=0;
	  uint8_t cell_idx=0;
    // 每个CAN帧发送8个电池告警，共需要发送 ceil(16/8)=2帧
    for (i = 0; i < 2; i++) {
        TxMessage.StdId = frame_id_base + i;
        TxMessage.ExtId = 0x00;
        TxMessage.IDE = CAN_ID_STD;
        TxMessage.RTR = CAN_RTR_DATA;
        TxMessage.DLC = 8;
        
        // 填充8个电池告警数据
        for (j = 0; j < 8; j++) {
             cell_idx = i * 8 + j;
            if (cell_idx < AlarmData.Cell_Number) {
                TxMessage.Data[j] = AlarmData.cell_alarms[cell_idx];
            } else {
                // 无数据填充0
                TxMessage.Data[j] = 0x00;
            }
        }
          timeout = 0xFF;
        // 发送消息
        TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
        while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
				{
					{
							if (timeout-- == 0) 
							{
									// 超时处理：报错、恢复CAN状态、或进入安全模式
									//Error_Handler(); 
									break;
							}
					}
				}
			}
}

// 发送温度告警信息 (0x2nA)
void CAN_SendTempAlarms(void) {
    CanTxMsg TxMessage;
    uint8_t timeout = 0xFF; // 设置超时计数器
	  uint8_t i=0;	
	  uint8_t TransmitMailbox=0;
    TxMessage.StdId = 0x22A; // 根据实际n值替换
    TxMessage.ExtId = 0x00;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 8;
    
    // 填充8个温度告警数据
    for (i = 0; i < 8; i++) {
        if (i < AlarmData.Tempt_Number) {
            TxMessage.Data[i] = AlarmData.temp_alarms[i];
        } else {
            // 无数据填充0
            TxMessage.Data[i] = 0x00;
        }
    }
      timeout = 0xFF;
    TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
    while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
	 {
		{
				if (timeout-- == 0) 
				{
						// 超时处理：报错、恢复CAN状态、或进入安全模式
						//Error_Handler(); 
						break;
				}
		}
	 }
}

// 发送综合告警信息 (0x2nB)
void CAN_SendComprehensiveAlarms(void) {
	uint8_t timeout = 0xFF; // 设置超时计数器
	CanTxMsg TxMessage;
	uint8_t TransmitMailbox=0;
	TxMessage.StdId = 0x22B; // 根据实际n值替换
	TxMessage.ExtId = 0x00;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	
	// Byte1: 电池单体个数和温度检测个数
	TxMessage.Data[0] = AlarmData.Cell_Number;
	TxMessage.Data[1] = AlarmData.Tempt_Number;
	
	// Byte2: 电流和电压告警
	TxMessage.Data[2] = AlarmData.charge_current_alarm;
	TxMessage.Data[3] = AlarmData.pack_voltage_alarm;
	TxMessage.Data[4] = AlarmData.discharge_current_alarm;
	
	// Byte3: 保护状态1
	TxMessage.Data[5] = AlarmData.protection_status1;
	
	// Byte4: 保护状态2
	TxMessage.Data[6] = AlarmData.protection_status2;
	
	// Byte5: 指示状态
	TxMessage.Data[7] = AlarmData.indication_status;
		timeout = 0xFF;
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
	{
			{
					if (timeout-- == 0) 
					{
							// 超时处理：报错、恢复CAN状态、或进入安全模式
							//Error_Handler(); 
							break;
					}
			}
		}
 }

// 发送控制与故障告警信息 (0x2nC)
void CAN_SendControlFaultAlarms(void) {
	CanTxMsg TxMessage;
	uint8_t timeout = 0xFF; // 设置超时计数器
	uint8_t TransmitMailbox=0;

	TxMessage.StdId = 0x22C; // 根据实际n值替换a
	TxMessage.ExtId = 0x00;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	
	// Byte1: 控制状态
	TxMessage.Data[0] = AlarmData.control_status;
	
	// Byte2: 故障状态
	TxMessage.Data[1] = AlarmData.fault_status;
	
	// Byte3-4: 均衡状态(示例中未定义，填充0)
	TxMessage.Data[2] = 0x00;
	TxMessage.Data[3] = 0x00;
	
	// Byte5: 告警状态1
	TxMessage.Data[4] = AlarmData.alarm_status1;
	
	// Byte6: 告警状态2
	TxMessage.Data[5] = AlarmData.alarm_status2;
	
	// Byte7-8: 保留
	TxMessage.Data[6] = 0x00;
	TxMessage.Data[7] = 0x00;
	timeout = 0xFF;
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
	{
		{
				if (timeout-- == 0) 
				{
						// 超时处理：报错、恢复CAN状态、或进入安全模式
						//Error_Handler(); 
						break;
				}
		}
	}
}




void Can_Response_Command(void)
{
	CanRxMsg RxMessage; 
	CanTxMsg TxMessage;
	uint8_t  timeout=0;
	uint8_t TransmitMailbox=0;
	IC_Setting_Mode  Bq_Para_Set;
  memset(&RxMessage,0,sizeof(RxMessage));
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	if(RxMessage.StdId==Can_Bq_Ready_ID)
	{
		if(((*(volatile uint32_t*)RxMessage.Data)==Can_Bq_Ready_Data1&&\
			(*(volatile uint32_t*)(RxMessage.Data+4))==Can_Bq_Ready_Data2))
		{
			Bq_Para_Set=BQ_Stdio_Ready;
	
			/////////////////修改完成进行反馈/////
			if(BQ769x2_Init(Bq_Para_Set)==Task_OK)  //使用studio设定
			{
				TxMessage.StdId = Can_Bq_Ready_ID; // 根据实际n值替换a
				TxMessage.ExtId = 0x00;
				TxMessage.IDE = CAN_ID_STD;
				TxMessage.RTR = CAN_RTR_DATA;
				TxMessage.DLC = 8;
				(*(volatile uint32_t*)RxMessage.Data)=Can_Bq_Ready_Re_Data1;
				(*(volatile uint32_t*)(RxMessage.Data+4))=Can_Bq_Ready_Re_Data2;
				timeout = 0xFF;
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
				while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
				{
					{
						if (timeout-- == 0) 
						{
								// 超时处理：报错、恢复CAN状态、或进入安全模式
								//Error_Handler(); 
								break;
						}
					}
				}
			}
			else
			{
          goto error_exit;
			}
		}
	}
	if(RxMessage.StdId==Can_Bq_Set_Done_ID)   //使用studio设定完成
	{
		if(((*(volatile uint32_t*)RxMessage.Data)==Can_Bq_Set_Done_Data1&&\
			(*(volatile uint32_t*)(RxMessage.Data+4))==Can_Bq_Set_Done_Data2))
		{
			Bq_Para_Set=BQ_Stdio_Set_Done;
			if(BQ769x2_Init(Bq_Para_Set)==Task_OK)
			{
				TxMessage.StdId = Can_Bq_Set_Done_ID; // 根据实际n值替换a
				TxMessage.ExtId = 0x00;
				TxMessage.IDE = CAN_ID_STD;
				TxMessage.RTR = CAN_RTR_DATA;
				TxMessage.DLC = 8;
				(*(volatile uint32_t*)RxMessage.Data)=Can_Bq_Set_Done_Re_Data1;
				(*(volatile uint32_t*)(RxMessage.Data+4))=Can_Bq_Set_Done_Re_Data2;
				timeout = 0xFF;
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
				while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
				{
					{
						if (timeout-- == 0) 
						{
								// 超时处理：报错、恢复CAN状态、或进入安全模式
								//Error_Handler(); 
								break;
						}
					}
				}		
			}	
			else
			{
				goto error_exit;
			}	
		}
	}
	if(RxMessage.StdId==Can_FlashSet_ID)
	{
		if(((*(volatile uint32_t*)RxMessage.Data)==Can_FlashSet_Data1&&\
			(*(volatile uint32_t*)(RxMessage.Data+4))==Can_FlashSet_Data2))
		{
			if(BQ769x2_Init(Flash_Setting)==Task_OK)
			{		
				TxMessage.StdId = Can_FlashSet_ID; // 根据实际n值替换a
				TxMessage.ExtId = 0x00;
				TxMessage.IDE = CAN_ID_STD;
				TxMessage.RTR = CAN_RTR_DATA;
				TxMessage.DLC = 8;
				(*(volatile uint32_t*)RxMessage.Data)=Can_FlashSet_Re_Data1;
				(*(volatile uint32_t*)(RxMessage.Data+4))=Can_FlashSet_Re_Data2;
				timeout = 0xFF;
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
				while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
				{
					{
						if (timeout-- == 0) 
						{
								// 超时处理：报错、恢复CAN状态、或进入安全模式
								//Error_Handler(); 
								break;
						}
					}
				}
			}
			else
			{
				goto error_exit;
			}
		}
	}
	if(RxMessage.StdId==Can_InitSet_ID)
	{
		if(((*(volatile uint32_t*)RxMessage.Data)==Can_InitSet_Data1&&\
			(*(volatile uint32_t*)(RxMessage.Data+4))==Can_InitSet_Data2))
		{
			if(BQ769x2_Init(Init_Setting)==Task_OK)
			{		
				TxMessage.StdId = Can_InitSet_ID; // 根据实际n值替换a
				TxMessage.ExtId = 0x00;
				TxMessage.IDE = CAN_ID_STD;
				TxMessage.RTR = CAN_RTR_DATA;
				TxMessage.DLC = 8;
				(*(volatile uint32_t*)RxMessage.Data)=Can_InitSet_Re_Data1;
				(*(volatile uint32_t*)(RxMessage.Data+4))=Can_InitSet_Re_Data2;
				timeout = 0xFF;
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
				while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
				{
					{
						if (timeout-- == 0) 
						{
								// 超时处理：报错、恢复CAN状态、或进入安全模式
								//Error_Handler(); 
								break;
						}
					}
				}
			}
			else
			{
				goto error_exit;
			}
		}
	}
	error_exit:
	TxMessage.StdId = Can_Error_ID; // 根据实际n值替换a
	TxMessage.ExtId = 0x00;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	(*(volatile uint32_t*)RxMessage.Data)=Can_Bq_Error_Data1;
	(*(volatile uint32_t*)(RxMessage.Data+4))=Can_Bq_Error_Data2;
	timeout = 0xFF;
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
	{
		{
			if (timeout-- == 0) 
			{
					// 超时处理：报错、恢复CAN状态、或进入安全模式
					//Error_Handler(); 
					break;
			}
		}
	}
}


















