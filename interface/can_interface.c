#include   "can_interface.h"


void CAN_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    
    /* Configure CAN pin: RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure CAN pin: TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* CAN register init */
    CAN_DeInit(CAN1);
    CAN_StructInit(&CAN_InitStructure);
    
    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;       // 时间触发通信模式禁用
    CAN_InitStructure.CAN_ABOM = ENABLE;        // 自动离线管理
    CAN_InitStructure.CAN_AWUM = ENABLE;        // 自动唤醒模式
    CAN_InitStructure.CAN_NART = DISABLE ;       // 非自动重传模式
    CAN_InitStructure.CAN_RFLM = DISABLE;       // 接收FIFO锁定模式
    CAN_InitStructure.CAN_TXFP = DISABLE;       // 发送FIFO优先级
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; // 正常模式
    CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;    // 同步跳转宽度
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;    // 时间段1
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;    // 时间段2
    CAN_InitStructure.CAN_Prescaler = 8;        // 分频系数
    
    if (CAN_Init(CAN1, &CAN_InitStructure) != CAN_InitStatus_Failed)
    {
        /* CAN filter init */
        CAN_FilterInitStructure.CAN_FilterNumber = 0;  // 使用过滤器0
        CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask; // 标识符屏蔽位模式
        CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; // 32位模式
        CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000; // 要过滤的ID高位
        CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;  // 要过滤的ID低位
        CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000; // 屏蔽位高位
        CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;  // 屏蔽位低位
        CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0; // 关联到FIFO0
        CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; // 激活过滤器
        CAN_FilterInit(&CAN_FilterInitStructure);
        
        /* Enable CAN interrupts */
        CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); // FIFO0消息挂起中断
			
			
								// 4. CAN过滤器配置 - 接收所有标准帧ID从0x220到0x227
					CAN_FilterInitStructure.CAN_FilterNumber = 0; // 使用过滤器0
					CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask; // 标识符屏蔽位模式
					CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; // 32位模式
					// 设置过滤器ID和掩码
					CAN_FilterInitStructure.CAN_FilterIdHigh = 0x220 << 5; // STDID[10:0]左移5位对齐
					CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
					CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x7F0 << 5; // 后三位不用匹配
					CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
					CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0; // 使用FIFO0
					CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; // 激活过滤器
					CAN_FilterInit(&CAN_FilterInitStructure);
					CAN_FilterInit(&CAN_FilterInitStructure);	
    }
    
    /* NVIC configuration */

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
	
	








