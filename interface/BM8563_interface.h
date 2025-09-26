#ifndef    BM8563_INTERFACE_H
#define    BM8563_INTERFACE_H
#include "stm32f10x.h"





#define   BM8563_Gpio_SDA      GPIOB     
#define   BM8563_Pin_SDA       GPIO_Pin_11
#define   BM8563_Gpio_SCL      GPIOB
#define   BM8563_Pin_SCL       GPIO_Pin_10
 
 
 
extern uint8_t  Time_Receive[7];

ErrorStatus BM8563_Init_Confi(void);
ErrorStatus Read_TimeNow(void);
ErrorStatus Set_BM8563_CountDown_Fre(void);
ErrorStatus Set_BM8563_Control_Regi(void);
ErrorStatus Set_BM8563_TimeAlarm(void);
ErrorStatus Set_BM8563_TimeNow(void);



#endif




