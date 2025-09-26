#include "DMA_drive.h"


void dma_config_m_d(uint32_t DMAX,dma_channel_enum DMA_CHX,DMA_Init_Struct *DMAX_Init)
{
//dma_deinit(DMAX,DMA_CHX);
dma_init(DMAX,DMA_CHX,DMAX_Init);
dma_circulation_enable(DMAX,DMA_CHX);
dma_channel_enable(DMAX, DMA_CHX);
}












