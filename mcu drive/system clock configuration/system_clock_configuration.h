#ifndef SYSTEM_CLOCK_CONFIGURATION_H
#define SYSTEM_CLOCK_CONFIGURATION_H
#include "stm32f10x.h"


#define C8M    1

typedef struct
{   
    uint32_t AHB_PRESCALER;                                                                                                               
    uint32_t PLLMF;                                                                                                                      
    uint32_t PREDV0;                                                                                                  
}AHBCLOCK_confi_struct;




void AHB_clock(AHBCLOCK_confi_struct* AHB_struct);    //AHB时钟配置
void  AHB_HXTAL72M(uint16_t X);                       //定义72MHZ
void rcu_periph_drive_clock_enable(rcu_periph_enum RCU_periph);   //用于开启时钟










#endif /* SYSTEM_CLOCK_CONFIGURATION_H */



