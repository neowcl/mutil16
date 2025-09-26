#ifndef  _CAN_API_H
#define  _CAN_API_H
#include "gd32f10x.h"

#include "can_drive.h"




void  RMS1_Deal_It(can_receive_MSG_struct  *RMS1_data);    //0x0000x111处
void  RMS2_Deal_It(can_receive_MSG_struct  *RMS2_data);    //0x0000x111处
void  RMS3_Deal_It(can_receive_MSG_struct  *RMS3_data);   //0x0000x110处理




#endif






