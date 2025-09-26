/*!
    \file    gd32f10x_it.c
    \brief   interrupt service routines

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f10x_it.h"
#include "systick.h"
#include "Can_drive.h"
#include "can_interface.h"
#include  "can_api.h"
#include "Memory_Par_Inter.h"
#include "./TIMER_interface/TIMER_interface.h"

#include "./gpio_init/gpio_init.h" 
#include "ALarm_EXit_inter.h"
extern uint8_t transfersize;
extern uint8_t receivesize;
extern  uint8_t txcount; 
extern  uint16_t rxcount; 
extern uint8_t receiver_buffer[32];
extern uint8_t transmitter_buffer[];

extern FlagStatus receive_flag;   //判断数据是否有接收到
extern can_receive_MSG_struct  can0_receive_MSG;//接收数据结构体


/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    delay_decrement();
}


uint8_t IntFlag;
void EXTI1_IRQHandler(void)
{
		
}

void EXTI0_IRQHandler(void)
{	

}



 
void TIMER1_IRQHandler(void)
{
	/*
	if(ucTimer0Cnt==0)
	{
		ucTimer0Cnt=1;
 GPIO_WORK_TIME(0,1, GPIOA, GPIO_PIN_3);
	}
	else{
	ucTimer0Cnt=0;
 GPIO_WORK_TIME(1,0, GPIOA, GPIO_PIN_3);
	}
	*/
	
	
	if(++ucTimer0Cnt>=50)
	{
		bTimerFlg=TRUE;
		ucTimer0Cnt=0;
	}
	
	
timer_timer_20ms_flag_clear();

}




extern uint8_t transfersize;
extern uint8_t receivesize;
extern  uint8_t txcount; 
extern  uint16_t rxcount; 
extern uint8_t receiver_buffer[32];
extern uint8_t transmitter_buffer[];
void USART0_IRQHandler(void)
{	 		
	
}




void CAN0_RX1_IRQHandler(void)
{


}



void EXTI10_15_IRQHandler(void)
{

	if(Alarm_input_bit_get()==RESET)
	{
		bAFEFlg=TRUE;   //进行ALARM读取标志位置位
	}
Alarm_interrupt_flag();

}

























