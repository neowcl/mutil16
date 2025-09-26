#ifndef   RS485_EXCHANGE_H
#define   RS485_EXCHANGE_H

#include   "stm32f10x.h"
#include   "Bq7695202_drive.h"


// 协议常量定义
#define SOI             0x7E
#define EOI             0x0D
#define CID1_BATTERY    0x46
#define PROTOCOL_VER    0x25

#define  CID2_Analog    0x42
#define  CID2_Alarm     0x44




// 从机地址配置（实际应用中通过拨码开关获取）
static uint8_t slave_address = 2; // 地址范围2-15

void Build_Analog_Response(BatteryData* data, uint8_t* frame, uint16_t* length);


uint8_t Calculate_Lcheksum(uint16_t lenid);

uint16_t Calculate_Chksum(uint8_t* data, uint16_t length);

void HexTransToAscii(uint8_t* frame_adrre,uint8_t hex,uint16_t* pos_t);

void build_alarm_response(PackAlarmData* alarms, uint8_t* frame, uint16_t* length);

unsigned char processTwoHexValues(unsigned char hex1, unsigned char hex2);

void process_rs485_command(uint8_t* received_frame, uint16_t rx_len, BatteryData* battery, PackAlarmData* alarms);

void RS485_Response_Data(void);
#endif





