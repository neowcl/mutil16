#ifndef  _ADC_DRIVE_H_
#define   _ADC_DRIVE_H_

#include "stm32f10x.h"



#define  ADC_REGULAR_CHANNEL_ENABLE        0
#define  ADC_REGULAR_CHANNEL_DISABLE       1
#define  ADC_INSERTED_CHANNEL_ENABLE       2
#define  ADC_INSERTED_CHANNEL_DISABLE      3






typedef struct
{
	
	uint32_t  ADCX;
	
  uint32_t ADC_Mode;                      /*!< Configures the ADC to operate in independent or
                                               dual mode. 
                                               This parameter can be a value of @ref ADC_mode */

  ControlStatus ADC_ScanConvMode;       /*!< Specifies whether the conversion is performed in
                                               Scan (multichannels) or Single (one channel) mode.
                                               This parameter can be set to ENABLE or DISABLE */

  ControlStatus ADC_ContinuousConvMode; /*!< Specifies whether the conversion is performed in
                                               Continuous or Single mode.
                                               This parameter can be set to ENABLE or DISABLE. */

  uint32_t ADC_ExternalTrigConv;          /*!< Defines the external trigger used to start the analog
                                               to digital conversion of regular channels. This parameter
                                               can be a value of @ref ADC_external_trigger_sources_for_regular_channels_conversion */

  uint32_t ADC_DataAlign;                 /*!< Specifies whether the ADC data alignment is left or right.
                                               This parameter can be a value of @ref ADC_data_align */

  uint8_t ADC_NbrOfChannel;               /*!< Specifies the number of ADC channels that will be converted
                                               using the sequencer for regular channel group.
                                               This parameter must range from 1 to 16. */
	uint8_t channel_group;            //注入通道还是常规通道//
	
	uint8_t ADC_channel;            /* 通道选择*/
	
	uint32_t adc_samptx;                /*adc的采集速率*/
	
	uint32_t  channel_rank;             //通道的数量//
	
	uint32_t external_trigger_SEL;
	
	uint32_t  ADC_Clock_DIVX;           //ADC时钟分频
	
	
}ADC_Init_Struct;



void  ADCx_special_Mode_Config_init(ADC_Init_Struct* ADCX_init);



#endif



