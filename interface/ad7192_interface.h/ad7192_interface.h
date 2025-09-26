#ifndef AD7192_INTERFACE_H
#define AD7192_INTERFACE_H


/////////////CS   PC4的控制作用
#define	 cs_gpio          GPIOC
#define	 cs_mode          GPIO_MODE_OUT_PP 
#define	 cs_pin_define    GPIO_PIN_4 
#define	 cs_remap         GPIO_SWJ_NONJTRST_REMAP          //随意取值
#define	 cs_selfuyong     DISABLE
#define	 cs_speed         GPIO_OSPEED_50MHZ
/////////////////////////SCK，miso，mosi      PB3配置
#define	 sck_miso_mosi_gpio          GPIOB
#define	 sck_miso_mosi_mode          GPIO_MODE_AF_PP 
#define	 sck_miso_mosi_pin_define    GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
#define	 sck_miso_mosi_remap         GPIO_SPI0_REMAP          //随意取值
#define	 sck_miso_mosi_selfuyong     ENABLE
#define	 sck_miso_mosi_speed         GPIO_OSPEED_50MHZ
///////////////////////////
 #define      ADC_clock_polarity_phase      SPI_CK_PL_HIGH_PH_2EDGE      //SPI_CK_PL_HIGH_PH_2EDGE     
 #define      ADC_device_mode               SPI_MASTER                   //主机模式
 #define      ADC_endian                    SPI_ENDIAN_MSB               //高位先行，MSB
 #define      ADC_frame_size                SPI_FRAMESIZE_8BIT           //一次传输8位
 #define      ADC_nss                       SPI_NSS_HARD                 //硬件控制
 #define      ADC_prescale                  SPI_PSC_32                   //32位分频
 #define      ADC_trans_mode                SPI_TRANSMODE_FULLDUPLEX     //双线双向
 #define      spiX_periph                    SPI0
 

///////////////模式选择

/* 单次转换|使能状态传输|外部时钟|sinc4滤波器|禁用奇偶校验|时钟不分频|禁用单周期转换|禁用60Hz陷波|128 */
#define  ad7192_mode    MODE_SING|DAT_STA_EN|EXT_XTAL|SINC_4|ENPAR_DIS|CLK_DIV_DIS|SINGLECYCLE_DIS|REJ60_DIS|1023
#define  ad7192_cfg     CHOP_DIS|REF_IN1|AIN1_AIN2|BURN_DIS|REFDET_DIS|BUF_DIS|UB_BI|GAIN_1
/*禁用斩波|外部基准电压1|12差分通道(单)|禁用激励电流|禁用基准电压检测|禁用模拟输入缓冲|双极性模式|增益为128 */
  






#endif



