#include "./interrupt/interrupt.h" 


/**
  * @brief set the NVIC 
   	@param \
  * @param   
  *   
  * @retval 
  */
void interrupt_init(GPIO_exti_init_struct* 	GPIO_EXTI,NVIC_InitTypeDef* fenzu)
{
	GPIO_EXTILineConfig(GPIO_EXTI->GPIOX_SOURCE,GPIO_EXTI->PIN_SOURCE);
	NVIC_Init(fenzu);	
	EXTI_Init(GPIO_EXTI->Exit_Set);    //exti open or not
}


/*
@brief 抢占优先级，优先级分组
*/

//void priority_SET(priority_SET_struct* 	function_fenzu )
//{	
//nvic_irq_enable(function_fenzu->EXTI_IRQ, function_fenzu->nvic_pre_priority, function_fenzu->nvic_sub_priority);
//	//enable and set key EXTI interrupt to the lowest priority 
//}

void interrupt_on(uint32_t 	PIN_SOURCE)
{
	(*(volatile uint32_t *)(uint32_t)(EXTI_BASE+ 0x04U))|= (uint32_t)PIN_SOURCE;   //open the interrupt
	EXTI_ClearFlag(PIN_SOURCE);
//exti_software_interrupt_enable(GPIO_EXTI->EXTI_XIAN);
}


//void   nvic_priority_group_set_drive(uint32_t NVIC_GROUP)
//{
//nvic_priority_group_set(NVIC_GROUP);
//}







