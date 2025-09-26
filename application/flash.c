#include "flash.h"



uint8_t  FLASH_UnlockAndWait(void)
{
  uint16_t Time_Wait=0;
	Time_Wait=Time_Out_Set;
    // 解锁Flash
    FLASH_Unlock();
    // 等待Flash解锁完成
    while (FLASH_GetStatus() != FLASH_COMPLETE) {
        if (Time_Wait==0) {
            return 0;
        }
				Time_Wait--;
    }
    return 1;
}


/**
 * @brief  擦除Flash页
 * @param  page_address: 要擦除的页地址
 * @retval FlashStatus状态
 */
uint8_t FLASH_Erase_Page(uint16_t start)
{
   uint16_t Time_Wait=0;
	 uint8_t  status_Get;
	 uint8_t i=0;
	 FLASH_Status status;
    // 解锁Flash
    status_Get = FLASH_UnlockAndWait();
    if (status_Get != 1) {
        return 0;
    }
		Time_Wait=Time_Out_Set;
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	  status = FLASH_ErasePage((0x08000000+start*1024)+(1024*i));
		while ((status = FLASH_GetStatus()) == FLASH_BUSY) {
			Time_Wait--;
       if (Time_Wait==0) {
         FLASH_Lock();
				 FLASH_ClearFlag(FLASH_FLAG_EOP);
         return 0;
			}
    }
		FLASH_ClearFlag(FLASH_FLAG_EOP);
		// 锁定Flash
    FLASH_Lock();
    return 1;
}
		

uint8_t FLASH_Write(uint32_t address, uint32_t *data, uint32_t length)
{
    FLASH_Status   status;
	  uint8_t        status_Get;
    uint16_t       Time_Wait=0;
    uint8_t        i; 
    // 检查地址是否半字对齐
	  if((length%4)!=0)   //如果不是4的整数，则返回0
		{
			return 0;
		}
    if ((address & 0x1) != 0) {
        return 0;
    }
    // 解锁Flash
    status_Get = FLASH_UnlockAndWait();
    if (status_Get==0) {
        return 0;
    }
    // 写入数据
    for (i = 0; i < (length/4); i++) {
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        status = FLASH_ProgramWord(address, *data);

        // 等待写入完成
		  	Time_Wait=Time_Out_Set;
        while ((status = FLASH_GetStatus()) == FLASH_BUSY) {
					  Time_Wait--;
            if (Time_Wait==0) {
                FLASH_Lock();
                return 0;
            }
        }
        if (status != FLASH_COMPLETE) {
            FLASH_Lock();
            return 0;
        }
        
        // 验证写入的数据是否正确
        if (*(volatile uint32_t*)(address) != data[0]) {
            FLASH_Lock();
            return 0;
        }
				data+=1;   //地址加4
			  address+=4;   //所写地址加1；
    }
    
    // 锁定Flash
    FLASH_Lock();
    return 1;
}


void FLASH_Read(uint32_t address, uint8_t *data, uint32_t length)
{
    uint32_t i;
    // 读取数据
    for (i = 0; i < length; i++) {
        data[i] = *(volatile uint8_t*)(address + i);
    }
}













