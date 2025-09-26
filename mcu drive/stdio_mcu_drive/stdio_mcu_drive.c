#include "stdio_mcu_drive.h"
#include "usart_drive.h"
#include "spi_drive.h"


extern uint8_t stdio_c_mode_switch=0;



/*******************************************************************************
* 函数名  : fputc
* 描述    : 可使用printf表示发送
* 输入    : 主要是字符串
* 输出    : 无
* 返回值  : 无
* 说明    : ///重定向c库函数printf到串口，重定向后可使用printf函数
******************************************************************************/

int fputc(int ch, FILE *f)
{
	

	switch(stdio_c_mode_switch)
	{
		case(USART0_transmission):
	          	{
							while (usartX_flag_get(USART0, USART_FLAG_TC) == RESET)
							{
							};
		          usart_data_transmit_drive(USART0, (uint8_t) ch);
		         while (usartX_flag_get(USART0, USART_FLAG_TC) == RESET);		
							    break;			  
	            }
	  case(USART1_transmission):
	          	{
							while (usartX_flag_get(USART1, USART_FLAG_TC) == RESET)
							{
							};	
		          usart_data_transmit_drive(USART1, (uint8_t) ch);
		         while (usartX_flag_get(USART1, USART_FLAG_TC) == RESET);		
			       break;
	            }
		case(USART2_transmission):
	          	{
		          usart_data_transmit_drive(USART2, (uint8_t) ch);
		         while (usartX_flag_get(USART2, USART_FLAG_TC) == RESET);		
			       break;
	            }
		case(SPI0_transmission):
	          	{
							while (spi_i2s_flag_get_drive(SPI0 ,SPI_FLAG_TBE) == RESET);		
							spi_i2s_data_transmit_drive(SPI0,(uint8_t) ch);	
							while (spi_i2s_flag_get_drive(SPI0,SPI_FLAG_TBE) == RESET)
							{
							};	
			        break;														
	            }
		case(SPI1_transmission):
	          	{
	      while (spi_i2s_flag_get_drive(SPI1 ,SPI_FLAG_TBE) == RESET);		
							spi_i2s_data_transmit_drive(SPI1,(uint8_t) ch);	
							while (spi_i2s_flag_get_drive(SPI1,SPI_FLAG_TBE) == RESET)
							{
							};	
			        break;
	            }
	  case(SPI2_transmission):
	          	{
	           while (spi_i2s_flag_get_drive(SPI2 ,SPI_FLAG_TBE) == RESET);		
							spi_i2s_data_transmit_drive(SPI2,(uint8_t) ch);	
							while (spi_i2s_flag_get_drive(SPI2,SPI_FLAG_TBE) == RESET)
							{
							};	
			        break;
	            }
				
		
  }
			return (ch);	
}






///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{

	uint16_t   data_receive=0;
		switch(stdio_c_mode_switch)
		{
		case(USART0_transmission):
		{
		while (usartX_flag_get(USART0 , USART_FLAG_RBNE) == RESET);
		data_receive=usartX_data_receive(USART0);
			break;
		}
		case(USART1_transmission):
		{
		while (usartX_flag_get(USART1 , USART_FLAG_RBNE) == RESET);
		data_receive=usartX_data_receive(USART1);
						break;

		}
			case(USART2_transmission):
		{
		while (usartX_flag_get(USART2 , USART_FLAG_RBNE) == RESET);
    data_receive=usartX_data_receive(USART2);
						break;

		}
			case(SPI0_transmission):
		{
		while (spi_i2s_flag_get_drive(SPI0 , SPI_FLAG_RBNE) == RESET)     //表示有数据进入，接受寄存器不为空
    data_receive=spi_i2s_data_receive_drive(SPI0);             //这个数据包含了什么？
					break;

		}
			case(SPI1_transmission):
		{
		while (spi_i2s_flag_get_drive(SPI1 , SPI_FLAG_RBNE) == RESET)     //表示有数据进入，接受寄存器不为空
    data_receive=spi_i2s_data_receive_drive(SPI1);             //这个数据包含了什么？
					break;

		}
		
			case(SPI2_transmission):
		{
		while (spi_i2s_flag_get_drive(SPI2 , SPI_FLAG_RBNE) == RESET)     //表示有数据进入，接受寄存器不为空
    data_receive=spi_i2s_data_receive_drive(SPI2);             //这个数据包含了什么？
					break;

		}
		}
		return data_receive;
}























