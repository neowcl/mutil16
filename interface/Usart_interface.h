#ifndef    _USART_INTERFACE_H
#define    _USART_INTERFACE_H
#include "stm32f10x.h"
#include   <stdbool.h>

#define USART1_TX_DMA_CHANNEL DMA1_Channel4
#define USART1_RX_DMA_CHANNEL DMA1_Channel5
#define USART1_DR_ADDRESS     ((uint32_t)&USART1->DR)

//#define RX_BUFFER_SIZE 256
#define TX_BUFFER_SIZE 1024

#define USART1_TX_DMA_CHANNEL DMA1_Channel4
#define USART1_RX_DMA_CHANNEL DMA1_Channel5
#define USART1_DR_ADDRESS     ((uint32_t)&USART1->DR)



#define   TX_GPIO    GPIOA
#define   RX_GPIO    GPIOA
#define   Contr_GPIO GPIOA
#define   TX_Pin     GPIO_Pin_9 
#define    RX_Pin    GPIO_Pin_10
#define   Contr_Pin  GPIO_Pin_8

// 缓冲区配置
#define U0_Tx_SIZE        100
#define U0_Rx_SIZE        500     // 接收缓冲区大小
#define U0_Rx_Max         100     // 需要预留给接收区的最小空间
#define Ptr_Num           10      // 数据块指针数量

// 数据结构
typedef struct {
    uint8_t *Start;               // 数据块起始地址
    uint8_t *End;                 // 数据块结束地址
} UCB_UsartRxBuffer;

typedef struct {
    uint16_t Rx_Count;            // 已接收数据总量
    UCB_UsartRxBuffer RxDataPtr[Ptr_Num]; // 数据块指针数组
    UCB_UsartRxBuffer *RxDataIn;  // 当前写入指针
    UCB_UsartRxBuffer *RxDataOut; // 当前读出指针
    UCB_UsartRxBuffer *RxDataEnd; // 指针数组末尾（边界检查）
    bool BufferOverflow;          // 缓冲区溢出标志
} UCB_Control;

extern uint8_t U0_RxBuff[U0_Rx_SIZE];
extern UCB_Control U0CB_Rx;
extern uint8_t tx_buffer_DMA[TX_BUFFER_SIZE];
extern volatile uint8_t tx_busy;










//// 环形缓冲区实现
//typedef struct {
//    uint8_t buffer[RX_BUFFER_SIZE];
//    volatile uint16_t head;
//    volatile uint16_t tail;
//} RingBuffer;




//extern  RingBuffer rx_buffer;

void USART1_Init(uint32_t baudrate);

void U0Rx_PtrInit(void);

void USART1_Init(uint32_t baudrate);
void USART1_SendString(uint8_t *str,uint16_t Length_Data);

uint8_t Rx_Message_Size(uint16_t *Length);
void Start_Receive_Message(void);
uint8_t USART1_SendData_DMA(uint8_t *data, uint16_t len);


void RS485_Stop_SendData(void);























#endif













