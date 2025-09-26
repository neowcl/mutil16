#ifndef   _ADC_INTERFACE_H
#define   _ADC_INTERFACE_H
#include  "gd32f10x.h"
#include  "ADC_drive.h"
#include  "DMA_drive.h"





#define ADC0_PB1_Init_SEL             DISABLE
#define ADC0_PB1_Init_RCU_per         RCU_AF    /*!< alternate function clock */
#define ADC0_PB1_Init_remap           GPIO_SWJ_SWDPENABLE_REMAP   /*!< full SWJ(JTAG-DP + SW-DP),but without NJTRST */
#define ADC0_PB1_Init_GPIO            GPIOB    /*!< alternate function clock */
#define ADC0_PB1_Init_MODE            GPIO_MODE_AIN
#define ADC0_PB1_Init_speed           GPIO_OSPEED_50MHZ
#define ADC0_PB1_Init_PIN             GPIO_PIN_1

#define    ADC0_IN9_ADCX                                ADC0                   
#define    ADC0_IN9_ADCX_ADC_Mode                       ADC_MODE_FREE            
#define    ADC0_IN9_ADCX_ADC_ScanConvMode               ENABLE
#define    ADC0_IN9_ADCX_ADC_ContinuousConvMode         ENABLE
#define    ADC0_IN9_ADCX_ADC_ExternalTrigConv           ADC0_1_2_EXTTRIG_REGULAR_NONE    
#define    ADC0_IN9_ADCX_ADC_DataAlign                  ADC_DATAALIGN_LEFT
#define    ADC0_IN9_ADCX_ADC_NbrOfChannel               2
#define    ADC0_IN9_ADCX_channel_group                  ADC_REGULAR_CHANNEL    
#define    ADC0_IN9_ADCX_ADC_channel                    ADC_CHANNEL_9
#define    ADC0_IN9_ADCX_adc_samptx                     ADC_SAMPLETIME_55POINT5
#define    ADC0_IN9_ADCX_channel_rank                   0
#define    ADC0_IN9_ADCX_external_trigger_SEL           ADC_REGULAR_CHANNEL_ENABLE
#define    ADC0_IN8_ADCX_ADC_Clock_DIVX                 RCU_CKADC_CKAPB2_DIV12




#define ADC0_PB0_Init_SEL             DISABLE
#define ADC0_PB0_Init_RCU_per         RCU_AF    /*!< alternate function clock */
#define ADC0_PB0_Init_remap           GPIO_SWJ_SWDPENABLE_REMAP   /*!< full SWJ(JTAG-DP + SW-DP),but without NJTRST */
#define ADC0_PB0_Init_GPIO            GPIOB    /*!< alternate function clock */
#define ADC0_PB0_Init_MODE            GPIO_MODE_AIN
#define ADC0_PB0_Init_speed           GPIO_OSPEED_50MHZ
#define ADC0_PB0_Init_PIN             GPIO_PIN_0





#define    ADC0_IN8_ADCX                                ADC0                   
#define    ADC0_IN8_ADCX_ADC_Mode                       ADC_MODE_FREE            
#define    ADC0_IN8_ADCX_ADC_ScanConvMode               ENABLE
#define    ADC0_IN8_ADCX_ADC_ContinuousConvMode         ENABLE
#define    ADC0_IN8_ADCX_ADC_ExternalTrigConv           ADC0_1_2_EXTTRIG_REGULAR_NONE    
#define    ADC0_IN8_ADCX_ADC_DataAlign                  ADC_DATAALIGN_RIGHT
#define    ADC0_IN8_ADCX_ADC_NbrOfChannel               2
#define    ADC0_IN8_ADCX_channel_group                  ADC_REGULAR_CHANNEL    
#define    ADC0_IN8_ADCX_ADC_channel                    ADC_CHANNEL_8
#define    ADC0_IN8_ADCX_adc_samptx                     ADC_SAMPLETIME_55POINT5
#define    ADC0_IN8_ADCX_channel_rank                   1
#define    ADC0_IN8_ADCX_external_trigger_SEL           ADC_REGULAR_CHANNEL_ENABLE
#define    ADC0_IN8_ADCX_ADC_Clock_DIVX                 RCU_CKADC_CKAPB2_DIV12


#define    DMA_Channel0_DMAX                           DMA0
#define    DMA_Channel0_DMA_CHX                        DMA_CH0  
	
#define    DMA_Channel0_periph_addr                    (uint32_t)(&ADC_RDATA(ADC0))    //寻找ADC数据位的地址,注意需要加一个&
#define    DMA_Channel0_periph_width                   DMA_PERIPHERAL_WIDTH_32BIT
#define    DMA_Channel0_memory_addr                    (uint32_t)adc_value       //变量的地址,这个是自己定义的变量
#define    DMA_Channel0_memory_width                   DMA_MEMORY_WIDTH_32BIT
#define    DMA_Channel0_number                         2                                 //DMA的通道选择,我们是ADC,是channe0
#define    DMA_Channel0_priority                       DMA_PRIORITY_HIGH   
#define    DMA_Channel0_periph_inc                     DMA_PERIPH_INCREASE_DISABLE
#define    DMA_Channel0_memory_inc                     DMA_MEMORY_INCREASE_ENABLE       
#define    DMA_Channel0_direction	                     DMA_PERIPHERAL_TO_MEMORY


void Voltage_measure(void);
void ADC0_IN8_Init_inter(void);	 
void ADC0_IN9_Init_inter(void);
void DMA_Channel0_init_inter(void);
#endif




