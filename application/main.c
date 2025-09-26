#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "./systick/systick.h"
#include "./chushihua/chushihua.h"  
#include "Memory_Par_Inter.h"
#include "Power_manage_Chip_Set.h"
#include "Schedule.h"
#include  "Can_Exchange.h"
#include  "RS485_exchange.h"
#include  "Timer_interface.h"
#include "ALarm_EXit_inter.h" 
#include "Usart_interface.h"
int main(void)
{   
	System_INIT();
	while(1)
	{
		EVE_dispatch();
	}	
}








