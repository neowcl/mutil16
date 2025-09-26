#ifndef  _LED_PEIZHI_H
#define  _LED_PEIZHI_H
#include "stm32f10x.h"    //可以使用unint32 的数据类型




#define LED1_GPIO            GPIOB    
#define LED1__PIN      GPIO_Pin_7



void LED1_WORK_TIME(uint32_t ONTIME,uint32_t OFFTIME);







#endif /* LED_PEIZHI_H*/




