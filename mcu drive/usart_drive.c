#include "usart_drive.h"
#include "./GPIO_Init/GPIO_Init.h" 




/*配置串口*/
void usart_drive_init(gpio_drive_init* usart0_TX_init,gpio_drive_init* usart_init_gpio_RX,usartx_init* usartx_init_drive)
{
gpio_mode_init(usart0_TX_init);	
gpio_mode_init(usart_init_gpio_RX);		
usart_deinit(usartx_init_drive->usartx);	
usart_baudrate_set(usartx_init_drive->usartx,usartx_init_drive->botelv);
usart_word_length_set(usartx_init_drive->usartx,usartx_init_drive->shujuwei);
usart_stop_bit_set(usartx_init_drive->usartx,usartx_init_drive->stopwei);
usart_parity_config(usartx_init_drive->usartx,usartx_init_drive->jiouyanzheng);
usart_hardware_flow_rts_config(usartx_init_drive->usartx,usartx_init_drive->RTSshujuliu);	
usart_hardware_flow_cts_config(usartx_init_drive->usartx,usartx_init_drive->CTSshujuliu);	
usart_transmit_config(usartx_init_drive->usartx, usartx_init_drive->TRANSMIT_switch);
usart_receive_config(usartx_init_drive->usartx, usartx_init_drive->RECEIVE_switch);
usart_enable(usartx_init_drive->usartx);//使能USART0		
	
}


/*配置发送或者接收的中断*/
void usart_interrupt_SWITCH_drive_RX(uint32_t usartx,uint32_t SWITCH)
{
	if(SWITCH==ENABLE)
	{
	usart_interrupt_enable(usartx , USART_INT_RBNE);
	}
	else 
	{
		usart_interrupt_disable(usartx , USART_INT_RBNE);
	}
}

void usart_interrupt_SWITCH_drive_TX(uint32_t usartx,uint32_t SWITCH_OP)
{
	if(SWITCH_OP==ENABLE)
	{
	usart_interrupt_enable(usartx , USART_INT_TBE);
	}
	else 
	{
		usart_interrupt_disable(usartx , USART_INT_TBE);
	}
}



FlagStatus usartX_interrupt_flag_get(uint32_t usart_periph, uint32_t int_flag)
{

return usart_interrupt_flag_get(usart_periph,int_flag);	
}

FlagStatus usartX_flag_get(uint32_t usart_periph, usart_flag_enum int_flag)
{
	return usart_flag_get(usart_periph,int_flag);	
}





uint16_t usartX_data_receive(uint32_t usart_periph)
{
	return usart_data_receive(usart_periph);
}




