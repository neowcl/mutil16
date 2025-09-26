#ifndef  _SYSCLOCKFUZHI_H
#define  _SYSCLOCKFUZHI_H


//用于时钟的开启，宏定义赋值
#define  RCU_periph1        RCU_GPIOA
#define  RCU_periph2        RCU_GPIOB
#define  RCU_periph3        RCU_USART0
#define  RCU_periph4        RCU_AF 
#define  RCU_periph5        RCU_SPI0 
#define  RCU_periph6        RCU_ADC0 
#define  RCU_periph7        RCU_DMA0 
#define  RCU_periph8        RCU_CAN0
#define  RCU_periph9        RCU_TIMER1






void rcu_periph_interface_clock_enable(void);        //用于各个外设是时钟的开启  RCU_AF    
void sysclockfuzhi(void);



#endif /* SYSCLOCKFUZHI_H*/



