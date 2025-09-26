#ifndef _RELAY_SWITCH_FUZHI_H
#define _RELAY_SWITCH_FUZHI_H
#include "gd32f10x.h"


#define   on   1
#define   off  0

#define      relay1_gpio                GPIOA 
#define      relay1_pin                 GPIO_PIN_2

//sw1  PB6
#define      relaysw1_gpio                GPIOB 
#define      relaysw1_pin                 GPIO_PIN_6


//SW2 PB5
#define      relaysw2_gpio                GPIOB
#define      relaysw2_pin                 GPIO_PIN_5

	

void  relay1_switch_condition(uint8_t SET_condition);
void  relaysw1_switch_condition(uint8_t SET_condition);
void  relaysw2_switch_condition(uint8_t SET_condition);



#endif





