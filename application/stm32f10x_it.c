/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2011 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include   "stm32f10x_it.h"
#include   "IIC_hard_Drive.h"
#include   "Usart_interface.h"
#include   "systick.h"
#include   "Schedule.h"
#include   "GPIO_Par_Inter.h"
#include   "Can_Exchange.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	delay_decrement();
}

// PA5, PA6中断处理函数
void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        // PA5上升沿中断
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
    
    if (EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        // PA6上升沿中断
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
}

// PB15中断处理函数
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        // PB15上升沿中断
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}

/**
  * @brief  CAN接收中断处理
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{ 
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
	{
			// 从FIFO0读取消息
			
			
			Can_Response_Command();   //后续将任务挂起
		
			// 在这里处理接收到的消息
			// RxMessage.StdId 包含消息ID
			// RxMessage.Data 包含数据
			// RxMessage.DLC 包含数据长度
			// 清除中断标志	
	}
	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
}



/**
  * @brief  I2C1错误中断服务函数
  * @param  无
  * @retval 无
  */
void I2C1_ER_IRQHandler(void)
{
    // 检测总线错误
    if(I2C_GetITStatus(I2C1, I2C_IT_BERR))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_BERR);
        // 错误处理
    }
    
    // 检测仲裁丢失错误
    if(I2C_GetITStatus(I2C1, I2C_IT_ARLO))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_ARLO);
        // 错误处理
    }
    
    // 检测ACK错误
    if(I2C_GetITStatus(I2C1, I2C_IT_AF))
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
        // 错误处理
    }
    
}



/**
  * @brief  DMA1通道6中断服务函数(I2C1_TX)
  * @param  无
  * @retval 无
  */
void DMA1_Channel6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC6))
    {
        DMA_ClearITPendingBit(DMA1_IT_TC6);
        // 传输完成处理
        I2C_State = 0; // 回到空闲状态
    }
}

/**
  * @brief  DMA1通道7中断服务函数(I2C1_RX)
  * @param  无
  * @retval 无
  */
static uint8_t	iii=0;
void DMA1_Channel7_IRQHandler(void)
{
		if(DMA_GetITStatus(DMA1_IT_TC7))
    {
			if(iii==1)
			{       // 在最后一个字节传输完成前设置NACK
       I2C_AcknowledgeConfig(I2C1, DISABLE);
				iii=0;
			}
			
			if(DMA1_Channel7->CNDTR==1)
			{
				iii=1;
			}
			else
			{
				iii=0;
			}
        // 清除中断标志
        DMA_ClearITPendingBit(DMA1_IT_TC7);
    }
}



/**
  * @brief  TIM1更新中断服务函数
  * @param  无
  * @retval 无
  */
void TIM1_UP_IRQHandler(void)
{  	
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		 EVE_update();  //更新任务状态
		 TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}





/**
  * @brief  EXTI1中断服务函数(PB2)
  * @param  无
  * @retval 无
  */
void EXTI1_IRQHandler(void)
{
	uint8_t ID_Task=0;
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		  //标志位位读取1000ms倒计时复位
		 if((ID_Task=Filter_task_number(Period_Manage_Battery_Sta_Task))!=0)
			{
				EVE_queue[ID_Task]->delay=EVE_queue[ID_Task]->period;
				EVE_queue[ID_Task]->state=TASK_DELAYED;
			}
			//任务就绪
			if((ID_Task=Filter_task_number(Bq76952_Interrupt_processing_Task))!=0)
			{
				EVE_resume(ID_Task);
			}
		//清空中断标志位
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}



///1.RS485中断触发
//2.接收信息
void USART1_IRQHandler(void)
{    
	volatile uint32_t tmp;
	uint16_t received_len =0;
	if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) 
	{ 
     //存入环形存储序列
		//表示中断是空闲的
		//清除中断位
			tmp = USART1->SR;  // 读取USART_SR寄存器
			tmp = USART1->DR;  // 读取USART_DR寄存器
			(void)tmp;         // 防止编译器警告
	
			received_len = U0_Rx_Max - DMA_GetCurrDataCounter(USART1_RX_DMA_CHANNEL);
			// 检查缓冲区剩余空间
			if ((U0_Rx_SIZE - U0CB_Rx.Rx_Count) < received_len) {
					U0CB_Rx.BufferOverflow = true; // 标记溢出
					U0CB_Rx.Rx_Count = 0;         // 重置计数器
					U0CB_Rx.RxDataIn->Start = U0_RxBuff;
			}

			// 更新当前数据块信息
			U0CB_Rx.Rx_Count += received_len;
			U0CB_Rx.RxDataIn->End = &U0_RxBuff[U0CB_Rx.Rx_Count - 1];

			// 移动写入指针（环形缓冲区）
			U0CB_Rx.RxDataIn++;  //指向另一个指针
			if (U0CB_Rx.RxDataIn == U0CB_Rx.RxDataEnd) {        //如果指向最后一个指针地址
					U0CB_Rx.RxDataIn = &U0CB_Rx.RxDataPtr[0];
			}

			// 设置下一个数据块起始地址
			if ((U0_Rx_SIZE - U0CB_Rx.Rx_Count) >= U0_Rx_Max) {
					U0CB_Rx.RxDataIn->Start = &U0_RxBuff[U0CB_Rx.Rx_Count];   //如果足够
			} else {
				U0CB_Rx.RxDataIn->Start = U0_RxBuff; // 缓冲区回绕  //进行覆盖  //如果预留的空间不够
					U0CB_Rx.Rx_Count = 0;
			} 

			// 重新配置DMA
			DMA_Cmd(USART1_RX_DMA_CHANNEL, DISABLE);
			DMA_SetCurrDataCounter(USART1_RX_DMA_CHANNEL, U0_Rx_Max);
			USART1_RX_DMA_CHANNEL->CMAR = (uint32_t)U0CB_Rx.RxDataIn->Start;
			DMA_Cmd(USART1_RX_DMA_CHANNEL, ENABLE);
			//“RS485回复任务”是否恢复
			if(EVE_queue[Filter_task_number(RS485_Response_Data_Task)]->state==TASK_SUSPENDED)
			{
				//“RS485回复任务”恢复执行
				  EVE_resume(RS485_Response_Data_Task);  // 挂起任务。
			}
			USART_ClearITPendingBit(USART1,USART_IT_IDLE);   //清除标志位
	}
	//代表串口发送完成
	if (USART_GetITStatus(USART1, USART_IT_TC) != RESET) 
	{ 
		RS485_Stop_SendData();
		USART_ClearITPendingBit(USART1,USART_IT_TC);   //清除标志位
	}
	
	
}













/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


