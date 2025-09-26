#ifndef SPI_DRIVE_H
#define SPI_DRIVE_H
#include "stm32f10x.h"
#include "stdio.h"
#include "GPIO_Init.h"
//////////////////////////////GD32库的函数
#if (defined(GD32F10X_MD) || defined(GD32F10X_HD) || defined(GD32F10X_XD))
#define    spiX_parameter_struct            spi_parameter_struct

//定义spi接口
#define        spi_init_mcu_drive                spi_init
#define        spi_denit                         spi_i2s_deinit
#define        spi_enable_drive                  spi_enable
#define        spi_i2s_flag_get_drive            spi_i2s_flag_get 
#define        spi_i2s_data_transmit_drive       spi_i2s_data_transmit       //将数据写入data寄存器中
#define        spi_i2s_data_receive_drive        spi_i2s_data_receive        //接收对应的数据，问为什么没有16位的数据   
#elif  (other) 
#endif
////////////////////////

void SPI_Soft_SendData_Drive(unsigned char* WriteBuffer,uint8_t Number,gpio_drive_init* MOSI,gpio_drive_init* CLK,gpio_drive_init* NSS);
void SOFT_SPI_RW_MODE0( uint8_t write_dat,gpio_drive_init* MOSI,gpio_drive_init* CLK,gpio_drive_init* NSS);
void SOFT_SPI_RW_MODE1(uint8_t byte,gpio_drive_init* MOSI,gpio_drive_init* CLK); 
void SOFT_SPI_RW_MODE2(uint8_t byte,gpio_drive_init* MOSI,gpio_drive_init* CLK);  
void SOFT_SPI_RW_MODE3(uint8_t write_dat,gpio_drive_init* MOSI,gpio_drive_init* CLK);

void    spi_drive_init(uint32_t spi_periph,spiX_parameter_struct* spi_mcu_drive_par);
void    SPI_TransmitReceive_drive(uint32_t spix,unsigned char* WriteBuffer, unsigned char *ReadBuffer, unsigned char NumberOfByte,uint32_t  SPITimeout);
void    SPI_SendData_drive(uint32_t spix,unsigned char* WriteBuffer,unsigned char Number,uint32_t  SPITimeout);
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);


#endif






