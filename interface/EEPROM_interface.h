#ifndef  _EEPROM_INTERFACE_H
#define  _EEPROM_INTERFACE_H
#include "stm32f10x.h"


#define   Gpio_SDA_EEPROM_Use      GPIOB     
#define   Pin_SDA_EEPROM_Use       GPIO_Pin_4
#define   Gpio_SCL_EEPROM_Use      GPIOB
#define   Pin_SCL_EEPROM_Use       GPIO_Pin_3





#define  Check_EEprom_Written  Check_EEprom_Written_Drive(Gpio_SDA_EEPROM_Use,Pin_SDA_EEPROM_Use,Gpio_SCL_EEPROM_Use,Pin_SCL_EEPROM_Use)









#endif





