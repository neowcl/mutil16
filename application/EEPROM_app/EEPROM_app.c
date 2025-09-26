#include   "EEPROM_app.h"
#include   "EEPROM_interface.h"

uint8_t readData[10]={0};
uint8_t writeData[8]={4,5,6,7,8,9,10,11};

void EEPROM_write_then_read(void)
{
EEPROM1_inter_byte_write_I2C(12,10);
EEPROM1_inter_WaitForWriteEnd();
IIC_nbyte_WritetoEEPROM1_inter(16,writeData,8);	
EEPROM1_inter_WaitForWriteEnd();
I2C_EEP1_inter_read_nbyte(16,readData,8);
}







