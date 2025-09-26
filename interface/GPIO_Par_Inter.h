#ifndef GPIO_PAR_INERT_H
#define GPIO_PAR_INERT_H
#include "stm32f10x.h"


#define    B_VOL        GPIOA     //PA0
#define    BL_SLEEP     GPIOA     //PA1
#define    BL_MODE      GPIOA     //PA2
#define    SOC_LED1     GPIOA     //PA3
#define    SOC_LED2     GPIOA     //PA4
#define    SOC_LED3     GPIOA     //PA5
#define    SOC_LED4     GPIOA     //PA6
#define    SOC_LED5     GPIOA     //PA7
#define    RS485_Contr_G   GPIOA     //PA8
#define    NONE_IO_A    GPIOA     //PA9
#define    NONE_IO_A    GPIOA     //PA10
#define    CANO_RX      GPIOA     //PA11
#define    CANO_TX      GPIOA     //PA12
#define    DIO_SWD      GPIOA     //PA13
#define    CLK_SWD      GPIOA     //PA14
#define    LED_RUN      GPIOA     //PA15       //led的控制
#define    CHG_CHK      GPIOB     //PB0        //检测C0 控制的输出端的电压
#define    Alert_G      GPIOB     //PB1      //检测DO 控制的输出端的电压
#define    NONE_IO_B    GPIOB     //PB2    
#define    RTC_SCL      GPIOB     //PB3  
#define    RTC_SDA      GPIOB     //PB4
#define    EE_WP        GPIOB     //PB5
#define    TX_485       GPIOB     //PB6
#define    RX_485       GPIOB     //PB7
#define    NONE_IO_B    GPIOB     //PB8
#define    NONE_IO_B    GPIOB     //PB9
#define    AFE_SCL      GPIOB     //PB10
#define    AFE_SDA      GPIOB     //PB11
#define    ALRM         GPIOB     //PB12       //各种事件的触发会引起这个管脚的电平变化
#define    PRO_EN       GPIOB     //PB13
#define    NONE_IO_B    GPIOB     //PB14
#define    NONE_IO_B    GPIOB     //PB15

#define    RS485_Contr_P   GPIO_Pin_8

#define    NONE_IO_C    GPIOC     //PC13
#define    NONE_IO_C    GPIOC     //PC14
#define    NONE_IO_C    GPIOC     //PC15


#define    NONE_IO_D    GPIOD     //PD0
#define    NONE_IO_D    GPIOD     //PD1

void LED_Do(void);

void GPIO_Set(void);

void Gpio_Set_mode(void);





#endif




