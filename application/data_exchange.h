#ifndef    DATA_EXCHANGE_H
#define    DATA_EXCHANGE_H

#include   "stm32f10x.h"


//{
//	uint16_t		VCell[16];      //用于记录对应的电压值//uint16_t Stack_Voltage = 0x00;
//	uint16_t    Stack_Voltage;
//	uint16_t    Pack_Voltage;
//	uint16_t    LD_Voltage;
//	uint16_t    Total_Voltage;
//	uint16_t    Pack_Current;
//  float       Temperature [10];                  //记录由SH367数组40H 的温度数据计算后值,或许可以记录其他的值
//	uint32_t		E2ulFCC;                 ///可能是总容量    ,,//也有可能是充电冲的电量                 
//	uint32_t		RC;                     //采集::::安时积分 然后乘以百分比获取的容量  ,此时的容量    ,,,,,单位是毫安时,可能单位会不会不对
//	uint16_t		RSOC;            //此时电池的容量     0   10  20  30来记录   
////	uint16_t		E2uiCycleCount;
////	uint16_t		PackStatus;                  //系统状态
////	uint16_t		BatStatus;
////	uint16_t		PackConfig;
////	uint16_t		ManufactureAccess;
//}PACK_SYSINFOR_Str;





extern BatteryData    BatData;
extern PackAlarmData  AlarmData;

#endif










