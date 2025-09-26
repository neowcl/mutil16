#ifndef    CAN_EXCHANE_H
#define    CAN_EXCHANE_H

#include   "stm32f10x.h"


#define   Can_Bq_Ready_ID          0x120                //使用BQ76952设置
#define   Can_Bq_Ready_Data1     0x11223344
#define   Can_Bq_Ready_Data2     0x55667788


#define   Can_Bq_Ready_Re_Data1  0x44332211
#define   Can_Bq_Ready_Re_Data2  0x88776655




#define   Can_Bq_Set_Done_ID          0x123               //使用BQ76952设置
#define   Can_Bq_Set_Done_Data1       0x66778899
#define   Can_Bq_Set_Done_Data2       0xAABBCCDD


#define   Can_Bq_Set_Done_Re_Data1    0x99887766
#define   Can_Bq_Set_Done_Re_Data2    0xDDCCBBAA


#define   Can_InitSet_ID           0x121               //使用BQ76952初始设定
#define   Can_InitSet_Data1      0x8899AABB
#define   Can_InitSet_Data2      0xCCDDEEFF

#define   Can_InitSet_Re_Data1      0xBBAA9988
#define   Can_InitSet_Re_Data2      0xFFEEDDCC



#define   Can_FlashSet_ID          0x122               //使用flash设置
#define   Can_FlashSet_Data1     0x44556677
#define   Can_FlashSet_Data2     0x8899AABB

#define   Can_FlashSet_Re_Data1  0x77665544
#define   Can_FlashSet_Re_Data2  0xBBAA9988






#define   Can_Error_ID           0x12F                 //错误设定
#define   Can_Bq_Error_Data1    0x00FF00FF
#define   Can_Bq_Error_Data2    0x00FF00FF


void CAN_Send_Analog_Data(void);
void CAN_SendControlFaultAlarms(void);
void CAN_SendComprehensiveAlarms(void); 
void CAN_SendTempAlarms(void);
void CAN_SendCellAlarms(void);
void CAN_SendPackConfig(void);
void CAN_SendPackInfo(void);
void CAN_SendCellVoltages(void);
void CAN_SendTemperatures(void) ;
void Can_Response_Command(void);



#endif




