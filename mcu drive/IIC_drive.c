#include "IIC_drive.h"
#include "gpio_init.h"
#include "systick.h"


void  I2C_init_drive_mcu(uint32_t I2CX,I2C_drive_InitTypeDef* I2CX_init_drive)
{
i2c_clock_config_mcu_drive(I2CX,I2CX_init_drive->I2C_ClockSpeed,I2CX_init_drive->I2C_DutyCycle);   //配置时钟的时序
i2c_mode_addr_config_mcu_drive(I2CX,I2CX_init_drive->I2C_Mode, I2CX_init_drive->I2C_AcknowledgedAddress,I2CX_init_drive->I2C_OwnAddress1);
i2c_ack_config_mcu_drive(I2CX,I2CX_init_drive->I2C_Ack);	
i2c_enable(I2CX);	
}
/*******************************************************************************
* 函数名  : I2CX_byte_write
* 描述    : IIC写入一个字节
* 输入    : I2CX，从机位置position_slave,trandi`rection主从机模式，addr_register寄存器位置
             data_mcu_drive 数据内容
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void I2CX_byte_write(uint32_t I2CX,uint8_t position_slave,\
	uint8_t addr_register,uint8_t data_IIC)
{
i2c_ack_config_mcu_drive(I2CX,I2C_ACK_ENABLE);	
i2c_start_on_bus(I2CX);
while((i2c_flag_get(I2CX,I2C_FLAG_SBSEND))==0);
i2c_master_addressing_mcu_drive(I2CX,position_slave,I2C_TRANSMITTER);    //发送从机的地址，主机向从从机表示写
while((i2c_flag_get(I2CX,I2C_FLAG_ADDSEND)&i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);
i2c_data_transmit(I2CX,addr_register);
while((i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);
i2c_data_transmit(I2CX,data_IIC);
while((i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);
while((i2c_flag_get(I2CX,I2C_FLAG_BTC))==0);	
i2c_stop_on_bus(I2CX);
}
/*******************************************************************************
* 函数名  : SLAVE_WaitForWriteEnd
* 描述    : 等待从机内部的数据接收完成
* 输入    : I2CX，position_slave从机位置，position_slave寄存器位置
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void SLAVE_WaitForWriteEnd(uint32_t I2CX,uint32_t position_slave)
{
	i2c_ack_config_mcu_drive(I2CX,I2C_ACK_ENABLE);	
	do
	{
		do
		{
	i2c_start_on_bus(I2CX);
		}
	while((i2c_flag_get(I2CX,I2C_FLAG_SBSEND))==0);
	i2c_master_addressing_mcu_drive(I2CX,position_slave,I2C_TRANSMITTER);    //发送从机的地址，主机向从从机表示写
	}while((i2c_flag_get(I2CX,I2C_FLAG_ADDSEND))==0);
	i2c_stop_on_bus(I2CX);
	i2c_ack_config_mcu_drive(I2CX,I2C_ACK_DISABLE);
}

/*******************************************************************************
* 函数名  : IIC_nbyte_Write
* 描述    : 向从设备写入多个字节数据
* 输入    : I2CX，从机位置position_slave,trandirection主从机模式，addr_register寄存器位置
             *data_page数据内存数据，numByteToWrite个数
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void IIC_nbyte_Write(uint32_t I2CX,uint8_t position_slave,\
	uint8_t addr_register,uint8_t *data_page_write,uint8_t numByteToWrite)
{
	i2c_ack_config_mcu_drive(I2CX,I2C_ACK_ENABLE);	
i2c_start_on_bus(I2CX);
while((i2c_flag_get(I2CX,I2C_FLAG_SBSEND)& i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)\
	      &i2c_flag_get(I2CX,I2C_FLAG_MASTER))==0);

i2c_master_addressing_mcu_drive(I2CX,position_slave,I2C_TRANSMITTER);    //发送从机的地址，主机向从从机表示写
while((i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)&i2c_flag_get(I2CX,I2C_FLAG_ADDSEND)&\
	      i2c_flag_get(I2CX,I2C_FLAG_BTC)&i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);

i2c_data_transmit(I2CX,addr_register);
while((i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)&\
	      i2c_flag_get(I2CX,I2C_FLAG_BTC)& i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);

while(numByteToWrite)
{
i2c_data_transmit(I2CX,*data_page_write);
while((i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)&i2c_flag_get(I2CX,I2C_FLAG_MASTER)&\
	i2c_flag_get(I2CX,I2C_FLAG_BTC)& i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);
numByteToWrite--;
data_page_write++;
}
i2c_stop_on_bus(I2CX);
i2c_ack_config_mcu_drive(I2CX,I2C_ACK_DISABLE);
}





void I2C_read_nbyte(uint32_t I2CX,uint8_t position_slave,\
	uint8_t addr_register,uint8_t *data_page_read,uint8_t numByteToread)
{
i2c_start_on_bus(I2CX);
while((i2c_flag_get(I2CX,I2C_FLAG_SBSEND)& i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)\
	        &i2c_flag_get(I2CX,I2C_FLAG_MASTER))==0);	
i2c_master_addressing_mcu_drive(I2CX,position_slave,I2C_TRANSMITTER);    //发送从机的地址，主机向从从机表示写
while((i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)&i2c_flag_get(I2CX,I2C_FLAG_ADDSEND)&\
	      i2c_flag_get(I2CX,I2C_FLAG_MASTER)& i2c_flag_get(I2CX,I2C_FLAG_BTC)&i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);
i2c_data_transmit(I2CX,addr_register);
while((i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)&i2c_flag_get(I2CX,I2C_FLAG_MASTER)&\
	      i2c_flag_get(I2CX,I2C_FLAG_BTC)& i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);	

i2c_start_on_bus(I2CX);
while((i2c_flag_get(I2CX,I2C_FLAG_SBSEND)& i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)\
	        &i2c_flag_get(I2CX,I2C_FLAG_MASTER))==0);	
i2c_master_addressing_mcu_drive(I2CX,position_slave,I2C_RECEIVER);    //发送从机的地址，主机向从从机表示写
while((i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)&i2c_flag_get(I2CX,I2C_FLAG_ADDSEND)&\
	      i2c_flag_get(I2CX,I2C_FLAG_MASTER)& i2c_flag_get(I2CX,I2C_FLAG_BTC)&i2c_flag_get(I2CX,I2C_FLAG_TBE))==0);
while(numByteToread)
{
	if(numByteToread==1)
	{
	i2c_ack_config_mcu_drive(I2CX,I2C_ACK_DISABLE);	
	}
  while((i2c_flag_get(I2CX,I2C_FLAG_I2CBSY)&i2c_flag_get(I2CX,I2C_FLAG_MASTER)&\
	i2c_flag_get(I2CX,I2C_FLAG_RBNE))==0);	
  *data_page_read=i2c_data_receive(I2CX);
   numByteToread--;
   data_page_read++;
}
i2c_stop_on_bus(I2CX);

}









