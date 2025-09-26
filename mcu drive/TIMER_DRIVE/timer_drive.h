#ifndef _TIMER_DRIVE_H
#define _TIMER_DRIVE_H
#include "stm32f10x.h"


void timer_init_drive(uint32_t timerx,timer_parameter_struct* timer_drive,uint32_t interrupt_switch);
void timer_drive_enable(uint32_t timerx);
void timer_drive_disable(uint32_t timerx);
void  timer_drive_flag_clear(uint32_t timerx,uint32_t interrupt_switch);
void rcu_drive_TIMER_periph_clock_enable(rcu_periph_enum RCC_timerx);
void timer_drive_denit(uint32_t timer_periph);




#endif /*TIMER_DRIVE_H*/
