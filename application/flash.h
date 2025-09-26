#ifndef     _FLASH_H
#define     _FLASH_H

#include "stm32f10x.h"


#define Time_Out_Set     0x00FF
// 错误码定义










#define   Flash_SADDR                  0x08000000             //Flash起始地址
#define   Flash_Page_Size              1024                //Flash扇区的大小
#define   Bq76952_Set_Page             62      //0x0800E000
#define   Bq76952_Copy_Page            63      //0x0800E000



#define   Bq76952_Set_SADDR            Flash_SADDR+(Bq76952_Set_Page)*Flash_Page_Size    //设定存储位置
#define   Bq76952_Copy_SADDR           Flash_SADDR+(Bq76952_Copy_Page)*Flash_Page_Size    //备份存储位置

#define FLASH_PAGE_SIZE   (0x400) 
uint8_t  FLASH_UnlockAndWait(void);

uint8_t FLASH_Erase_Page(uint16_t start);

uint8_t FLASH_Write(uint32_t address, uint32_t *data, uint32_t length);

void FLASH_Read(uint32_t address, uint8_t *data, uint32_t length);
#endif
























