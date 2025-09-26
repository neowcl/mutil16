#include "Usart_interface.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "GPIO_Par_Inter.h"
#include <stdio.h>
#include <string.h>
#include "systick.h"

//RingBuffer rx_buffer;
uint8_t tx_buffer_DMA[TX_BUFFER_SIZE];
volatile uint8_t tx_busy;

uint8_t U0_RxBuff[U0_Rx_SIZE];
UCB_Control U0CB_Rx;



void USART1_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    // 1. 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    // 2. 配置GPIO
    // PA9 - USART1_TX
    GPIO_InitStructure.GPIO_Pin = TX_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TX_GPIO, &GPIO_InitStructure);
    
    // PA10 - USART1_RX
    GPIO_InitStructure.GPIO_Pin = RX_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(RX_GPIO, &GPIO_InitStructure);
	 //PA8
	  GPIO_InitStructure.GPIO_Pin = Contr_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(Contr_GPIO, &GPIO_InitStructure);
     
		 
		GPIO_ResetBits(RS485_Contr_G,RS485_Contr_P);   //为接收状态

    // 3. 配置USART1
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    // 4. 配置DMA发送
    DMA_DeInit(USART1_TX_DMA_CHANNEL);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)tx_buffer_DMA;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(USART1_TX_DMA_CHANNEL, &DMA_InitStructure);

    // 5. 配置DMA接收
    DMA_DeInit(USART1_RX_DMA_CHANNEL);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr =  (uint32_t)U0_RxBuff;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = U0_Rx_Max;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // 循环模式
    DMA_Init(USART1_RX_DMA_CHANNEL, &DMA_InitStructure);

    // 6. 使能USART1 DMA
    USART_DMACmd(USART1, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);

    // 7. 配置USART1中断
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); // 空闲中断用于接收
    
		USART_ITConfig(USART1, USART_IT_TC, ENABLE); // 空闲中断用于接收
		
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 8. 使能DMA和USART
    DMA_Cmd(USART1_RX_DMA_CHANNEL, ENABLE);
    USART_Cmd(USART1, ENABLE);
		

		U0Rx_PtrInit();   //重新定义串口接收结构体
}



void DMA_Usart_Address_Fresh(uint16_t size,uint32_t Memory_Address)
{
	USART1_TX_DMA_CHANNEL->CNDTR=size;      //重新归类
	USART1_TX_DMA_CHANNEL->CMAR=Memory_Address; 
}



//// 重定向printf到USART1
//int fputc(int ch, FILE *f)
//{

//    USART_SendData(USART1, (uint8_t)ch);
//    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)  //?????注意问题，给一个具体时间的时间
//    return ch;
//}

//// 实现getchar函数
//int __io_getchar(void)
//{
//	  uint8_t ch=0;
//    while(rx_buffer.head == rx_buffer.tail); // 等待数据
//    __disable_irq();
//    ch = rx_buffer.buffer[rx_buffer.tail];
//    rx_buffer.tail = (rx_buffer.tail + 1) % RX_BUFFER_SIZE;
//    __enable_irq();
//    return ch;
//}



//进行发送数据
uint8_t USART1_SendData_DMA(uint8_t *data, uint16_t len)
{
	uint16_t Time_delay=0;
	Time_delay=100;
	do 
	{
		//RS485状态是否为繁忙
		if(tx_busy==0)
		{ // 等待上次发送完成 //或者未发送
			if ((DMA_GetCurrDataCounter(DMA1_Channel5) == U0_Rx_Max)&&\
				(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET))  //无数据在接收 
			{
				GPIO_SetBits(RS485_Contr_G,RS485_Contr_P);   //为接收状态
				delay_1us(200);      //等待500us
				if(len > TX_BUFFER_SIZE) len = TX_BUFFER_SIZE;
				memcpy(tx_buffer_DMA, data, len);
				DMA_Cmd(USART1_TX_DMA_CHANNEL, DISABLE);
				DMA_SetCurrDataCounter(USART1_TX_DMA_CHANNEL, len);
				tx_busy = 1;
				DMA_Cmd(USART1_TX_DMA_CHANNEL, ENABLE);
				return 1;
			 }
		}
		if(tx_busy==1)
		{
			delay_1us(200);   //延时100us
		}
		Time_delay--;
  }while(Time_delay!=0);
	if(Time_delay==0)
	{
		//printf(进行上报错误)。
		tx_busy=0;
		return 0;
	}
	return 1;
}

// 发送字符串
void USART1_SendString(uint8_t *str,uint16_t Length_Data)
{
  USART1_SendData_DMA((uint8_t*)str, Length_Data);
}



// 初始化指针管理结构体
void U0Rx_PtrInit(void) {
    U0CB_Rx.RxDataIn = &U0CB_Rx.RxDataPtr[0];
    U0CB_Rx.RxDataOut = &U0CB_Rx.RxDataPtr[0];
    U0CB_Rx.RxDataEnd = &U0CB_Rx.RxDataPtr[Ptr_Num - 1];
    U0CB_Rx.RxDataIn->Start = U0_RxBuff;
    U0CB_Rx.Rx_Count = 0;
    U0CB_Rx.BufferOverflow = false;
}

// 移动到下一个数据块（通常在处理完当前数据后调用）
void Start_Receive_Message(void) {
    if (U0CB_Rx.RxDataOut == U0CB_Rx.RxDataIn) return; // 无新数据可移动

    U0CB_Rx.RxDataOut++;
    if (U0CB_Rx.RxDataOut > U0CB_Rx.RxDataEnd) {
        U0CB_Rx.RxDataOut = &U0CB_Rx.RxDataPtr[0]; // 环形回绕
    }
}

// 读取指定位置的数据（安全访问）
uint8_t Rx_Message_Manage(uint16_t number) {
  	uint16_t block_len=0;
    if (U0CB_Rx.RxDataOut == U0CB_Rx.RxDataIn) return 0; // 无数据
    
    block_len = U0CB_Rx.RxDataOut->End - U0CB_Rx.RxDataOut->Start + 1;
    if (number >= block_len) return 0; // 越界保护
    
    return U0CB_Rx.RxDataOut->Start[number];
}

// 获取当前数据块长度
uint8_t Rx_Message_Size(uint16_t *Length) {
    if (U0CB_Rx.RxDataOut == U0CB_Rx.RxDataIn) {
        *Length = 0;
        return 0; // 无数据
    }
    *Length = U0CB_Rx.RxDataOut->End - U0CB_Rx.RxDataOut->Start + 1;
    return 1; // 成功获取长度
}


//关闭485的GPIO，延时关闭GPIO，进行合理发送信息
//收发器为接收模式，代表不繁忙
//繁忙复位任务
void RS485_Stop_SendData(void)
{
	GPIOA->BRR=GPIO_Pin_8;
  tx_busy = 0; // 标记发送完成
}

























	
