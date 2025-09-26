#include "./CH9120_app/CH9120_app.h"
#include "./CH9120_interface/CH9120_interface.h"
uint8_t transmitter_buffer[] = "HELLOWORLD";//定义发送数组
uint8_t receiver_buffer[10];//定义接收数组
#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))    //计算数据的地址和数据的总内存
#define TRANSMIT_SIZE   (ARRAYNUM(transmitter_buffer) - 1)//计算大小      计算发送数组的内存大小
uint8_t transfersize = TRANSMIT_SIZE;   //发送数据内存的大小
uint8_t receivesize = 3;           //接受数据的个数，一个8位的数据为一个
__IO uint8_t txcount = 0;         //发送的个数
__IO uint16_t rxcount = 0;        //接收的个数






void CH9120_commun_device(void)
{
	CH9120_interrupt_switch(RX_ready,ENABLE);
	while(1)
	{	
			if(rxcount >= receivesize)//接收满10个字节，在USART0_IRQHandler函数中计数
			{
				rxcount=0;
				txcount=0;
				CH9120_interrupt_switch(TX_ready, ENABLE );//发送中断打开
				while(txcount < transfersize);//等待发送完成，在USART0_IRQHandler函数中计数
				while (RESET == CH9120_flag_get(TX_finish));//发送完成判断
				 CH9120_interrupt_switch(RX_ready, ENABLE);//接收中断打开
			}
    
	}
	
}


/*
void CH9120_commun_device(void)
{
	CH9120_interrupt_switch(RX_ready,DISABLE);
	while(1)
	{	
				rxcount=0;
				txcount=0;
				CH9120_interrupt_switch(TX_ready, ENABLE );//发送中断打开
				while(txcount < transfersize);//等待发送完成，在USART0_IRQHandler函数中计数
				while (RESET == CH9120_flag_get(TX_finish));//发送完成判断
	}
	
}

*/




