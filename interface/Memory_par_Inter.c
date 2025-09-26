#include "Memory_Par_Inter.h"


uint16_t       uiPackConfig;				//0x000,0x0E0   对照E2uiPackConfigMap的值
uint16_t       uiPackStatus;				
uint16_t       uiBatStatus;
		
		

ErrorStatus  EEprom_Written;          //判断EEPROM是否已经被写入
ErrorStatus  EEprom_Error_AFE;       //判断EEPROM是否读取失败



ErrorStatus bWakeupFlg;						//唤醒标志，系统从低功耗被唤醒
ErrorStatus bCADCFlg;						//CADC转码完成标志
ErrorStatus bCalibrationFlg;				//上位机发送校准命令后置位该标志
ErrorStatus bWrFlashFlg;					//写FLASH标志
ErrorStatus bE2PProcessFlg;					//EEPROM处理标志
ErrorStatus bISPFlg;						//ISP升级标志，进入ISP程序
ErrorStatus bTimerFlg;						//1s定时器标志
ErrorStatus bIdleTimerFlg;					//5s定时器标志
ErrorStatus bHalfHzFlg;						//0.5HZ标志（用于LED显示蓝牙状态）
ErrorStatus b2HzFlg;						//2HZ标志（用于LED显示蓝牙状态）
ErrorStatus bIdleFlg;						//系统进入IDLE标志
ErrorStatus bSleepFlg;						//系统进入SLEEP标志
ErrorStatus bPCSleepFlg;					//PC通知系统进入SLEEP标志
ErrorStatus bLEDOpen;						//LED电量显示标志
ErrorStatus bLEDFlg;						//LED电量显示过程中
ErrorStatus bLongKeyFlg;					//按键长按检测标志
ErrorStatus bBleOnOffFlg;					//蓝牙启停标志
ErrorStatus bUartSndAckFlg;					//UART已经发送ACK给主机
ErrorStatus bUartNeedAckFlg;				//UART需要发送ACK给主机
ErrorStatus bCHGClosedFlg;					//充电结束关闭充电MOS标志
ErrorStatus bDSGClosedFlg;					//放电结束关闭放电MOS标志
ErrorStatus bProtectFlg;					//保护发生标志，需要从低功耗唤醒(未置位，恒为0)
ErrorStatus bAFEFlg;						//AFE的ALARM发生标志

ErrorStatus bDsgToChgFlg;					//放电转换为充电，需要备份数据
ErrorStatus bChgToDsgFlg;					//充电转换为放电，需要备份数据
ErrorStatus bLVBkFlg;						//LV低电压标志，需要备份信息到外挂EEPROM
ErrorStatus bE2PBKDsgEnd;					//放电结束标志，需要备份信息到外挂EEPROM
ErrorStatus bE2PBKChgStop;					//充电结束标志，需要备份信息到外挂EEPROM
ErrorStatus bE2PBKChgStart;					//充电开始标志，需要备份信息到外挂EEPROM
ErrorStatus bE2PBKRtc;						//RTC定时备份标志，需要备份信息到外挂EEPROM
ErrorStatus bE2PErase;						//擦除外挂EEPROM标志
ErrorStatus bE2PRdData;						//读取外挂EEPROM标志
ErrorStatus bRTCRdTime;						//读取RTC时间标志
//ErrorStatus bE2ON;				            //E2ON(0：外挂E2需初始化。1：外挂E2无需初始化。)
//ErrorStatus bRTCON;							//RTCON(0：外挂RTC需初始化。1：外挂RTC无需初始化。)

//uint16_t     NTC103AT[161];				//热敏电阻NTC103AT阻值表

//*****************************     MEMORY START***************************//
//uint8_t    STACK[];		//堆栈

uint8_t       ucResetFlag;				//PC to send a software reset instruction
uint8_t       ucTimer0Cnt;				//Timer0 counter, Every 20ms +1
uint8_t       ucTimer0Cnt1;				
uint8_t       ucFlashWrValid;				//Write flash protect flag
uint8_t       ucKeyDownCnt;				//Key Down state counter
uint8_t        ucCellNum;					//For storage cell num        //篆刻
uint16_t      uiCellVmax;					//The maximum value of all the Cell
uint16_t      uiCellVmin;					//The minimum value of all the Cell
uint8_t       ucUartTimeCnt;				//Uart no communication timing, for enter sleep or idle
uint8_t       ucIdleTimeCnt;				//idle counter
int16_t       siCurBuf[12];				//for storage CADC value, Is used to calculate the mean Within 1s
uint8_t       ucCadcTimeCnt;				//for storage CADC value, Is used to calculate the mean Within 1s
uint8_t       ucChgEndTimeCnt;			//Charging cut-off delay count
uint8_t       ucChgEndRTimeCnt;
uint8_t       ucDsgEndTimeCnt;			//Discharging cut-off delay count
uint8_t       ucDsgEndRTimeCnt;			//Discharging cut-off delay count
uint8_t       ucBalanceTimeCnt[16];		//Balance time counter(for each cell)
uint8_t       ucBalUpdateTimeCnt;			//Balance update time counter
uint16_t      uiBalanceChannel;			//Balance Channel
uint8_t       ucLEDTimeCnt;				//LED display delay count

uint8_t        ucExtcaliSwitch1;			//calibration flag      //校准标志位
uint8_t        ucExtcaliFlag;				//calibration flag
uint32_t       ulExtVPack;				//During calibration, the received total voltage
uint32_t       slExtCur;					//During calibration, the received current
uint16_t       uiExtTemp1;				//During calibration, the received ttemperature1
uint16_t       uiExtTemp2;				//During calibration, the received ttemperature2
uint16_t       uiExtTemp3;				//During calibration, the received ttemperature3
uint8_t        ucTempeMiddle;				//Record the current temperature resistance corresponding address, for the next quick look     //需要注意在查询的时候,一定要选择合适的值
uint8_t        ucExtRTC[6];				//During calibration, the received RTC Time


uint8_t        ucMTPConfVal;				//for MTP CONF Register

uint32_t       ulRCCharge;				//Charge capacity statistics
uint32_t       ulRCDischarge;				//Discharge capacity statistics
uint32_t       ulDsgCycleCount;			//Discharge capacity statistics, for update E2uiCycleCount
uint32_t       ulFCCCount;				//The effective discharge capacity statistics, for updating E2ulFCC    //放电容量

uint16_t       uiE2PDataAddr;
uint8_t        ucRTCBKTime1;
uint16_t       uiRTCBKTime2;
//uint8_t        ucRTCBuf[];
uint8_t    ucUpDataLimitTime;

uint16_t       uiCHGValidTime;

ErrorStatus bUartReadFlg;
ErrorStatus bUartWriteFlg;
uint8_t       ucSubClassID;
uint8_t       ucUartBufPT;			//Pointing to the current UART Buffer
uint8_t       ucUartSndLength;		//UART Buffer send length
uint8_t       ucUartTimeoutCnt;		//UART timerout cnt, If not Uart communication within 2s, then clear ucUartBufPT
//uint8_t       ucUartBuf[];			//For UART transmit or acceptance buffer



//*****************************      MEMORY START***************************//
//系统参数，子命令号：0x00
uint16_t       E2uiPackConfigMap;
uint16_t       E2uiVOC[11];
uint32_t       E2ulDesignCap;
uint32_t       E2ulFCC;
uint32_t       E2ulCycleThreshold;
uint16_t       E2uiCycleCount;
uint16_t       E2uiNearFCC;
uint16_t       E2siLearnLowTemp;
uint16_t       E2siDfilterCur;      //用于判断电流方向
uint8_t        E2ucSleepDelay;
uint8_t        E2ucIdleDelay;
uint8_t        E2ucCommOffDelay;
uint8_t        E2ucChgBKDelay;
uint16_t       E2siChgBKCur;
uint8_t        E2ucRTCBKDelay;
uint8_t        E2ucRamCheckFlg1;

//用户自定义A区，子命令号：0x01
uint16_t       E2uiSWVersion;
uint16_t       E2uiHWVersion;
uint8_t        E2ucID;
//uint8_t        E2ucMNFName[];
uint32_t       E2ulMNFDate;
uint16_t       E2uiSerialNum;
//uint8_t        E2ucDeviceName[];
//uint8_t        E2ucDeviceChem[];
uint16_t       E2uiChemID;
uint8_t        E2ucRamCheckFlg2;

//充电参数，子命令号：0x02
uint16_t       E2uiChgEndVol;
uint16_t       E2siChgEndCur;
uint8_t        E2ucChgEndDelay;
uint8_t        E2ucRamCheckFlg3;

//平衡参数，子命令号：0x08
uint16_t       E2uiBalanceVol;
uint16_t       E2siBalanceCur;
uint16_t       E2uiBalanceVolDiff;      //最大和最小的电压  ,相差最大的值
uint8_t        E2ucBalanceDelay;
uint8_t        E2ucRamCheckFlg4;

//放电参数，子命令号：0x03
uint16_t       E2uiDsgEndVol;
uint8_t        E2ucDsgEndDelay;
uint8_t        E2ucRamCheckFlg5;
float       RES_SENSE;    //采样电阻的阻值 值为(例 10 *(0.000001欧),10为其中的值)


//AFE参数，子命令号：0x0A
 uint8_t   ucMTPBuffer[26]={SCONF1_Config,SCONF2_Config,OV_H_Config,OV_L_Config,OVR_H_Config,\
OVR_L_Config,Uv_Config,UVR_Config,BALV_Config,PREV_Config,L0V_Config,PFV_Config,OCD1V_OCD1T_Config,OCD2V_OCD2T_Config,\
SCV_SCT_Config,OCCV_OCCT_Config,MOST_OCRT_PFT,OTC_Config,OTCR_Config,UTC_Config,UTCR_Config,OTD_Config,OTDR_Config,UTD_Config,\
UTDR_Config,TR_Config};                                //关注11到19位,里面存放着各个采集温度与NTC电阻的对应值     


uint8_t        E2ucRamCheckFlg6;

//校准参数，子命令号：0x0B
uint16_t       E2uiVPackGain;
float          E2siCadcGain_Dio;
float          E2siCadcGain_Cha;
uint16_t       E2siCadcZero;
uint16_t       E2siTempe1Offset;
uint16_t       E2siTempe2Offset;
uint16_t       E2siTempe3Offset;
uint8_t        E2ucCalibrated;
uint8_t        E2ucRamCheckFlg7;

//类E2写入OK标志
uint16_t       E2uiCheckFlag;


AFEDATA     AFE;
SYSINFOR		Info;

ErrorStatus  Read_Bit_Data(uint16_t Status_Flag,uint8_t wei)
{
	uint16_t Data_Tempt=0;
	ErrorStatus pars=SUCCESS;
	Data_Tempt=(Status_Flag>>wei)&(0x0001);
	pars=(ErrorStatus)Data_Tempt;
	return pars;
}


void  Write_Bit_Data(uint16_t *Status_Flag,uint8_t wei,uint16_t Action)
{
	if(Action==1)
	{
	*Status_Flag|=(0x0001<<wei);
	}
	else if(Action==0)
	{
	*Status_Flag&=(~(0x0001<<wei));
	}
}





/*******************************************************************************
FunctionErrorStatus:
void Memory_SysInit_Assign(void)

Description:
将参数进行赋值并初始化,需要注意的是有些参数是不能更改的
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
void Memory_SysInit_Assign(void)
{
	uint8_t i=0;
	//ucMTPBuffer[26]    已经被定义为常量
	uiPackStatus=0x0000;     //将整个标志位都定义为0
	bAFE_ERR_FALSE;  //将bAFE_ERR定义为0   uiPackStatus的12位.表示没有错误
	for(i=0;i<=10;i++)     //初始化时  用来表示容量的大小,通过逼近法去逼近;
	{
	  E2uiVOC[i]=2800+145*i;
	}
  EEprom_Written=ERROR;
  EEprom_Error_AFE=ERROR;
  ucMTPConfVal=0x00;
	uiPackConfig|=0xC000;
	bTimerFlg=ERROR;   //1s标志位为初始状态位
	ucTimer0Cnt=0;     //初始状态为0;
	ucTempeMiddle = 80;   //用于计算温度
	E2uiVPackGain=24354;
	E2siCadcZero=0xFFFF;
	RES_SENSE=8000.0;    //采样电阻值 : 0.22毫欧
	E2siDfilterCur=300;  //如果小于这个值,则认为没有电流
	E2siCadcGain_Cha=0.9470862;   //用来修正充电电流
	E2siCadcGain_Dio=0.982;
	E2ulFCC=2648;   //电池为20AH
	Info.E2ulFCC=E2ulFCC;
}




