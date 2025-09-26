#include "Timer_interface.h"
#include "misc.h"

/**
  * @brief  TIM1初始化，配置1ms中断
  * @param  无
  * @retval 无
  */
void TIM1_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 使能TIM1时钟
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    
    // 定时器基本配置
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = 64 - 1; // 预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 重复计数器(高级定时器特有)
    
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    // 使能TIM1更新中断
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    
    // 配置TIM1中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // 使能TIM1
    TIM_Cmd(TIM1, ENABLE);
    
    // 如果是高级定时器(TIM1/TIM8)，需要额外使能主输出
  //  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}





void RCC_PeriphClockCmd_Enable(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  //IIC/重映射
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);            //I2C的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA , ENABLE); //串口，重映射时钟已开
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //定时器时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);   //can的时钟
 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  Alarm
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
}
























