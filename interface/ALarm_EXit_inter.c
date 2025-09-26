#include "ALarm_EXit_inter.h" 
#include "Bq7695202_drive.h"
#include "./GPIO_Init/GPIO_Init.h"
#include "./interrupt/interrupt.h"
#include "Schedule.h"
#include "Usart_interface.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
//Battery_Status_Str  BatSta;
/**
  * @brief  PB2下降沿中断初始化
  * @param  无
  * @retval 无
  */
void Alarm_Exti_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    // 开启 GPIOB 和 AFIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // 配置 PB1 为上拉输入（默认高电平，接地时变低）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 映射 PB1 到 EXTI1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    // 配置 EXTI1 为下降沿触发
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    // 配置 NVIC
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}


void Period_Manage_Battery_Sta(void)
{
	uint8_t Regis_Data1[4];
	uint8_t Regis_Data2[4];
	if(BQ769x2_SetRegister(CCGain,0x00,0)==0)
	{
	}
	if(I2C_ReadData(0x40,Regis_Data1,4)==0)   //读取32位，后两位为长度和checksum
	{
	}
	if(BQ769x2_SetRegister(CapacityGain,0x00,0)==0)
	{
	}
	if(I2C_ReadData(0x40,Regis_Data2,4)==0)   //读取32位，后两位为长度和checksum
	{
	}
	
	BQ769x2_ReadAlarmStatus();   //进行读取具体的位
  if(Battery_Sta_G.Alarm_Sta_bits.ADSCAN==1)
	{
		//printf   //进行报错
	}
	Bq76952_Interrupt_processing();
}


void Bq76952_Interrupt_processing(void)
{ 
	uint16_t   Alarm_Manage=0;
	BQ769x2_ReadAlarmStatus();   //进行读取具体的位  
  //Status_Tempt=	BatSta.Alarm_Sta;
	if((Battery_Sta_G.Alarm_Sta&0xFFFF)!=0x0000)
	{
		 //ADSCAN中断触发
		if(Battery_Sta_G.Alarm_Sta_bits.ADSCAN==1)
		{
			
			//进行采集电压数据
			BQ769x2_ReadAllVoltages();
			Alarm_Manage=(0x0001)<<1;
			DirectCommands(AlarmStatus,Alarm_Manage, W,2);  
			//检查是否清理完成
			BQ769x2_ReadAlarmStatus();
			if(Battery_Sta_G.Alarm_Sta_bits.ADSCAN==1)   //错误处理
			{
				//上报错误
			}
		}
		if(Battery_Sta_G.Alarm_Sta_bits.FULLSCAN==1)
		{
			//采集电池电压
			BQ769x2_ReadAllVoltages();
			//采集温度数据
			BQ769x2_ReadALLTemperature();
			//采集电流数据
			BQ769x2_ReadCurrent();
			//比较告警位
			Bat_Bit_Flag_Set();
			//清除FULLSCAN中断位
			Alarm_Manage=(0x0001)<<7;
			DirectCommands(AlarmStatus,Alarm_Manage, W,2);
			//读取alarm位
			BQ769x2_ReadAlarmStatus();
			if(Battery_Sta_G.Alarm_Sta_bits.FULLSCAN==1)   //错误处理
			{
				//上报错误
			}
		}
		//15-11位置位
		if((Battery_Sta_G.Alarm_Sta&(0xF800))!=0x0000)
		{
			//采集电池异常状态位
			BQ769x2_ReadSafetyStatus();
			BQ769x2_ReadPFStatus();
			//亮LED灯
			GPIO_SetBits(GPIOB,GPIO_Pin_13);	
			//清除15-11位置位中断位
			Alarm_Manage=0xF800;
			DirectCommands(AlarmStatus,Alarm_Manage, W,2);
			//读取alarm位
			BQ769x2_ReadAlarmStatus();
			if(Battery_Sta_G.Alarm_Sta_bits.FULLSCAN==1)
			{
				//上报错误
			}
		}
		if(Battery_Sta_G.Alarm_Sta_bits.CB==1)
		{
			//读取CB序号
			Subcommands(CB_ACTIVE_CELLS, 0 ,R);
			BatData.CB_Cells_Index=RX_Ser_Byte[1]*256 + RX_Ser_Byte[0];
			//赋位告警信息
			AlarmData.Cell_Balance1_8=(uint8_t)((BatData.CB_Cells_Index>>8)&(0x00FF));
			AlarmData.Cell_Balance9_16=(uint8_t)((BatData.CB_Cells_Index)&(0x00FF));

			//清除CB位
			Alarm_Manage=(0x0001)<<2;
			DirectCommands(AlarmStatus,Alarm_Manage, W,2);
			//读取alarm位
			BQ769x2_ReadAlarmStatus();
			if(Battery_Sta_G.Alarm_Sta_bits.CB==1)
			{
				//上报错误
			}
		}
	}
}















