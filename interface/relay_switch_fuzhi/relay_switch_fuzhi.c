#include "relay_switch_fuzhi.h"
#include "gpio_init.h"



void  relay1_switch_condition(uint8_t SET_condition)
{
	switch(SET_condition)
	{
		case(0):
		  gpio_bit_reset_drive(relay1_gpio,relay1_pin);
	   	break;
		case(1):
			gpio_bit_set_drive(relay1_gpio,relay1_pin);
			break;
		default:
			break;
	}
}

void  relaysw1_switch_condition(uint8_t SET_condition)
{
	switch(SET_condition)
	{
		case(0):
		  gpio_bit_reset_drive(relaysw1_gpio,relaysw1_pin);
	   	break;
		case(1):
			gpio_bit_set_drive(relaysw1_gpio,relaysw1_pin);
			break;
		default:
			break;
	}
}

void  relaysw2_switch_condition(uint8_t SET_condition)
{
	switch(SET_condition)
	{
		case(0):
		  gpio_bit_reset_drive(relaysw2_gpio,relaysw2_pin);
	   	break;
		case(1):
			gpio_bit_set_drive(relaysw2_gpio,relaysw2_pin);
			break;
		default:
			break;
	}
}

















