#include "ad7689_interface.h"
#include  "ad7689_drive.h"
#include  "spi_drive.h"
extern unsigned char WriteBuf[2]; //定义有2个元素的写缓存数组，每个数组元素占1个字节。
extern unsigned char ReadBuf[2];  //定义有2个元素的读缓存数组，每个数组元素占1个字节。
static   gpio_drive_init          ad7689_PART1_CS={0,0,0,0,0,0};
static	 gpio_drive_init          ad7689_PART1_sck_miso_mosi={0,0,0,0,0,0};
static   spi_parameter_struct     ad7689_PART1_SPI_PAR={0,0,0,0,0,0,0};


static uint16_t CFGIN0_IN7[8]={0,0,0,0,0,0,0,0};//要读或写AD7192Registers[8]
uint8_t    medium_1byte[2]={0,0};
uint8_t    read_data_medium[2]={0,0};           //用于存放8位数据

/*******************************************************************************
* 函数名  : CFG_IN0_IN7_FUZHI
* 描述    : 由于不采用自动序列的读取，所以要对每个数据进行赋值
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void  CFG_IN0_IN7_FUZHI(void)
{
	uint8_t i;
	for(i=0;i<=7;i++)
	{
		switch(i)
		{
			case(0):CFGIN0_IN7[0]=CFG_refresh|INCC_single1|IN0|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			case(1):CFGIN0_IN7[1]=CFG_refresh|INCC_single1|IN1|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			case(2):CFGIN0_IN7[2]=CFG_refresh|INCC_single1|IN2|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			case(3):CFGIN0_IN7[3]=CFG_refresh|INCC_single1|IN3|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			case(4):CFGIN0_IN7[4]=CFG_refresh|INCC_single1|IN4|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			case(5):CFGIN0_IN7[5]=CFG_refresh|INCC_single1|IN5|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			case(6):CFGIN0_IN7[6]=CFG_refresh|INCC_single1|IN6|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			case(7):CFGIN0_IN7[7]=CFG_refresh|INCC_single1|IN7|BW_ALL|REF_OUT_NOTEM|SEQ_disable;
				break;
			default:
				break;
		
	}
}
}



/*******************************************************************************
* 函数名  : ad7689_PART1_init_inter
* 描述    : 对ad7689spi进行端口配置，以及spi0配置
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void ad7689_PART1_init_inter(void)
{
	
	
	ad7689_PART1_CS.gpio=PART1_CS_GPIO;
	ad7689_PART1_CS.mode=PART1_CS_MODE;
	ad7689_PART1_CS.pin=PART1_CS_PIN;
	ad7689_PART1_CS.remap=PART1_CS_REMAP;
	ad7689_PART1_CS.selfuyong=PART1_CS_selfuyong;
	ad7689_PART1_CS.speed=PART1_CS_speed;
	
	
	ad7689_PART1_sck_miso_mosi.mode=PART1_sck_miso_mosi_MODE;
	ad7689_PART1_sck_miso_mosi.pin=PART1_sck_miso_mosi_PIN;
	ad7689_PART1_sck_miso_mosi.remap=PART1_sck_miso_mosi_REMAP;
	ad7689_PART1_sck_miso_mosi.selfuyong=PART1_sck_miso_mosi_selfuyong;
	ad7689_PART1_sck_miso_mosi.speed=PART1_sck_miso_mosi_speed;
	
	ad7689_PART1_SPI_PAR.clock_polarity_phase=PART1_SPI_clock_polarity_phase;
	ad7689_PART1_SPI_PAR.device_mode=PART1_SPI_device_mode;
	ad7689_PART1_SPI_PAR.endian=PART1_SPI_endian;
	ad7689_PART1_SPI_PAR.frame_size=PART1_SPI_rame_size;
	ad7689_PART1_SPI_PAR.nss=PART1_SPI_nss;
	ad7689_PART1_SPI_PAR.prescale=PART1_SPI_prescale;
	ad7689_PART1_SPI_PAR.trans_mode=PART1_SPI_trans_mode;
	
	ad7689_init_per(part1_spiX_periph,&ad7689_PART1_CS,\
	&ad7689_PART1_sck_miso_mosi,&ad7689_PART1_SPI_PAR);
  gpio_bit_reset_drive(part1_spiX_periph,PART1_CS_PIN);
  spi_enable_drive(part1_spiX_periph);
}



/*
@brief :先进行配置，进行两次的哑输入，扔掉两次无用的数据
*/
void ad7689_part1_converstion_start(void)
{
medium_1byte[0]= ((CFGIN0_IN7[0]>>8)&0xff);
medium_1byte[1]=(CFGIN0_IN7[0]&0xff);	
ad7689_converstion_start(&ad7689_PART1_CS,part1_spiX_periph,\
	medium_1byte,read_data_medium);	
}


void ad7689_converstion_getdata_inter(uint16_t INx_choose,uint16_t *databuffer)
{
	INx_choose=((INx_choose>>10)&0xff);
	switch(INx_choose)
	{
		case(0X00):
		                 medium_1byte[0]= ((CFGIN0_IN7[0]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[0]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
				             break;
		case(0X01):
		                 medium_1byte[0]= ((CFGIN0_IN7[1]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[1]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
				             break;
		case(0X02):
		                 medium_1byte[0]= ((CFGIN0_IN7[2]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[2]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
				             break;
		case(0X03):
		                 medium_1byte[0]= ((CFGIN0_IN7[3]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[3]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
				             break;
		case(0X04):
		                 medium_1byte[0]= ((CFGIN0_IN7[4]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[4]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
				             break;
		case(0X05):
		                 medium_1byte[0]= ((CFGIN0_IN7[5]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[5]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
				             break;
		case(0X06):
		                 medium_1byte[0]= ((CFGIN0_IN7[6]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[6]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
				             break;
		case(0X07):
		                 medium_1byte[0]= ((CFGIN0_IN7[7]>>8)&0xff);
                     medium_1byte[1]=(CFGIN0_IN7[7]&0xff);	
	                   ad7689_converstion_getdata(&ad7689_PART1_CS,part1_spiX_periph,\
		                 medium_1byte,read_data_medium);
		                 break;
		default :
			               break;
	
	}
databuffer[INx_choose]=(((read_data_medium[0])<<8)&(read_data_medium[1]));
}










