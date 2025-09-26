#ifndef _INTERRUPT_H
#define _INTERRUPT_H
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#define exti_interrupt_flag_clear_mcu_drive( EXTI_linex)  exti_flag_clear( EXTI_linex)

//中断相关的结构体配置
/*
@brief   主要是对中断的进行配置，包括触发引脚，触发源，触发模式等
*/
typedef struct
{     
 uint8_t                     GPIOX_SOURCE;
 uint32_t                    PIN_SOURCE;              //主要是GOIP的终端驱动
 EXTI_InitTypeDef*            Exit_Set; 
}GPIO_exti_init_struct;
























///*
//对中断源进行配置中断优先级
//*/
//typedef struct
//{  
// uint8_t              EXTI_IRQ;                //主要是看相应的中断源
// uint8_t	            nvic_pre_priority;     //主优先级
// uint8_t              nvic_sub_priority;    //子优先级	
//}priority_SET_struct;


void interrupt_init(GPIO_exti_init_struct* 	GPIO_EXTI,NVIC_InitTypeDef* fenzu);
//void priority_SET(priority_SET_struct* 	function_fenzu );
void interrupt_on(uint32_t 	PIN_SOURCE);
void nvic_priority_group_set_drive(uint32_t NVIC_GROUP);
#endif /*INTERRUPT_H*/










