#ifndef IIC_DRIVE_H
#define IIC_DRIVE_H
#include "stm32f10x.h"
#include "GPIO_Init.h"

//设置IIC的初始化的结构体
typedef struct
{
  uint32_t I2C_ClockSpeed;          /*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 400kHz */

  uint16_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode */

  uint16_t I2C_DutyCycle;           /*!< Specifies the I2C fast mode duty cycle.
                                         This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

  uint16_t I2C_OwnAddress1;         /*!< Specifies the first device own address.
                                         This parameter can be a 7-bit or 10-bit address. */

  uint16_t I2C_Ack;                 /*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of @ref I2C_acknowledgement */

  uint16_t I2C_AcknowledgedAddress; /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address */
}I2C_drive_InitTypeDef;







#define    i2c_clock_config_mcu_drive          i2c_clock_config       //时钟的配置
#define    i2c_mode_addr_config_mcu_drive      i2c_mode_addr_config
#define    i2c_ack_config_mcu_drive            i2c_ack_config
#define    i2c_enable_mcu_drive                i2c_enable
#define    i2c_master_addressing_mcu_drive     i2c_master_addressing
#define    i2c_flag_get_mcu_drive              i2c_flag_get





void  I2C_init_drive_mcu(uint32_t I2CX,I2C_drive_InitTypeDef* I2CX_init_drive);


void I2CX_byte_write(uint32_t I2CX,uint8_t position_slave,\
	uint8_t addr_register,uint8_t data_IIC);

void IIC_nbyte_Write(uint32_t I2CX,uint8_t position_slave,\
	uint8_t addr_register,uint8_t *data_page_write,uint8_t numByteToWrite);


void SLAVE_WaitForWriteEnd(uint32_t I2CX,uint32_t position_slave);

void I2C_read_nbyte(uint32_t I2CX,uint8_t position_slave,\
	uint8_t addr_register,uint8_t *data_page_read,uint8_t numByteToread);



#endif



