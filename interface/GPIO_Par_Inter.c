#include "GPIO_Par_Inter.h"
#include "GPIO_Init.h"
#define F103_GPIO_NUMBER      37 
#define F103_GPIO_Ser         5

static gpio_drive_init GPIO_Disp[F103_GPIO_NUMBER]=
{
	{                      //PA0   
		B_VOL,              //采集最高串电压的总电压大小,采用ADC的模式
		GPIO_Pin_0,
		GPIO_Mode_AIN,    //模拟输入
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	
	{//PA1
		BL_SLEEP,     //低功耗控制引脚，低电平有效，内置上拉电阻
		GPIO_Pin_1,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PA2
		BL_MODE,
		GPIO_Pin_2,//  AT 透传功能切换引脚  0：AT 模式 1：透传模式
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PA3
		SOC_LED1,       //采集电压:过流电压,采样电阻的电压;
		GPIO_Pin_3,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PA4
		SOC_LED2 ,
		GPIO_Pin_4,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	
	{//PA5
		SOC_LED3 ,    //唤醒CPU的方法,通过管脚控制????
		GPIO_Pin_5,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PA6
		SOC_LED4 ,     //采集ADC.can的电压
		GPIO_Pin_6,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PA7
		SOC_LED5 ,
		GPIO_Pin_7,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PA8
		RS485_Contr_G,
		GPIO_Pin_8,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PA9
		NONE_IO_A,       
		GPIO_Pin_9,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	
	{//PA10
		NONE_IO_A,    
		GPIO_Pin_10,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PA11
		CANO_RX,
		GPIO_Pin_11,
		GPIO_Mode_IPU,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PA12
		CANO_TX,
		GPIO_Pin_12,
		GPIO_Mode_AF_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	

	{//PA13
		DIO_SWD,
		GPIO_Pin_13,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PA14
		CLK_SWD,
		GPIO_Pin_14,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PA15
		LED_RUN ,
		GPIO_Pin_15,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	
	{//PB0 
		CHG_CHK,        //ADC的作用
		GPIO_Pin_0,
		GPIO_Mode_AIN,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PB1
		Alert_G ,        //ADC的作用
		GPIO_Pin_1,
		GPIO_Mode_IPU,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PB2
		NONE_IO_B,     
		GPIO_Pin_2,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PB3
		RTC_SCL,      //iic接口
		GPIO_Pin_3,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	{//PB4
		RTC_SDA ,   //IIc接口
		GPIO_Pin_4,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
 {//PB5
		EE_WP ,
		GPIO_Pin_5,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
 {//PB6
		TX_485 ,
		GPIO_Pin_6,
		GPIO_Mode_AF_PP,
		GPIO_Speed_50MHz,
		ENABLE ,
		GPIO_Remap_USART1,
	},
 {//PB7
		RX_485 ,
		GPIO_Pin_7,
	  GPIO_Mode_IPU,
		GPIO_Speed_50MHz,
		ENABLE ,
		GPIO_Remap_USART1,
	},
  {//PB8
		NONE_IO_B ,
		GPIO_Pin_8,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
	  {//PB9
		NONE_IO_B ,
		GPIO_Pin_9,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
 {//PB10
		AFE_SCL,
		GPIO_Pin_10,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PB11
		AFE_SDA,
		GPIO_Pin_11,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PB12
		ALRM,
		GPIO_Pin_12,
		GPIO_Mode_IPU, 
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PB13
		PRO_EN,     //无用
		GPIO_Pin_13,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PB14
		NONE_IO_B,
		GPIO_Pin_14,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PB15
		NONE_IO_B,
		GPIO_Pin_15,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PC13
		NONE_IO_C ,
		GPIO_Pin_13,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PC14
		NONE_IO_C ,
		GPIO_Pin_14, 
		GPIO_Mode_Out_PP,  
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PC15
		NONE_IO_C ,
		GPIO_Pin_15,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PD0
		NONE_IO_D ,
		GPIO_Pin_0,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
{//PD1
		NONE_IO_D,
		GPIO_Pin_1,
		GPIO_Mode_Out_PP,
		GPIO_Speed_50MHz,
		DISABLE,
		GPIO_Remap_SWJ_Disable,
	},
 
	

};

void Gpio_Set_mode(void)
{
//	uint16_t Gpio_Number=0;
//	for(Gpio_Number=0;Gpio_Number<=(F103_GPIO_NUMBER-1);Gpio_Number++)
//	{ 
//		gpio_mode_init(&GPIO_Disp[Gpio_Number]);
//	}
}



void GPIO_Set(void)
{
	 GPIO_InitTypeDef   GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 复用开漏输出，进行输出信号或者信息读取
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 复用开漏输出，进行输出信号或者信息读取
   GPIO_Init(GPIOA, &GPIO_InitStructure);
 	 GPIO_SetBits(GPIOA,GPIO_Pin_7);
	
}
static  uint8_t kk=0;
void LED_Do(void)
{
	kk=~kk;
	if(kk==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14);
	}
	
}



















