#include   "BM8563_interface.h"
#include   "BM8563_Drive.h"
static uint8_t TimeNow[7]={0x23,0x27,0x0D,0x06,0x04,0x84,0x17};
static uint8_t Time_Alarm[4]={0x00,0x00,0x00,0x00};
static uint8_t Control_Regi[2]={0x80,0x00};
static uint8_t CountDown[3]={0x00,0x03,0x00};
#define HEX_To_BCD(x)     x/10*16+x%10
#define BCD_To_HEX(x)     x/16*10+x%16


uint8_t  Time_Receive[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};

bool BM8563_Init_Confi(void)
{
	if(!(Set_BM8563_CountDown_Fre()))
	{
		return FALSE;
	}
	if(!(Set_BM8563_Control_Regi()))
	{
		return FALSE;
	}		
	if(!(Set_BM8563_TimeAlarm()))
	{
		return FALSE;
	}		
	if(!(Set_BM8563_TimeNow()))
	{
		return FALSE;
	}	
	return TRUE;
}



/*******************************************************************************
Functionbool:
void Set_BM8563_TimeNow()
Description:设置时间当前
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
bool Set_BM8563_TimeNow(void) 
{
	uint8_t TimeNow_Tempt[7];
	TimeNow_Tempt[0]=HEX_To_BCD(TimeNow[0]);     //秒转换,BCD码
  TimeNow_Tempt[1]=HEX_To_BCD(TimeNow[1]);     //分转换,BCD 
  TimeNow_Tempt[2]=HEX_To_BCD(TimeNow[2]); 	   //时转化
  TimeNow_Tempt[3]=HEX_To_BCD(TimeNow[3]); 	  //日转化
  TimeNow_Tempt[4]=TimeNow[4];               //星期
  TimeNow_Tempt[5]=HEX_To_BCD(TimeNow[5]);   //月转化
  TimeNow_Tempt[6]=HEX_To_BCD(TimeNow[6]);   //年转化
	if(!(Set_BM8563_TimeNow_Drive(BM8563_Gpio_SDA,BM8563_Pin_SDA,BM8563_Gpio_SCL,BM8563_Pin_SCL,TimeNow_Tempt)))
	{
		return FALSE;
	}
	  return TRUE;
}

/*******************************************************************************
Functionbool:
void Set_BM8563_TimeAlarm()
Description:设置时间报警
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
bool Set_BM8563_TimeAlarm(void)
{
	uint8_t Time_Alarm_Tempt[4];
	Time_Alarm_Tempt[0]=HEX_To_BCD(Time_Alarm[0]);
	Time_Alarm_Tempt[1]=HEX_To_BCD(Time_Alarm[1]);
	Time_Alarm_Tempt[2]=HEX_To_BCD(Time_Alarm[2]);
	Time_Alarm_Tempt[3]=HEX_To_BCD(Time_Alarm[3]);
	if(!(Set_BM8563_TimeAlarm_Drive(BM8563_Gpio_SDA,BM8563_Pin_SDA,BM8563_Gpio_SCL,BM8563_Pin_SCL,Time_Alarm_Tempt)))
	{
		return FALSE;
	}
	  return TRUE;
}

/*******************************************************************************
Functionbool:
void Set_BM8563_Control_Regi(void)
Description:设置时间控制寄存器的值
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
bool Set_BM8563_Control_Regi(void)
{
	if(!(Set_BM8563_Control_Regi_Drive(BM8563_Gpio_SDA,BM8563_Pin_SDA,BM8563_Gpio_SCL,BM8563_Pin_SCL,Control_Regi)))
		{
		return FALSE;
	}
	  return TRUE;
}

/*******************************************************************************
Functionbool:
void Set_BM8563_CountDown_Fre(void)
Description:设置时间定时器
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/

bool Set_BM8563_CountDown_Fre(void)
{
	if(!(Set_BM8563_CountDown_Fre_Drive(BM8563_Gpio_SDA,BM8563_Pin_SDA,BM8563_Gpio_SCL,BM8563_Pin_SCL,CountDown)))
	{
		return FALSE;
	}
	  return TRUE;
}

       
bool Read_TimeNow(void)
{
uint8_t  Time_Receive_Tempt[7];
if(!(Read_TimeNow_Drive(BM8563_Gpio_SDA,BM8563_Pin_SDA,BM8563_Gpio_SCL,BM8563_Pin_SCL,Time_Receive_Tempt)))
{
	return FALSE;
}
Time_Receive[0]=BCD_To_HEX(Time_Receive_Tempt[0]);     //秒转换,BCD码
Time_Receive[1]=BCD_To_HEX(Time_Receive_Tempt[1]);     //分转换,BCD 
Time_Receive[2]=BCD_To_HEX(Time_Receive_Tempt[2]); 	   //时转化
Time_Receive[3]=BCD_To_HEX(Time_Receive_Tempt[3]); 	  //日转化
Time_Receive[4]=Time_Receive_Tempt[4];               //星期
Time_Receive[5]=BCD_To_HEX(Time_Receive_Tempt[5]);   //月转化
Time_Receive[6]=BCD_To_HEX(Time_Receive_Tempt[6]);   //年转化
return TRUE;
}








