#include "ADC_Api.h"
#include "ADC_interface.h"
#include "systick.h"

extern uint32_t adc_value[2];
extern uint32_t Vol_Value[2];


//uint16_t adc_value;
void Voltage_measure(void)
{
Vol_Value[0]=(adc_value[0])*3300/4095;
Vol_Value[1]=(adc_value[1])*3300/4095;
delay_1ms(500);
}















