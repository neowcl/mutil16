#ifndef  _IIC_HARD_DRIVE_H
#define  _IIC_HARD_DRIVE_H



#include "stm32f10x.h"


// 定义I2C引脚
#define I2C1_SCL_PIN    GPIO_Pin_6
#define I2C1_SDA_PIN    GPIO_Pin_7
#define I2C1_GPIO_PORT  GPIOB

// 缓冲区大小
#define I2C_BUFFER_SIZE 32

#define I2C_TIMEOUT           20000


#define  I2C_Battery   I2C1

typedef enum
{
	Start_ERROR=0,
	Normal_OK=1,
	Slave_ERROR=2,
	Register_ERROR=3,
	DMA_ERROR=4,
	Busy_ERROR=5,
}IIC_FLag_E;









extern uint8_t I2C_Dev_Addr;
extern uint16_t I2C_Tx_Count;
extern uint16_t I2C_Rx_Count;



extern uint8_t I2C_Rx_Buffer[I2C_BUFFER_SIZE];
extern uint8_t tx_buffer_IIC[I2C_BUFFER_SIZE];
extern volatile uint8_t I2C_State; // 0:空闲 1:发送中 2:接收中


void I2C1_GPIO_Config(void);
void I2C1_Mode_Config(void);
void I2C1_DMA_TX_Config(void);
void I2C1_DMA_RX_Config(void);
void I2C1_NVIC_Config(void);
void I2C1_Init(void);
uint8_t smbus_read_with_pec(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);
uint8_t I2C_Read_DMA(uint8_t dev_addr, uint8_t *pdata, uint16_t size);
IIC_FLag_E I2C_Write_DMA(uint8_t *pdata, uint16_t size);
uint8_t I2C_ReadData_DMA(uint8_t regAddr, uint8_t *pData, uint16_t len);
void I2C_RecoverBus(I2C_TypeDef* I2Cx);
#endif  /*_IIC_HARD_DRIVE_H*/



