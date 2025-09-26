#include "./led/led.h"
#include "relay_switch_fuzhi.h"
#include "./led_fuzhi/led_peizhi.h"
#include "./key_fuzhi/key_fuzhi.h"
#include "./TIMER_interface/TIMER_interface.h"
#include "./gd32f10x_it/gd32f10x_it.h"
#include "./systick/systick.h"



extern uint8_t IntFlag;  //按键的标志


extern uint32_t Timcounter;     //定时器标志 决定多久亮一次
extern uint8_t  LedFlag;        //用于是时间的翻转

void LED_shanshuo(void)
{
	LED2_WORK_TIME(100,0);
	LED3_WORK_TIME(100,0);
	
key1_interrupt_on();	
timer_1ms_enable();
while(1)
    {
	
      if(key1_input_bit_get()==RESET && IntFlag==0x00)//读取PA1引脚电平如果是低电平，而且外部中断已经进入
				{
				delay_1ms(100);
			  if(key1_input_bit_get()==RESET && IntFlag==0x00)
				{
					
					
					while(key1_input_bit_get()==RESET)
					{
					}
					relay1_switch_condition(1);
					LED1_WORK_TIME(0,100);
					
				}
				}
				if(key1_input_bit_get()==RESET && IntFlag==0x01)//读取PA1引脚电平如果是低电平，而且外部中断已经进入
				{
					delay_1ms(100);
			  if(key1_input_bit_get()==RESET && IntFlag==0x01)
				{
					while(key1_input_bit_get()==RESET)
					{
					}
					relay1_switch_condition(0);
					LED1_WORK_TIME(100,0);
				}
				}		
				}			

}



















