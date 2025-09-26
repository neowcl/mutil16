#include "SH367309_interface.h"
#include "SH367309_drive.h"




bool Read_SH367309_BYTE(uint8_t Length,uint16_t WrAddr,uint8_t  *RdBuf)
{
if(!Read_SH367309_BYTE_Drive(Gpio_SDA_SH_Use, Pin_SDA_SH_Use,Gpio_SCL_SH_Use,Pin_SCL_SH_Use,Length,WrAddr,RdBuf))
{
	return FALSE;
}
return TRUE;
}


bool Write_SH367309_BYTE(uint8_t Length,uint16_t WrAddr,uint8_t  *WrBuf)
{
if(!Write_SH367309_BYTE_Drive(Gpio_SDA_SH_Use, Pin_SDA_SH_Use,Gpio_SCL_SH_Use,Pin_SCL_SH_Use,Length,WrAddr,WrBuf))
{
	return FALSE;
}
return TRUE;
}



//Check_SH367_Error_drive










