#ifndef  POWER_MANANGE_CHIP_SET_H
#define  POWER_MANANGE_CHIP_SET_H
#include "stm32f10x.h"













void InitGasGauge(void);
void BatteryInfoManage(void);                   
void CalcuTemperature(void);
void CalcuVoltage(void);
void CalcuVolMaxMin(void);
void GaugeManage(void);








#endif












