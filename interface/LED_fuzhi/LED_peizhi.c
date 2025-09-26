#include "./LED_fuzhi/LED_peizhi.h"    //µ×²ãÇý¶¯ÔÚLED_drive
#include "./gpio_init/gpio_init.h"



void LED1_WORK_TIME(uint32_t ONTIME,uint32_t OFFTIME)
{	
GPIO_WORK_TIME(ONTIME,OFFTIME,LED1_GPIO,LED1__PIN);
}










