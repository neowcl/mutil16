#ifndef   _AD7689_INTERFACE_H
#define   _AD7689_INTERFACE_H
#include  "gd32f10x.h"
#include  "gpio_init.h"

#define   CFG_refresh      (uint16_t)((uint16_t)  0x01U<<16)
#define   CFG_keep         (uint16_t)((uint16_t)  0x00U<<16)
#define   INCC_single3     (uint16_t)((uint16_t)  0x07U<<13)
#define   INCC_single2     (uint16_t)((uint16_t)  0x06U<<13)
#define   INCC_single1     (uint16_t)((uint16_t)  0x04U<<13)
#define   IN0              (uint16_t)((uint16_t)  0x00U<<10)
#define   IN1              (uint16_t)((uint16_t)  0x01U<<10)
#define   IN2              (uint16_t)((uint16_t)  0x02U<<10)
#define   IN3              (uint16_t)((uint16_t)  0x03U<<10)
#define   IN4              (uint16_t)((uint16_t)  0x04U<<10)
#define   IN5              (uint16_t)((uint16_t)  0x05U<<10)
#define   IN6              (uint16_t)((uint16_t)  0x06U<<10)
#define   IN7              (uint16_t)((uint16_t)  0x07U<<10)
#define   BW_ALL           (uint16_t)((uint16_t)  0x01U<<9)
#define   BW_1_4           (uint16_t)((uint16_t)  0x00U<<9)
#define   REF_OUT_NOTEM    (uint16_t)((uint16_t)  0x06U<<6)
#define   SEQ_disable      (uint16_t)((uint16_t)  0x00U<<3)
#define   RB               (uint16_t)((uint16_t)  0x01U<<2)


  #define       PART1_CS_GPIO           GPIOA
	#define       PART1_CS_MODE           GPIO_MODE_OUT_PP
	#define       PART1_CS_PIN            GPIO_PIN_4
	#define       PART1_CS_REMAP          1
	#define       PART1_CS_selfuyong      DISABLE
	#define       PART1_CS_speed          GPIO_OSPEED_50MHZ


  #define       PART1_sck_miso_mosi_GPIO           GPIOB
	#define       PART1_sck_miso_mosi_MODE           GPIO_MODE_OUT_PP
	#define       PART1_sck_miso_mosi_PIN            GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
	#define       PART1_sck_miso_mosi_REMAP          GPIO_SPI0_REMAP
	#define       PART1_sck_miso_mosi_selfuyong      ENABLE
	#define       PART1_sck_miso_mosi_speed          GPIO_OSPEED_50MHZ

	#define   PART1_SPI_clock_polarity_phase         SPI_CK_PL_LOW_PH_1EDGE
	#define   PART1_SPI_device_mode                  SPI_MASTER
	#define   PART1_SPI_endian                       SPI_ENDIAN_MSB
	#define   PART1_SPI_rame_size                    SPI_FRAMESIZE_8BIT  
	#define   PART1_SPI_nss                          SPI_NSS_HARD 
	#define   PART1_SPI_prescale                     SPI_PSC_32 
	#define   PART1_SPI_trans_mode                   SPI_TRANSMODE_FULLDUPLEX
  #define  part1_spiX_periph                       SPI0


void ad7689_converstion_getdata_inter(uint16_t INx_choose,uint16_t *databuffer);
void ad7689_part1_converstion_start(void);
void ad7689_PART1_init_inter(void);
void  CFG_IN0_IN7_FUZHI(void);




#endif


