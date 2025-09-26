#ifndef _DMA_DRIVE_H
#define _DMA_DRIVE_H

#include "stm32f10x.h"




#define   DMA_Init_Struct       dma_parameter_struct




void dma_config_m_d(uint32_t DMAX,dma_channel_enum DMA_CHX,DMA_Init_Struct *DMAX_Init);




#endif




