#include   "Power_manage_Chip_Set.h"
#include "SH367309_interface.h"
#include "Memory_Par_Inter.h"
#include "Calibration_inter.h"

/************************************************************************************
**********************BatteryInfoManage相关函数,主要是电压温度的数据处理******
*****************************开始*开始*开始**开始*开始*开始*************************************/
/*******************************************************************************
Function: 
Description: First Calculate Temp1/Temp2/Temp3/VCell1-VCell16/Current 
Input:
Output:
Others:
*******************************************************************************/
/*
void BatteryInfoManage(void)                       //进行计算对应的数据,有关SH 的寄
{
if(GetAFEData)       //将全局数组,AFE的值进行赋值.   
	{
		CalcuTemperature();   //根据获取的40H 的温度值,寄存器值,tempt1进行计算温度
		///将info的数组的数据,,进行对应的更新
		CalcuVoltage();
		//将INFO 有关电压的数据采集完毕
		CalcuVolMaxMin();   //  uiCellVmin  uiCellVmax  寻找到最大的电压和最小的电压,并且赋值给全局变量. 需要注意的是,sh367309是支持乱序插法的,所以电压的大小并不是累加的
	}	
}
*/
/*******************************************************************************
Function: 
void CalcuTemperature(void)
Description: 对温度计算计算,然后留出温度的接口,三个温度接口,传的是地址
Input:	
Output:  Temp1   Tempt2  Tempt3  的返回值
Others:   赋值给Info.Temperature1   Info.Temperature2   Info.Temperature3

Others:   根据数据池中的数据AFE.TEmpt1  进行温度修正计算
*******************************************************************************/
/*
void CalcuTemperature(void)
{
	uint16_t  tempedata=0;
	
	if(!bTempNum1 && bTempNum0)					//Support one temperature detection    //bTempNum1  bTempNum0全局变量,其实只是一个标志位  //在系统初始化时已经规定好了
	{
		tempedata = CalcuTemp(AFE.Temp1)+E2siTempe1Offset;    //校正参数值,放在对应寄存器 位置,可直接查询 值   //E2siTempe1Offset可以进行通过PC机进行校准   //tempedata为获取 值后,获得的数据
		//UART_IRQ_DISABLE;          //串口中断关闭
		Info.Temperature1 = tempedata;    //info数组记录此时的温度值
        Info.Temperature2 = 2731;        //随意写了数据可能
        Info.Temperature3 = 2731;
		//UART_IRQ_ENABLE;                   //串口中断开启
	}
	else if(bTempNum1 && !bTempNum0)			//Support two temperature detection
	{
		tempedata = CalcuTemp(AFE.Temp1)+E2siTempe1Offset;
		//UART_IRQ_DISABLE;
		Info.Temperature1 = tempedata;
		//UART_IRQ_ENABLE;
		
		tempedata = CalcuTemp(AFE.Temp2)+E2siTempe2Offset;
		//UART_IRQ_DISABLE;
		Info.Temperature2 = tempedata;
        Info.Temperature3 = 2731;
		//UART_IRQ_ENABLE;
	}
	else if(bTempNum1 && bTempNum0)				//Support three temperature detection
	{
		tempedata = CalcuTemp(AFE.Temp1)+E2siTempe1Offset;
		//UART_IRQ_DISABLE;
		Info.Temperature1 = tempedata;
		//UART_IRQ_ENABLE;
		
		tempedata = CalcuTemp(AFE.Temp2)+E2siTempe2Offset;
		//UART_IRQ_DISABLE;
		Info.Temperature2 = tempedata;
		//UART_IRQ_ENABLE;
		
		tempedata = CalcuTemp(AFE.Temp3)+E2siTempe3Offset;
		//UART_IRQ_DISABLE;
		Info.Temperature3 = tempedata;
		//UART_IRQ_ENABLE;
	}
}
*/

/*******************************************************************************
Function: 
Description:  
1. Calculate a single battery voltage     //进行电压的计算
2. Calculate the total voltage
Input:	 	
Output: 
Others:
*******************************************************************************/
void CalcuVoltage(void)
{
	uint8_t  i;
	uint32_t temppackvol=0, tempcellvol=0;
		for(i=0; i<ucCellNum; i++)
	{
		AFE.Cell[i]=AFE.Cell[i]*3800/24354;
	}
	
	for(i=0; i<ucCellNum; i++)
	{
		
		
	//	tempcellvol = (uint32_t)AFE.Cell[i]*CALIVOL/E2uiVPackGain;			//Calculate a single battery voltage   //  E2uiVPackGain   0x05F,0x022,   //E2uiVPackGain  是通过上位机进行校正的一个值,通过这个校正值,可以使电压的反应正确的值
		tempcellvol = (uint32_t)AFE.Cell[i];
		temppackvol += tempcellvol;						//Calculate the total voltage
		//UART_IRQ_DISABLE;    //关闭串口
		Info.VCell[i] = temppackvol;       //在对应的数组中,写入对应的电压值
	//	UART_IRQ_ENABLE;     //打开串口中断
		
	}
	
	//UART_IRQ_DISABLE;
	Info.Voltage = temppackvol;
	//UART_IRQ_ENABLE;
}


/*******************************************************************************
Function: 
Description:  Get the maximum and minimum voltage    ??????????????存在疑问,不应该是AFE吗
Input:	 	
Output: 
Others:
*******************************************************************************/
void CalcuVolMaxMin(void)
{
	uint8_t i=0;

	uiCellVmax = AFE.Cell[i];
	uiCellVmin = AFE.Cell[i];
	
	for(i=1; i<ucCellNum; i++)
	{
		if(AFE.Cell[i] > uiCellVmax)
		{
			uiCellVmax = Info.VCell[i];
		}
		if(AFE.Cell[i] < uiCellVmin)
		{
			uiCellVmin = Info.VCell[i];
		}
	}
		//uiCellVmax = (uint32_t)uiCellVmax*CALIVOL/E2uiVPackGain;
  	//uiCellVmin=(uint32_t)uiCellVmax*CALIVOL/E2uiVPackGain;
}

/************************************************************************************
**********************BatteryInfoManage相关函数,主要是电压温度的数据处理结束******
*****************************结束结束结束结束*************************************/



/**************************************************************************
****************************以下是电池容量的相关处理*******************
*********************************************************************/

/*******************************************************************************
Function:InitGasGauge() 
Description: Calculate the remaining capacity according to pack voltage   
////获取剩余容量  
//但是从一定程度上讲,这个算法其实是不理想的,因为还存在着死电池,这个短板效应才是影响电池容量的方法
//算法还需要去改正
/////但是还是需要注意,这是主机刚刚开启的时候
/////可能需要根据EEprom上的数据进行测算
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
void InitGasGauge(void)
{
	uint8_t  i;
	Info.RSOC = 100;   //百分比为100%
	for(i=0; i<=10; i++)
	{
		if(Info.Voltage < E2uiVOC[i]*ucCellNum)   //获得这个量的值,也就是逼近这个电压的参数    // ucCellNum之前已经进行记录过了
		{
			if(i == 0)   
			{   //电压的值小于3200,也就是V0C10 的值
				if(Info.Voltage < E2uiDsgEndVol*ucCellNum)   //E2uiDsgEndVol   在dataflash中是3000   //也就是说进行再次判断
				{  //小于那么容量为0
					Info.RSOC = 0;	
				}
				else
				{
				 	Info.RSOC = (uint32_t)(Info.Voltage-E2uiDsgEndVol*ucCellNum)*10/((E2uiVOC[0]-E2uiDsgEndVol)*ucCellNum);	   //采用算中间值的方法
				}
				break;
			}
			else
			{
				Info.RSOC = 10*i + (uint32_t)(Info.Voltage-E2uiVOC[i-1]*ucCellNum)*10/((E2uiVOC[i]-E2uiVOC[i-1])*ucCellNum);  //也是采用算中间值的方法
				break;
			}
		}
	}

	Info.RC = E2ulFCC*Info.RSOC/100;      ////可能是求安时积分  ,也就是容量*时间
}




/******************************************************************
*******************************SOC计算****************************
*************************************************************************/



/*******************************************************************************
Function:GaugeManage() 
Description: Manage the capacity of the pack    //管理电池的容量    //1如果充电,则代表,达到1AH时,这个容量将会增加
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
void GaugeManage(void)     
{
	uint16_t FccDelta=0;
uint16_t    tempt=0;
	if(bCHGING|bSC|bOCC|bOCD1|bOCD2)  //如果发现有报警的信息	   //注意没有正常放电的阿情况 					//If the charge or discharge overcurrent   //bSC | bOCC | bOCD1 | bOCD2  uiBatStatus的标志位   //43h的值
	{
		bVDQ_FALSE;  /////注意如果是放电的时候也会发生  /////发生过流时,测的值是不准的
	}
	else
	{ ///假设如果都没发生上面的事件  则bVDQ = 1;  那么将会不会进入下面的if的语句中      ////如果都没有这些置位,那么可以测温度,,,,,,,   //bVDQ这个标志位  已经是置1了    //bVDQ = 1;  肯定有什么非常重要的作用
		if(!bVDQ && (Info.RC>(Info.E2ulFCC-E2uiNearFCC)))   //E2uiNearFCC可能是不能进行电池管理的值        
		{     //进行测温度     高于某个最低温度,那么可以进行电源管理,并且把对应的位进行更新
			if(!bTempNum1 && bTempNum0)					//Support one temperature detection
			{
				if(Info.Temperature1>E2siLearnLowTemp)
				{
					
					ulFCCCount = 0;               //	进行置位
          ulRCCharge=0;          //实时容量归0.因为过流不能反应真实情况					
				}
			}
			else if(bTempNum1 && !bTempNum0)			//Support two temperature detection
			{
				if((Info.Temperature1>E2siLearnLowTemp)
					&& (Info.Temperature2>E2siLearnLowTemp))
				{
					
					ulFCCCount = 0;	
          ulRCCharge=0;          //实时容量归0.因为过流不能反应真实情况					
					
					
				}
			}
			else if(bTempNum1 && bTempNum0)				//Support three temperature detection
			{
				if((Info.Temperature1>E2siLearnLowTemp)
					&& (Info.Temperature2>E2siLearnLowTemp)
					&& (Info.Temperature3>E2siLearnLowTemp))
				{
					
					ulFCCCount = 0;			
          ulRCCharge=0;          //实时容量归0.因为过流不能反应真实情况	
					
					
				}				
			}
			else									   //No temperature detection
			{
				 ulRCCharge=0;          //实时容量归0.因为过流不能反应真实情况		
				ulFCCCount = 0;
			}
		}
	}
	
	if(bCHGING)		  ///如果是过流了???怎么去思考,,,或者是	///?????????可能依靠的是硬件上的 逻辑    											//charging          //如果是充电,并且是高于某个阈值  E2siDfilterCur
	{
		ulRCCharge += Info.CurCadc;       //CurCadc  存放测量的电流值    //ulRCCharge += Info.CurCadc  可能是安时积分,,但是这个是秒级的
		tempt=0;
		while(ulRCCharge >= VALUE_mAH)   //当这个值高于3600   毫安时    //进入循环
		{
			ulRCCharge -= VALUE_mAH;       //然后进行  每一减.那么电池容量就会加一
			if(Info.RC < Info.E2ulFCC)
			{
				//UART_IRQ_DISABLE;
				tempt++;
				Info.RC++;										//have charged 1mAh    //以这个为单位   //然后容量加上1mH
				////UART_IRQ_ENABLE;
			}
			else
			{   //表示电池已经充满了.高于或者等于这个的最高的容量
				//UART_IRQ_DISABLE;
				Info.RC = Info.E2ulFCC;
				////UART_IRQ_ENABLE;
				ulRCCharge = 0;
			}
		}
		if(ulRCCharge <=VALUE_mAH)
		{
			tempt=tempt;
		}
	}
	else if(bDSGING)		//			如果是放电								//discharging
	{
		ulRCDischarge += -Info.CurCadc;
		if(ulRCDischarge >= VALUE_mAH)
		{   //如果电流积攒到1mAH
			while(ulRCDischarge >= VALUE_mAH)
			{//如果电流积攒到1mAH,,,再次校验ulRCDischarge >= VALUE_mAH
				ulRCDischarge -= VALUE_mAH;
				ulDsgCycleCount++;     //计算一共放电量
				if(Info.RC > 0)
				{
					//UART_IRQ_DISABLE;
					Info.RC--;
					////UART_IRQ_ENABLE;
				}
				if(bVDQ)     //
				{
					ulFCCCount++;      //每一次毫安时积分,对应的值就会加上一个值
				}
			}
			
			if(ulDsgCycleCount >= E2ulCycleThreshold)    //  大于6400   ///这个循环值会不会太大了
			{
				ulDsgCycleCount -= E2ulCycleThreshold;
				E2uiCycleCount++;   
 			  Info.E2uiCycleCount = E2uiCycleCount;   //6400mAH进行累计  ,每次    //充放电循环统计.
				bWrFlashFlg = SUCCESS;				//write E2uiCycleCount to flash flag
        //UpEepromWithDelay();
			}
		}
	}
	
	if(Info.RC < Info.E2ulFCC)						//Calculate RSOC
	{
		//UART_IRQ_DISABLE;
		Info.RSOC = (uint32_t)Info.RC*100/Info.E2ulFCC;   //计算剩余的容量  ,,百分比   
		////UART_IRQ_ENABLE;
	}
	else
	{  //表示是大于容量的100%
		//UART_IRQ_DISABLE;
		Info.RSOC = 100;     //
		////UART_IRQ_ENABLE;
	}

	//UART_IRQ_DISABLE;
	if(!bDSG_FET)		//如果放电mos关闭	    //////欠压保护保护															//OverVoltage Protect
	{
		if(bUV)			//如果欠压保护											        //E2ulFCC updata
		{
     if(bVDQ)
     {	
		 //此时一切正常,且没有充电开启
			FccDelta = (Info.E2ulFCC/10)*FCC_UPDATE_PERCENT;  //FccDelta是一个暂态变量,而且FccDelta代表容量的30%
			
			if(ulFCCCount > Info.E2ulFCC+FccDelta)  //  如果大于容量的130%
			{
				ulFCCCount = Info.E2ulFCC + FccDelta;  //则为30%
			}
			else if(ulFCCCount+FccDelta < Info.E2ulFCC)   //如果放电低于容量的70%   //   如果放电放完,比这个值还小,说明可能因为电池衰减,容量变小了...........但是如果我们考虑其他因素.
			{
				ulFCCCount = Info.E2ulFCC - FccDelta;      //ulFCCCount 为容量的70%  (次/mah)
			}
			//UART_IRQ_DISABLE;
			Info.E2ulFCC = ulFCCCount;	   //										//write E2ulFCC to flash
			////UART_IRQ_ENABLE;
			E2ulFCC = ulFCCCount;   //重新定义容量
			//bWrFlashFlg = SUCCESS;
      //UpEepromWithDelay();   //重新写到flash里面
		}
	
		Info.RC = 0;																
		Info.RSOC = 0;
	}
		if(!bLVBkFlg)   //有关外挂到EEPROM的信息的处理
		{
			bLVBkFlg = SUCCESS;
			bE2PProcessFlg = SUCCESS;				//backup battery info when bLV
			bE2PBKDsgEnd = SUCCESS;
		}
	}
	else if(!bCHG_FET)   //发生过压保护,,,																	//UnderVoltage Protect
	{
		if(bOV)  //如果过压保护
		{
		bVDQ_SUCCESS;   //置位  ,,,此时才会进行容量更新
		Info.RC = Info.E2ulFCC;   //那么容量为一百
		Info.RSOC = 100;
		}
	}
	else
	{
		bLVBkFlg = ERROR;
	}
	////UART_IRQ_ENABLE;
}
















