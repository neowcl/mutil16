#ifndef STRUCT_DRIVE_H
#define STRUCT_DRIVE_H

#include "gd32f10x.h"



////////////////////////////////////////////////////////
 typedef struct
{     
    //rcu_periph_enum           fuyongpin;                                                        
    uint32_t                  selfuyong;  
	  uint32_t                  remap;  
    uint32_t                  pin;                                                             
    uint8_t                   speed;                                                           
    uint8_t                   mode;
	  uint32_t                  gpio;
	 // rcu_periph_enum           RCU_GPIO;
}gpio_drive_init;


//中断相关的结构体配置
/*
@brief   主要是对中断的进行配置，包括触发引脚，触发源，触发模式等
*/
typedef struct
{     
 uint8_t                     GPIOX_SOURCE;
 uint8_t                     PIN_SOURCE;              //主要是GOIP的终端驱动
 exti_line_enum             EXTI_XIAN;
 exti_mode_enum             INT_OR_EVENT;
 exti_trig_type_enum        CHUFA_MODE;
}GPIO_exti_init_struct;

/*
对中断源进行配置中断优先级
*/
typedef struct
{  
 uint8_t              EXTI_IRQ;                //主要是看相应的中断源
 uint8_t	            nvic_pre_priority;     //主优先级
 uint8_t              nvic__sub_priority;    //子优先级	
}priority_SET_struct;

#if (defined(GD32F10X_MD) || defined(GD32F10X_HD) || defined(GD32F10X_XD))
#define    spiX_parameter_struct            spi_parameter_struct

#elif  (other)
#endif


#endif



