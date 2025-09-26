#ifndef  _CAN_INTERFACE_H
#define  _CAN_INTERFACE_H

#include "stm32f10x.h"
#include   "interrupt.h"


	
#define           can0_EXTI_IRQ                CAN0_RX1_IRQn            
#define           can0_nvic_pre_priority       0U       
#define           can0_nvic_sub_priority       0U      


void CAN_Config(void);

//void JiLian_DuanXian_mode_choose(EventStatus Status,uint32_t Passage_Type);





#endif







