#include "./timer_drive/timer_drive.h" 


void timer_init_drive(TIM_TypeDef* timerx,TIM_TimeBaseInitTypeDef* timer_drive,uint32_t interrupt_switch)
{
//timer_init(timerx,timer_drive);	
 // 初始化定时器
TIM_TimeBaseInit(timerx, timer_drive); 
	
timer_interrupt_enable(timerx,interrupt_switch);	
	
timer_auto_reload_shadow_enable(timerx);  //会导致中断没办法停下来
	
timer_disable(timerx);	
	
}


void timer_drive_enable(uint32_t timerx)
{
timer_enable(timerx);
}

void timer_drive_disable(uint32_t timerx)
{
timer_disable(timerx);
}




void  timer_drive_flag_clear(uint32_t timerx,uint32_t interrupt_switch)
{
	timer_flag_clear(timerx,interrupt_switch);
}


//时钟的启动
void rcu_drive_TIMER_periph_clock_enable(rcu_periph_enum RCC_timerx)    //注意枚举结构体的使用方法
{
	    rcu_periph_clock_enable(RCC_timerx); 
}


//timerX的复位作用，关于复位作用的几个方针，第一个时钟操作，存在复位不能启动外设。
void timer_drive_denit(uint32_t timer_periph)
{
	
	timer_deinit(timer_periph);
}






