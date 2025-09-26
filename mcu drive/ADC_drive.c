#include "ADC_drive.h"
#include "systick.h"


void  ADCx_special_Mode_Config_init(ADC_Init_Struct* ADCX_init)
{
rcu_adc_clock_config(ADCX_init->ADC_Clock_DIVX);
adc_deinit (ADCX_init->ADCX);	
adc_mode_config(ADCX_init->ADC_Mode);    //看看是独立模式还是并行模式
	if(ADCX_init->ADC_ScanConvMode)
	{
adc_special_function_config(ADCX_init->ADCX,ADC_SCAN_MODE,ENABLE);	
	}
	else
	{
adc_special_function_config(ADCX_init->ADCX,ADC_SCAN_MODE,DISABLE);	

 	}
	
if(ADCX_init->ADC_ContinuousConvMode)
	{
adc_special_function_config(ADCX_init->ADCX,ADC_CONTINUOUS_MODE,ENABLE);	
	}
	else
	{
adc_special_function_config(ADCX_init->ADCX,ADC_CONTINUOUS_MODE,DISABLE);	

 	}
adc_data_alignment_config(ADCX_init->ADCX, ADCX_init->ADC_DataAlign);
adc_channel_length_config(ADCX_init->ADCX, ADCX_init->channel_group, ADCX_init->ADC_NbrOfChannel);
adc_regular_channel_config(ADCX_init->ADCX,ADCX_init->channel_rank,ADCX_init->ADC_channel,ADCX_init->adc_samptx);	
adc_external_trigger_source_config(ADCX_init->ADCX,ADCX_init->channel_group,ADCX_init->ADC_ExternalTrigConv);	
	
switch(ADCX_init->external_trigger_SEL)
{
	case 0:
	 adc_external_trigger_config(ADCX_init->ADCX, ADC_REGULAR_CHANNEL, ENABLE);	
		break;
	case 1:
	 adc_external_trigger_config(ADCX_init->ADCX, ADC_REGULAR_CHANNEL, DISABLE);	
		break;
	case 2:
	 adc_external_trigger_config(ADCX_init->ADCX, ADC_INSERTED_CHANNEL, ENABLE);	
		break;
	case 3:
	 adc_external_trigger_config(ADCX_init->ADCX, ADC_INSERTED_CHANNEL, DISABLE);	
		break;
	default:
		while(1);
}	
adc_enable(ADCX_init->ADCX);
delay_1ms(1);
adc_calibration_enable(ADCX_init->ADCX);
adc_dma_mode_enable(ADCX_init->ADCX);      //DMA进行合理配置
adc_software_trigger_enable(ADCX_init->ADCX, ADCX_init->channel_group);
}























