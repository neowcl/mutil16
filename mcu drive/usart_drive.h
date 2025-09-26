#ifndef  USART_DRIVE_H
#define  USART_DRIVE_H
#include "stm32f10x.h"
#include "GPIO_Init.h"
//#include  "stdio.h"

#define usart_data_transmit_drive              usart_data_transmit

typedef struct
{      
	  uint32_t           usartx;      
	  uint32_t           botelv;
	  uint32_t           shujuwei;
	  uint32_t           stopwei;
	  uint32_t           jiouyanzheng;
	  uint32_t           RTSshujuliu;
	  uint32_t           CTSshujuliu;
	  uint32_t           TRANSMIT_switch;
	  uint32_t           RECEIVE_switch;
}usartx_init;


void usart_drive_init(gpio_drive_init* usartinit_TX,gpio_drive_init* usart_init_gpio_RX,usartx_init* usartx_init_drive);
void usart_interrupt_SWITCH_drive_RX(uint32_t usartx,uint32_t SWITCH);
void usart_interrupt_SWITCH_drive_TX(uint32_t usartx,uint32_t SWITCH);
FlagStatus usartX_interrupt_flag_get(uint32_t usart_periph, uint32_t int_flag);
uint16_t usartX_data_receive(uint32_t usart_periph);
FlagStatus usartX_flag_get(uint32_t usart_periph, usart_flag_enum int_flag);

#endif 



