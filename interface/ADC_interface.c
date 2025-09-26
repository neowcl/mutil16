#include  "ADC_interface.h"
#include  "ADC_drive.h"
#include  "DMA_drive.h"
#include  "gpio_init.h"
#include  "systick.h"
#include  "LED_peizhi.h"

uint32_t adc_value[2];
uint32_t Vol_Value[2];


ADC_Init_Struct  ADC0_IN8_Init;
ADC_Init_Struct  ADC0_IN9_Init;
DMA_Init_Struct  DMA_Channel0_init;

	

void ADC0_IN8_Init_inter(void)
{
ADC0_IN8_Init.ADCX=ADC0_IN8_ADCX;
ADC0_IN8_Init.ADC_Mode=ADC0_IN8_ADCX_ADC_Mode;
ADC0_IN8_Init.ADC_ScanConvMode=ADC0_IN8_ADCX_ADC_ScanConvMode;
ADC0_IN8_Init.ADC_ContinuousConvMode=ADC0_IN8_ADCX_ADC_ContinuousConvMode;
ADC0_IN8_Init.ADC_ExternalTrigConv=ADC0_IN8_ADCX_ADC_ExternalTrigConv;
ADC0_IN8_Init.ADC_DataAlign=ADC0_IN8_ADCX_ADC_DataAlign;
ADC0_IN8_Init.ADC_NbrOfChannel=ADC0_IN8_ADCX_ADC_NbrOfChannel;
ADC0_IN8_Init.channel_group=ADC0_IN8_ADCX_channel_group;
ADC0_IN8_Init.ADC_channel=ADC0_IN8_ADCX_ADC_channel;
ADC0_IN8_Init.adc_samptx=ADC0_IN8_ADCX_adc_samptx;
ADC0_IN8_Init.channel_rank=ADC0_IN8_ADCX_channel_rank;
ADC0_IN8_Init.external_trigger_SEL=ADC0_IN8_ADCX_external_trigger_SEL;
ADC0_IN8_Init.ADC_Clock_DIVX=ADC0_IN8_ADCX_ADC_Clock_DIVX;
ADCx_special_Mode_Config_init(&ADC0_IN8_Init);	

}


void ADC0_IN9_Init_inter(void)
{
	
ADC0_IN9_Init.ADCX=ADC0_IN9_ADCX;
ADC0_IN9_Init.ADC_Mode=ADC0_IN9_ADCX_ADC_Mode;
ADC0_IN9_Init.ADC_ScanConvMode=ADC0_IN9_ADCX_ADC_ScanConvMode;
ADC0_IN9_Init.ADC_ContinuousConvMode=ADC0_IN9_ADCX_ADC_ContinuousConvMode;
ADC0_IN9_Init.ADC_ExternalTrigConv=ADC0_IN9_ADCX_ADC_ExternalTrigConv;
ADC0_IN9_Init.ADC_DataAlign=ADC0_IN9_ADCX_ADC_DataAlign;
ADC0_IN9_Init.ADC_NbrOfChannel=ADC0_IN9_ADCX_ADC_NbrOfChannel;
ADC0_IN9_Init.channel_group=ADC0_IN9_ADCX_channel_group;
ADC0_IN9_Init.ADC_channel=ADC0_IN9_ADCX_ADC_channel;
ADC0_IN9_Init.adc_samptx=ADC0_IN9_ADCX_adc_samptx;
ADC0_IN9_Init.channel_rank=ADC0_IN9_ADCX_channel_rank;
ADC0_IN9_Init.external_trigger_SEL=ADC0_IN9_ADCX_external_trigger_SEL;
ADC0_IN9_Init.ADC_Clock_DIVX=ADC0_IN8_ADCX_ADC_Clock_DIVX;
ADCx_special_Mode_Config_init(&ADC0_IN9_Init);	
}




void DMA_Channel0_init_inter(void)
{
DMA_Channel0_init.periph_addr=DMA_Channel0_periph_addr;
DMA_Channel0_init.periph_width=DMA_Channel0_periph_width;  
DMA_Channel0_init.memory_addr=DMA_Channel0_memory_addr;
DMA_Channel0_init.memory_width=DMA_Channel0_memory_width;
DMA_Channel0_init.number=DMA_Channel0_number;
DMA_Channel0_init.priority=DMA_Channel0_priority;
DMA_Channel0_init.periph_inc=DMA_Channel0_periph_inc;
DMA_Channel0_init.memory_inc=DMA_Channel0_memory_inc;  
DMA_Channel0_init.direction=DMA_Channel0_direction;  	
dma_config_m_d(DMA_Channel0_DMAX,DMA_Channel0_DMA_CHX,&DMA_Channel0_init);	
}











