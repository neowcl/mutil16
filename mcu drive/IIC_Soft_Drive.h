#ifndef IIc_Sofe_Dive_H
#define IIc_Sofe_Dive_H
#include "stm32f10x.h"
#include   "GPIO_Init.h"


#define High  gpio_bit_set_drive
#define Low   gpio_bit_reset_drive
#define Read_Data  gpio_input_bit_get

extern uint8_t  delay_Time_us;   //用来定义延时多久 

uint8_t  CRC8cal(uint8_t *p, uint8_t counter);    		   //look-up table calculte CRC 
void OUT_OUT(uint32_t Gpio_Out,uint32_t Pin_Out);
void OUT_IN(uint32_t Gpio_Out,uint32_t Pin_Out);
void I2C_Read(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t *byte);
void I2C_SEND(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t byte);

void I2C_STOP(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL);
void IIC_Start(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL);  //通讯函数开始函数
void IIC_Start(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL); //通讯函数开始函数
ErrorStatus I2C_Wait_Ack(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL);
ErrorStatus  I2C_Read_BYTE_Mode1(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t Length,uint8_t  *RdWrBuf);
ErrorStatus  I2C_Read_BYTE_Mode2(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t Length,uint8_t  *RdBuf);

ErrorStatus  I2C_SEND_One_BYTE(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t  WrBuf);    //主要是为了Sh367309
ErrorStatus  I2C_Write_One_BYTE(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t  WrBuf);    //主要是为了EEprom

//ErrorStatus I2C_SEND_BYTES(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint16_t WrAddr,uint8_t Length,uint8_t  *WrBuf);
void I2C_NoAck(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL);
void I2C_Ack(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL);

#endif




