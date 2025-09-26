#ifndef    TIMER_INTERFACE_H
#define    TIMER_INTERFACE_H

#include "stm32f10x.h"



/********************基本定时器TIM参数定义，只限TIM6、7************/
#define            BASIC_TIM6 // 如果使用TIM7，注释掉这个宏即可
#define            BASIC_TIM                   TIM6
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM6
#define            BASIC_TIM_Period            1079
#define            BASIC_TIM_Prescaler         1999
#define            BASIC_TIM_IRQ               TIM1_BRK_IRQn
#define            BASIC_TIM_IRQHandler        TIM1_BRK_IRQHandler







static void BASIC_TIM_Config(void);
static void BASIC_TIM_NVIC_Config(void);
void BASIC_TIM_Init(void);


#endif  /* TIMER_INTERFACE_H */







