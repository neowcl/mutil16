#include "EEPROM_interface.h"
#include "GPIO_Init.h"
#include "IIC_drive.h"
#include  "EEPROM_Drive.h"

ErrorStatus Read_EEPROM_BYTE(uint8_t Length,uint16_t WrAddr,uint8_t  *RdBuf)
{
if(!Read_EEPROM_BYTE_Drive(Gpio_SDA_EEPROM_Use, Pin_SDA_EEPROM_Use,Gpio_SCL_EEPROM_Use,Pin_SCL_EEPROM_Use,Length,WrAddr,RdBuf))
{
	return ERROR;
}
return SUCCESS;
}


ErrorStatus Write_EEPROM_BYTE(uint8_t Length,uint16_t WrAddr,uint8_t  *WrBuf)
{
if(!Write_EEPROM_BYTE_Drive(Gpio_SDA_EEPROM_Use, Pin_SDA_EEPROM_Use,Gpio_SCL_EEPROM_Use,Pin_SCL_EEPROM_Use,Length,WrAddr,WrBuf))
{
	return ERROR;
}
return SUCCESS;
}


