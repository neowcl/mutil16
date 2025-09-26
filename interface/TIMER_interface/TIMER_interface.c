#include "./TIMER_interface/TIMER_interface.h"
#include "./timer_drive/timer_drive.h"
#include "./interrupt/interrupt.h" 


static timer_parameter_struct     timer_1ms={0,0,0,0,0,0};
static priority_SET_struct        timer_1ms_priority={0,0,0};
/*1ms的时钟变化*/
void   timer_1ms_init(void)
{
	
	//计时器的参数配置
timer_1ms.alignedmode=timer_1ms_alignedmode;
timer_1ms.clockdivision=timer_1ms_clockdivision;
timer_1ms.counterdirection=timer_1ms_counterdirection;
timer_1ms.period=timer_1ms_period;
timer_1ms.prescaler=timer_1ms_prescaler;
timer_1ms.repetitioncounter=timer_1ms_repetitioncounter;
	
//计时器的中断优先级进行配置
timer_1ms_priority.EXTI_IRQ=timer_1ms_EXTI_IRQ;
timer_1ms_priority.nvic_pre_priority=timer_1ms_nvic_pre_priority;
timer_1ms_priority.nvic_sub_priority=timer_1ms_nvic_sub_priority;
rcu_drive_TIMER_periph_clock_enable(RCC_timer_1ms_timerx);	
timer_drive_denit(timer_1ms_timerX);	
priority_SET(&timer_1ms_priority);
timer_init_drive(timer_1ms_timerX,&timer_1ms,timer_1ms_interrupt_switch);
	
}

void timer_1ms_enable(void)
{
timer_drive_enable(timer_1ms_timerX);
}

void timer_1ms_disable(void)
{
timer_drive_disable(timer_1ms_timerX);
}


void timer_timer_1ms_flag_clear(void)
{
	timer_drive_flag_clear(timer_1ms_timerX,timer_1ms_interrupt_switch);
	
}

