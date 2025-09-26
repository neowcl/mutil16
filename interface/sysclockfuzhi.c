#include "sysclockfuzhi.h" 
#include "system_clock_configuration.h" 


	//sysclockfuzhi();      //由于sysclock在初始化的时候完成，可暂不配置
/*

配置系统时钟
*/


//void sysclockfuzhi(void)
//{
//	
//AHB_HXTAL72M(C8M);                   //C8M 为HXTAL 晶振为8M ,AHB输出72M的时钟    
//	
//}

/*
abi：用于外设时钟的开启
input：rcu_AF
OUTPUT:对应外设时钟的开启
time0：2022年7月8日16点04分
*/


void rcu_periph_interface_clock_enable(void)
{
RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
}






