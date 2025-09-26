#include "./spi_drive/spi_drive.h"
#include  "stdio_mcu_drive.h"
#include "./GPIO_Init/GPIO_Init.h" 
#include "systick.h"
#include  "timer_drive.h"
extern uint32_t Timcounter;     //定时器标志 决定多久亮一次



void SPI_Soft_SendData_Drive(unsigned char* WriteBuffer,uint8_t Number,gpio_drive_init* MOSI,gpio_drive_init* CLK,gpio_drive_init* NSS)
{
	unsigned char i;   
  gpio_bit_reset_drive(CLK->gpio,CLK->pin);
  	delay_1us(1);
	  gpio_bit_set_drive(CLK->gpio,CLK->pin);
  	delay_1us(1);
	  gpio_bit_reset_drive(NSS->gpio,NSS->pin); 
  	delay_1us(1);
    gpio_bit_reset_drive(CLK->gpio,CLK->pin);


	for(i = 0;i < Number; i++)
	{
	SOFT_SPI_RW_MODE0(WriteBuffer[i], MOSI,CLK,NSS);
	}
	delay_1us(1);				
  gpio_bit_reset_drive(CLK->gpio,CLK->pin);
		delay_1us(1);				
	gpio_bit_set_drive(NSS->gpio,NSS->pin); 
	delay_1us(1);				

	
	

}


/* CPOL = 0, CPHA = 0, MSB first */
void SOFT_SPI_RW_MODE0( uint8_t write_dat,gpio_drive_init* MOSI,gpio_drive_init* CLK,gpio_drive_init* NSS)
{
    uint8_t ii; 
    for(ii= 0;ii<8;ii++)
    {
				gpio_bit_reset_drive(CLK->gpio,CLK->pin); 
        if( write_dat & 0x80 )
				{
        gpio_bit_set_drive(MOSI->gpio,MOSI->pin);
				}
        else 
				{					
        gpio_bit_reset_drive(MOSI->gpio,MOSI->pin);
				}
         delay_1us(1);
        write_dat <<= 1;
        gpio_bit_set_drive(CLK->gpio,CLK->pin);
				delay_1us(1);
        gpio_bit_reset_drive(CLK->gpio,CLK->pin);
        delay_1us(1);				
    }
}




/* CPOL=0，CPHA=1, MSB first */
void SOFT_SPI_RW_MODE1(uint8_t byte,gpio_drive_init* MOSI,gpio_drive_init* CLK) 
{
    uint8_t i;
 
	for(i=0;i<8;i++)     // 循环8次
	{
		gpio_bit_set_drive(CLK->gpio,CLK->pin);     //拉高时钟
		if(byte&0x80)
        {
			gpio_bit_set_drive(MOSI->gpio,MOSI->pin);  //若最到位为高，则输出高
        }
		else      
		{
			gpio_bit_reset_drive(MOSI->gpio,MOSI->pin);;   //若最到位为低，则输出低
		}
		byte <<= 1;     // 低一位移位到最高位
		delay_1us(1);
		gpio_bit_set_drive(CLK->gpio,CLK->pin);     //拉低时钟
	   delay_1us(1);
	}
}
 
/* CPOL=1，CPHA=0, MSB first */
void SOFT_SPI_RW_MODE2(uint8_t byte,gpio_drive_init* MOSI,gpio_drive_init* CLK)  
{
    uint8_t i;
 
	for(i=0;i<8;i++)     // 循环8次
	{
		if(byte&0x80)
        {
			gpio_bit_set_drive(MOSI->gpio,MOSI->pin);  //若最到位为高，则输出高
        }
		else      
		{
			gpio_bit_reset_drive(MOSI->gpio,MOSI->pin);   //若最到位为低，则输出低
		}
		byte <<= 1;     // 低一位移位到最高位
		delay_1us(1);
		gpio_bit_reset_drive(CLK->gpio,CLK->pin);     //拉低时钟;     //拉低时钟
		delay_1us(1);
		gpio_bit_set_drive(CLK->gpio,CLK->pin);     //拉低时钟;     //拉高时钟
		
	}
}
 
 
/* CPOL = 1, CPHA = 1, MSB first */
void SOFT_SPI_RW_MODE3( uint8_t write_dat,gpio_drive_init* MOSI,gpio_drive_init* CLK)
{
    uint8_t i;
    for( i = 0; i < 8; i++ )
    {
		gpio_bit_reset_drive(CLK->gpio,CLK->pin);     //拉低时钟;     //拉低时钟
        if( write_dat & 0x80 )
			gpio_bit_set_drive(MOSI->gpio,MOSI->pin);  //若最到位为高，则输出高
        else                    
			gpio_bit_reset_drive(MOSI->gpio,MOSI->pin);  //若最到位为高，则输出高
        write_dat <<= 1;
        delay_1us(1);	
		gpio_bit_set_drive(CLK->gpio,CLK->pin);     //拉低时钟;     //拉低时钟
		delay_1us(1);
    }
}











/*******************************************************************************
* 函数名  : spi_drive_init
* 描述    : SPI初始化配置(spiX, SPI的配置)
* 输入    : spiX, SPI的配置
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void spi_drive_init(uint32_t spi_periph,spiX_parameter_struct* spi_mcu_drive_par)
{
	
spi_init_mcu_drive(spi_periph,spi_mcu_drive_par);	
	
}

/*******************************************************************************
* 函数名  : SPI_TransmitReceive_drive
* 描述    : spi接收数据，底层驱动(写入数字，读取数组 ，读取字节，等待时间)
* 输入    : 写入数字，读取数组 ，读取字节，等待时间
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void SPI_TransmitReceive_drive(uint32_t spix,unsigned char* WriteBuffer, unsigned char *ReadBuffer\
	, unsigned char Number_16bit,uint32_t  SPITimeout)
{
	unsigned char i;
	uint32_t  Timeout = SPITimeout;          
	for(i = 0;i < Number_16bit; i++)
	{
			
			while (spi_i2s_flag_get_drive(spix , SPI_FLAG_TBE) == RESET)
			{
			 }

			/* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
			spi_i2s_data_transmit_drive(spix , WriteBuffer[i]);

			SPITimeout = Timeout;
			/* 等待接收缓冲区非空，RXNE事件 */
			while (spi_i2s_flag_get_drive(spix , SPI_FLAG_RBNE) == RESET)     //表示有数据进入，接受寄存器不为空
			{
		  }
			
			/* 读取数据寄存器，获取接收缓冲区数据 */
			ReadBuffer[i] = spi_i2s_data_receive_drive(spix);             //这个数据包含了什么？
	}

}

/*******************************************************************************
* 函数名  : SPI_SendData_drive
* 描述    : spi数据，底层驱动(写入数字，读取数组 ，读取字节，等待时间)
* 输入    : 写入数字，读取数组 ，读取字节，等待时间
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void SPI_SendData_drive(uint32_t spix,unsigned char* WriteBuffer,unsigned char Number,uint32_t  SPITimeout)
{
	unsigned char i;      	
	for(i = 0;i < Number; i++)
	{
			
			while (spi_i2s_flag_get_drive(spix , SPI_FLAG_TBE) == RESET)
			{
			}
			/* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
			spi_i2s_data_transmit_drive(spix , WriteBuffer[i]);
	}
}






/*******************************************************************************
* 函数名  : SPI_TIMEOUT_UserCallback
* 描述    : 超出时间反馈(错误代码)
* 输入    : 错误代码数
* 输出    : 串口输出错误代码数
* 返回值  : 0
* 说明    : 如果spi接收或者发送迟滞，无法正常运行，则错误
*******************************************************************************/


