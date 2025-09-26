#include "ad7192_interface.h"
#include "./ad7192_drive/ad7192_drive.h"
#include "./gpio_init/gpio_init.h" 
#include "./spi_drive/spi_drive.h"

#ifdef    _AD7192

static gpio_drive_init            gpio_spi_cs={0,0,0,0,0,0};
static gpio_drive_init            gpio_spi_sck_miso_mosi={0,0,0,0,0,0};
static spi_parameter_struct       SPI_InitStructure={0,0,0,0,0,0,0};
void ad7192_drive_init_inter(void)
{

	//定义  控制引脚  PC4
	gpio_spi_cs.gpio=cs_gpio;
	gpio_spi_cs.mode=cs_mode;
	gpio_spi_cs.pin=cs_pin_define;
	gpio_spi_cs.remap=cs_remap;
	gpio_spi_cs.selfuyong=cs_selfuyong;
	gpio_spi_cs.speed=cs_speed;
	
	
	//定义PB3,PB4,PB5  sck,MISO,MOSI时钟输出
	gpio_spi_sck_miso_mosi.gpio=sck_miso_mosi_gpio;
	gpio_spi_sck_miso_mosi.mode=sck_miso_mosi_mode;
	gpio_spi_sck_miso_mosi.pin=sck_miso_mosi_pin_define;
	gpio_spi_sck_miso_mosi.remap=sck_miso_mosi_remap;
	gpio_spi_sck_miso_mosi.selfuyong=sck_miso_mosi_selfuyong;
	gpio_spi_sck_miso_mosi.speed=sck_miso_mosi_speed;
	
	
	/* SPI 模式配置 */
  SPI_InitStructure.clock_polarity_phase=ADC_clock_polarity_phase;    
	SPI_InitStructure.device_mode=ADC_device_mode;
	SPI_InitStructure.endian=ADC_endian;
	SPI_InitStructure.frame_size=ADC_frame_size;
	SPI_InitStructure.nss=ADC_nss;
	SPI_InitStructure.prescale=ADC_prescale;
	SPI_InitStructure.trans_mode=ADC_trans_mode;       //不用CRC位
,  ad7192_drive_init_per(spiX_periph,&gpio_spi_cs,&gpio_spi_sck_miso_mosi,&SPI_InitStructure);
  gpio_bit_reset_drive(cs_gpio,cs_pin_define);
  spi_enable_drive(spiX_periph);
}



void continuous_conversion_voltage(void)
{
  uint32_t ad_data = 0;
  float v = 0.0;
  
  printf("野火 AD9172 4 路连续转换读电压实验\r\n");
  
  /* 读 AD7192 寄存器 */
  ReadFromAD7192ViaSPI(spiX_periph,REG_COM_STA, 8, AD7192Registers, REG_COM_STA);
  for(int i=0; i < 8; i++)
  {
    printf("AD7192Register[%d] = 0x%06X \r\n", i+REG_COM_STA,AD7192Registers[i+REG_COM_STA]);
  }
  
  ad7192_mode_cfg_reg(spiX_periph,ad7192_mode,ad7192_cfg);    // 配置模式寄存器和配置寄存器

  /* 校准 */
  AD7192InternalZeroScaleCalibration();
  AD7192InternalFullScaleCalibration();	
  
  AD7192StartContinuousConvertion(AIN1_COM|AIN2_COM|AIN3_COM|AIN4_COM);    // 启动连续转换
  
	while(1)
	{
    ad_data = AD7192ReadConvertingData();
    
    switch(ad_data & 7)
    {
      case 4:
        v = ((ad_data >> 8) / 8388608.0 - 1)*3.3;
        printf("AIN1_COM = %fV\n", v);
      break;
      
      case 5:
        v = ((ad_data >> 8) / 8388608.0 - 1)*3.3;
        printf("AIN2_COM = %fV\n", v);
      break;
      
      case 6:
        v = ((ad_data >> 8) / 8388608.0 - 1)*3.3;
        printf("AIN3_COM = %fV\n", v);
      break;
      
      case 7:
        v = ((ad_data >> 8) / 8388608.0 - 1)*3.3;
        printf("AIN4_COM = %fV\n", v);
      break;
    }
	}
}


#endif





