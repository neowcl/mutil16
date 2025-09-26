#include "./chushihua/chushihua.h"    //底层驱动在LED_drive"   
#include "./TIMER_interface/TIMER_interface.h"   
#include "ALarm_EXit_inter.h" 
#include "./systick/systick.h"
#include "./interrupt/interrupt.h"
#include "sysclockfuzhi.h" 
#include "GPIO_PAR_Inter.h"
#include   "can_interface.h"
#include "Usart_interface.h"
#include "Memory_Par_Inter.h"
#include   "Power_manage_Chip_Set.h"
#include  "IIC_hard_Drive.h"
#include "Timer_Interface.h"
#include "Schedule.h"
#include   "Low_power_inter.h"
#include  "Bq7695202_drive.h"

void System_INIT(void)        //总初始化
{  
	 RCC_PeriphClockCmd_Enable();   //打开时钟
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //2位抢占优先级，2位子优先级
	 systick_config();	   //systick_config 计时器初始化
   I2C1_Init();
	 GPIO_Set();
	 if(BQ769x2_Init(Flash_Setting)!=Task_OK)   //如果设定错误，就需要重启。
	 {
		 NVIC_SystemReset();   //进行重启
	 }
	 EVE_Init();
   TIM1_Init();                  //1ms中断
   CAN_Config();
   Alarm_Exti_Init();
	 USART1_Init(9600);  
	 
}


void  Manage_Chip_Init(void)
{
//Memory_SysInit_Assign();  //标志位初始化
//Check_Chip_Error;   //	查看SH是否准备完备,能够读取数据
//BatteryInfoManage();  // 读取电压,温度,电流,并求取电压最大值,最小值,总电压
//UpdataAfeConfig;	 //SH中的EEPROM值对照并检查(26个数据),如果失败则重写入
//BatteryInfoManage();  // 读取电压,温度,电流,并求取电压最大值,最小值,总电压
//InitGasGauge();	  //估测电池的初始容量,soc根据电压和数据对比进行估测
//EnableAFEWdtCadcz;	 //使能CHG&DSG&PCHG输出，且使能WDT和CADC模块
//Balance_Key;
}























