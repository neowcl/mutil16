#include "IIC_hard_Drive.h"
#include "string.h"
#include "Bq7695202_drive.h"
#include "./systick/systick.h" 
#include   <stdbool.h>

// 全局变量
uint8_t I2C_Rx_Buffer[I2C_BUFFER_SIZE];    //接收内存
uint8_t tx_buffer_IIC[I2C_BUFFER_SIZE];
// 全局变量
uint8_t I2C_Dev_Addr = 0;
uint16_t I2C_Tx_Count = 0;
uint16_t I2C_Rx_Count = 0;
volatile uint8_t I2C_State =0; // 0:空闲 1:发送中 2:接收中




/**
  * @brief  I2C1 GPIO和模式配置
  * @param  无
  * @retval 无
  */
void I2C1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
	// 使能GPIO，重映射和I2C时钟
   // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    
    // 配置I2C SCL和SDA引脚
    GPIO_InitStructure.GPIO_Pin = I2C1_SCL_PIN | I2C1_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // 复用开漏输出，进行输出信号或者信息读取
    GPIO_Init(I2C1_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  I2C1工作模式配置
  * @param  无
  * @retval 无
  */
void I2C1_Mode_Config(void)
{
    I2C_InitTypeDef I2C_InitStructure;
    
    I2C_DeInit(I2C1);
    
    // I2C配置
	  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;      //主机模式，PEC校验
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;   //调整占空比
    I2C_InitStructure.I2C_OwnAddress1 = 0x00; // 主模式不需要地址
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   //使用7位地址模式
    I2C_InitStructure.I2C_ClockSpeed = 200000; // 400kHz标准模式  //选用200HZ
    I2C_Init(I2C1, &I2C_InitStructure);
    
    // 使能I2C
    I2C_Cmd(I2C1, ENABLE);
	  //启动PEC的计算
	 // I2C_CalculatePEC(I2C1, ENABLE);
}

/**
  * @brief  DMA1通道6配置(I2C1_TX)
  * @param  无
  * @retval 无
  */
void I2C1_DMA_TX_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    DMA_DeInit(DMA1_Channel6);
    
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&I2C1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)tx_buffer_IIC;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);
}

/**
  * @brief  DMA1通道7配置(I2C1_RX)
  * @param  无
  * @retval 无
  */
void I2C1_DMA_RX_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    DMA_DeInit(DMA1_Channel7);
    
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&I2C1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)I2C_Rx_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    
    DMA_Init(DMA1_Channel7, &DMA_InitStructure);
	  I2C_DMACmd(I2C1, ENABLE);
}

/**
  * @brief  NVIC配置
  * @param  无
  * @retval 无
  */
void I2C1_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
   // NVIC_InitTypeDef NVIC_InitStruct;
    // I2C1事件中断
	/*
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  */  
    // I2C1错误中断
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	
	
				

			// 配置NVIC
//			NVIC_InitTypeDef NVIC_InitStruct;
//			NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel7_IRQn;
//			NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
//			NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
//			NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//			NVIC_Init(&NVIC_InitStruct);
//	
//	
//			DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);

			// 配置NVIC
			// 使能DMA传输完成中断
	
//			NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel7_IRQn;
//			NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
//			NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
//			NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//			NVIC_Init(&NVIC_InitStruct);
//		  DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
      //NVIC_EnableIRQ(DMA1_Channel7_IRQn);
			
		
	
	
}

/**
  * @brief  I2C1初始化
  * @param  无
  * @retval 无
  */
void I2C1_Init(void)
{
    I2C1_GPIO_Config();
    I2C1_Mode_Config();
    I2C1_DMA_TX_Config();
    I2C1_DMA_RX_Config();
    I2C1_NVIC_Config();
    
    // 使能I2C中断
    //I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_ERR, ENABLE);
}









/**
* @brief  I2C主设备发送数据，不主动计算CRC校验码，需要通过软件实现
  * @param  dev_addr: 从设备地址
  * @param  pdata: 发送数据缓冲区
  * @param  size: 发送数据大小
  * @retval 0:成功 1:失败
  *
  */ 
IIC_FLag_E I2C_Write_DMA(uint8_t *pdata, uint16_t size)
{
    uint16_t     timeout = 0;
	  I2C_DMACmd(I2C1, ENABLE);
	  DMA_Cmd(DMA1_Channel6, DISABLE);    //关闭
  // 1. 等待I2C总线空闲
	  timeout=0xFFFE;
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {
		    	timeout--;
        if (timeout == 0) 
				{
					I2C_GenerateSTOP(I2C1, ENABLE);
						// 超时处理：强制复位总线
						I2C_RecoverBus(I2C1);
						return Busy_ERROR;  // 超时
				}
    }
		//2.发送start信号
		I2C_GenerateSTART(I2C1, ENABLE);

    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
        if((timeout--) == 0) 
				{
					//I2C_DMACmd(I2C1, DISABLE);
					I2C_GenerateSTOP(I2C1, ENABLE);
					I2C_RecoverBus(I2C1);
					return Start_ERROR;
				}
    }
		//3.发送从设备地址
		I2C_Send7bitAddress(I2C1, DEV_ADDR, I2C_Direction_Transmitter);
    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
		{  //EV6
			if((timeout--) == 0) 
			{
				//I2C_DMACmd(I2C1, DISABLE);
				I2C_GenerateSTOP(I2C1, ENABLE);
				I2C_RecoverBus(I2C1);
				return Slave_ERROR;
			}
    }
		// 4. 配置DMA发送寄存器地址
		DMA_ClearFlag(DMA1_FLAG_TC6);   //需要清除标志位；
		DMA_Cmd(DMA1_Channel6, DISABLE);    //关闭
    DMA1_Channel6->CMAR = (uint32_t)pdata;
		DMA_SetCurrDataCounter(DMA1_Channel6,size+1);
    DMA_Cmd(DMA1_Channel6, ENABLE);
		// 等待DMA传输完成
    timeout = I2C_TIMEOUT;
    while(!DMA_GetFlagStatus(DMA1_FLAG_TC6)) {
        if((timeout--) == 0) {
					DMA_ClearFlag(DMA1_FLAG_TC6);   //需要清除标志位；
          DMA_Cmd(DMA1_Channel6, DISABLE);
          I2C_DMACmd(I2C1, DISABLE);
					I2C_RecoverBus(I2C1);
            return DMA_ERROR;
        }
    }
		DMA_ClearFlag(DMA1_FLAG_TC6);   //需要清除标志位；
		I2C_GenerateSTOP(I2C1, ENABLE);
		I2C_DMACmd(I2C1, DISABLE);
	  DMA_Cmd(DMA1_Channel6, DISABLE);    //关闭
    return Normal_OK;  // 发送成功	
}


uint8_t I2C_Read_DMA(uint8_t regAddr, uint8_t *pData, uint16_t len)
{
	
	 uint32_t timeout = 0;
	  DMA_Cmd(DMA1_Channel6, DISABLE);    //关闭
	  I2C_GenerateSTART(I2C1, ENABLE);
    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
        if((timeout--) == 0) 
				{
					//I2C_DMACmd(I2C1, DISABLE);
					I2C_AcknowledgeConfig(I2C1, DISABLE);
					I2C_GenerateSTOP(I2C1, ENABLE);
					I2C_RecoverBus(I2C1);
					return 0;
				}
    }
    
    // 5. 发送设备地址(读)
		I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_Send7bitAddress(I2C1, DEV_ADDR, I2C_Direction_Receiver);
    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {   //EV6
        if((timeout--) == 0) 
				{
					 //I2C_DMACmd(I2C1, DISABLE);
					I2C_GenerateSTOP(I2C1, ENABLE);
					I2C_RecoverBus(I2C1);
					return 0;
				}
    }
    // 6. 配置DMA接收数据
    DMA1_Channel7->CMAR = (uint32_t)pData;
    DMA_SetCurrDataCounter(DMA1_Channel7,len);
    // 使能I2C DMA请求
		DMA_Cmd(DMA1_Channel7, ENABLE);
    // 等待DMA传输完成
    timeout = I2C_TIMEOUT;
    while(!DMA_GetFlagStatus(DMA1_FLAG_TC7)) {
        if((timeout--) == 0) {
					 DMA_ClearFlag(DMA1_FLAG_TC7);   //清除标志位
            DMA_Cmd(DMA1_Channel7, DISABLE);
					//  I2C_DMACmd(I2C1, DISABLE);
				  	I2C_AcknowledgeConfig(I2C1, DISABLE);
					  I2C_GenerateSTOP(I2C1, ENABLE);
				  	I2C_RecoverBus(I2C1);
            return 0;
        }
    }
		DMA_ClearFlag(DMA1_FLAG_TC7);   //清除标志位
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    // 发送停止条件
    I2C_GenerateSTOP(I2C1, ENABLE);
    DMA_Cmd(DMA1_Channel7, DISABLE);
		I2C_DMACmd(I2C1, DISABLE);
    return 1;
}








uint8_t I2C_ReadData_DMA(uint8_t regAddr, uint8_t *pData, uint16_t len)
{
    uint32_t timeout = 0;
	
	  I2C_DMACmd(I2C1, ENABLE);
	
	  DMA_Cmd(DMA1_Channel6, DISABLE);    //关闭
	  DMA_Cmd(DMA1_Channel7, DISABLE);
  	timeout=5000;
	  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {
    if (timeout-- == 0) {
        // 超时处理：强制复位总线
        I2C_RecoverBus(I2C1);
        break;
     }
    }
    I2C_GenerateSTART(I2C1, ENABLE);
    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
        if((timeout--) == 0) 
				{
					//I2C_DMACmd(I2C1, DISABLE);
					I2C_GenerateSTOP(I2C1, ENABLE);
					I2C_RecoverBus(I2C1);
					return 0;
				}
    }
    // 2. 发送设备地址(写)
    I2C_Send7bitAddress(I2C1, DEV_ADDR, I2C_Direction_Transmitter);
    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {  //EV6
        if((timeout--) == 0) 
				{
					//I2C_DMACmd(I2C1, DISABLE);
					I2C_GenerateSTOP(I2C1, ENABLE);
					I2C_RecoverBus(I2C1);
					return 0;
				}

    }
    // 3. 配置DMA发送寄存器地址
    DMA1_Channel6->CMAR = (uint32_t)&regAddr;
		DMA_SetCurrDataCounter(DMA1_Channel6,1);
    DMA_Cmd(DMA1_Channel6, ENABLE);
  
    // 等待DMA传输完成
    timeout = I2C_TIMEOUT;
    while(!DMA_GetFlagStatus(DMA1_FLAG_TC6)) {
        if((timeout--) == 0) {
					DMA_ClearFlag(DMA1_FLAG_TC6);   //需要清除标志位；
          DMA_Cmd(DMA1_Channel6, DISABLE);
         // I2C_DMACmd(I2C1, DISABLE);
					I2C_RecoverBus(I2C1);
            return 0;
        }
    }
		 DMA_ClearFlag(DMA1_FLAG_TC6);   //需要清除标志位；
		//I2C_GenerateSTOP(I2C1, ENABLE);
    // 4. 重新发送起始条件(重复起始)
    I2C_GenerateSTART(I2C1, ENABLE);
    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
        if((timeout--) == 0) 
				{
					//I2C_DMACmd(I2C1, DISABLE);
					I2C_AcknowledgeConfig(I2C1, DISABLE);
					I2C_GenerateSTOP(I2C1, ENABLE);
					I2C_RecoverBus(I2C1);
					return 0;
				}
    }
    
    // 5. 发送设备地址(读)
		I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_Send7bitAddress(I2C1, DEV_ADDR, I2C_Direction_Receiver);
    timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {   //EV6
        if((timeout--) == 0) 
				{
					 //I2C_DMACmd(I2C1, DISABLE);
					I2C_GenerateSTOP(I2C1, ENABLE);
					I2C_RecoverBus(I2C1);
					return 0;
				}
    }
    // 6. 配置DMA接收数据
    DMA1_Channel7->CMAR = (uint32_t)pData;
    DMA_SetCurrDataCounter(DMA1_Channel7,len);
    // 使能I2C DMA请求
		DMA_Cmd(DMA1_Channel7, ENABLE);
    // 等待DMA传输完成
    timeout = I2C_TIMEOUT;
    while(!DMA_GetFlagStatus(DMA1_FLAG_TC7)) {
			timeout--;
        if(timeout == 0) {
					 DMA_ClearFlag(DMA1_FLAG_TC7);   //清除标志位
            DMA_Cmd(DMA1_Channel7, DISABLE);
					//  I2C_DMACmd(I2C1, DISABLE);
				  	I2C_AcknowledgeConfig(I2C1, DISABLE);
					  I2C_GenerateSTOP(I2C1, ENABLE);
				  	I2C_RecoverBus(I2C1);
            return 0;
        }
    }
		DMA_ClearFlag(DMA1_FLAG_TC7);   //清除标志位
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    // 发送停止条件
    I2C_GenerateSTOP(I2C1, ENABLE);
    DMA_Cmd(DMA1_Channel7, DISABLE);
		I2C_DMACmd(I2C1, DISABLE);
    return 1;
}











void I2C_RecoverBus(I2C_TypeDef* I2Cx) {
    // 1. 强制生成 STOP
  	uint8_t i=0;
	  uint16_t time_out=0;
	  GPIO_InitTypeDef GPIO_InitStruct;
    I2C_GenerateSTOP(I2Cx, ENABLE);
    
    // 2. 模拟时钟脉冲（尝试释放 SDA）
    GPIO_InitStruct.GPIO_Pin = I2C1_SCL_PIN | I2C1_SDA_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD; // 复用开漏输出，进行输出信号或者信息读取
    GPIO_Init(I2C1_GPIO_PORT, &GPIO_InitStruct);

	  GPIO_SetBits(I2C1_GPIO_PORT,I2C1_SDA_PIN);
    // 发送 9 个时钟脉冲（I2C 标准恢复流程）
    for ( i = 0; i < 9; i++) {
        GPIO_ResetBits(I2C1_GPIO_PORT,I2C1_SCL_PIN);
			  time_out=0x0FFF;
			  while(time_out!=0){time_out--;};
        GPIO_SetBits(I2C1_GPIO_PORT,I2C1_SCL_PIN);
				time_out=0x0FFF;
			  while(time_out!=0){time_out--;};
    }
    
    // 3. 重新初始化 I2C
		GPIO_InitStruct.GPIO_Pin = I2C1_SCL_PIN | I2C1_SDA_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD; // 复用开漏输出，进行输出信号或者信息读取
    GPIO_Init(I2C1_GPIO_PORT, &GPIO_InitStruct);
		I2C_SoftwareResetCmd(I2Cx, ENABLE);
    I2C_SoftwareResetCmd(I2Cx, DISABLE);
		I2C1_Mode_Config();
}





