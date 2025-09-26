#ifndef __GPIO_Init_H
#define __GPIO_Init_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

typedef struct
{
	GPIO_TypeDef*  GPIO;
  uint16_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */
  GPIOMode_TypeDef GPIO_Mode;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
  GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */
  FunctionalState NewState;
	uint32_t GPIO_Remap;
} gpio_drive_init;






#define  gpio_bit_reset_drive            GPIO_ResetBits 
#define  gpio_bit_set_drive              GPIO_SetBits
void gpio_mode_init(gpio_drive_init* GIOP_struct);
void GPIO_WORK_TIME(uint32_t ONTIME,uint32_t OFFTIME,GPIO_TypeDef* Gpiox,uint32_t Gpio_Pin);
FlagStatus gpio_input_bit_get_mcu_drive(gpio_drive_init* GIOP_struct);



#endif /*GPIO_Init_H*/




