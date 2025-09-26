#ifndef    MEMORY_PAR_INTERFACE_H
#define    MEMORY_PAR_INTERFACE_H
#include "stm32f10x.h"







#define bCHGEnd      Read_Bit_Data(uiPackConfig,8)         //FLASH 设定    1110 0000    //也就是,,充电需要不要人来控制
#define bDSGEnd      Read_Bit_Data(uiPackConfig,9)
#define bEnEEPRomBK  Read_Bit_Data(uiPackConfig,11)        
#define bLEDNum0     Read_Bit_Data(uiPackConfig,12)
#define bLEDNum1     Read_Bit_Data(uiPackConfig,13)       //定义有多少盏灯
#define bTempNum0    Read_Bit_Data(uiPackConfig,14)
#define bTempNum1    Read_Bit_Data(uiPackConfig,15)    //定义采集温度的数量




		
#define  bFD		  Read_Bit_Data(uiPackStatus,0)  
#define  bFC	 	  Read_Bit_Data(uiPackStatus,1)  
#define bVDQ			Read_Bit_Data(uiPackStatus,2)   
//#define bOverLoad		=	3;
#define bBLEOPEN		Read_Bit_Data(uiPackStatus,3)   
#define bCAL			  Read_Bit_Data(uiPackStatus,4)  //是否校正完成标志位  , 完成则校为1


#define bDSG_FET		Read_Bit_Data(uiPackStatus,8)  // 放电mos状态位
#define bCHG_FET		Read_Bit_Data(uiPackStatus,9)  //充电mos状态位
#define bPCHG_FET		Read_Bit_Data(uiPackStatus,10)  //预充电mos状态位
#define bL0V			  Read_Bit_Data(uiPackStatus,11)  //低电压禁止充电位
#define bAFE_ERR		Read_Bit_Data(uiPackStatus,12)     //标志位.只要有关EEPROM 烧写时遇到的错误
#define bDSGING		  Read_Bit_Data(uiPackStatus,14)  //代表  有电流流经的标志位   
#define bCHGING		  Read_Bit_Data(uiPackStatus,15)  //如果是放电




		
#define bUTC			Read_Bit_Data(uiBatStatus,0)     //充电低温保护
#define bOTC			Read_Bit_Data(uiBatStatus,1)    //充电高温保护
#define bUTD			Read_Bit_Data(uiBatStatus,2)    //放电低温保护
#define bOTD			Read_Bit_Data(uiBatStatus,3)    //放电高温保护

#define bOV	     	Read_Bit_Data(uiBatStatus,8)      //过压保护状态位
#define bUV			  Read_Bit_Data(uiBatStatus,9)        //欠压保护状态位          
#define bOCD1			Read_Bit_Data(uiBatStatus,10)    //放电过流1
#define bOCD2			Read_Bit_Data(uiBatStatus,11)   //放电过流2
#define bOCC			Read_Bit_Data(uiBatStatus,12)    //充电过流
#define bSC			  Read_Bit_Data(uiBatStatus,13)    //短路保护位
#define bPF			  Read_Bit_Data(uiBatStatus,14)








#define bCHGEnd_SUCCESS      Write_Bit_Data(&uiPackConfig,8,1)         //FLASH 设定    1110 0000    //也就是,,充电需要不要人来控制
#define bDSGEnd_SUCCESS      Write_Bit_Data(&uiPackConfig,9,1)
#define bEnEEPRomBK_SUCCESS  Write_Bit_Data(&uiPackConfig,11,1)        
#define bLEDNum0_SUCCESS     Write_Bit_Data(&uiPackConfig,12,1)
#define bLEDNum1_SUCCESS     Write_Bit_Data(&uiPackConfig,13,1)       //定义有多少盏灯
#define bTempNum0_SUCCESS    Write_Bit_Data(&uiPackConfig,14,1)
#define bTempNum1_SUCCESS    Write_Bit_Data(&uiPackConfig,15,1)    //定义采集温度的数量




		
#define  bFD_SUCCESS		  Write_Bit_Data(&uiPackStatus,0,1)  ///现在是纠正回来的状态    ////充电的标志位,,,但是按照45H,,应该是放电的状态位
#define  bFC_SUCCESS	 	  Write_Bit_Data(&uiPackStatus,1,1)  ///这个位会不会对照错了,,,,这个位对照45H ,,应该是在充电mos的状态位
#define bVDQ_SUCCESS			Write_Bit_Data(&uiPackStatus,2,1)
//#define bOverLoad		=	3;
#define bBLEOPEN_SUCCESS		Write_Bit_Data(&uiPackStatus,3,1)
#define bCAL_SUCCESS		  Write_Bit_Data(&uiPackStatus,4,1)  //是否校正完成标志位  , 完成则校为1
#define bDSG_FET_SUCCESS		Write_Bit_Data(&uiPackStatus,8,1)
#define bCHG_FET_SUCCESS		Write_Bit_Data(&uiPackStatus,9,1)
#define bPCHG_FET_SUCCESS		Write_Bit_Data(&uiPackStatus,10,1)
#define bL0V_SUCCESS			  Write_Bit_Data(&uiPackStatus,11,1)
#define bAFE_ERR_SUCCESS		Write_Bit_Data(&uiPackStatus,12,1)     //标志位.只要有关EEPROM 烧写时遇到的错误
#define bDSGING_SUCCESS		  Write_Bit_Data(&uiPackStatus,14,1)  //代表  有电流流经的标志位   
#define bCHGING_SUCCESS		  Write_Bit_Data(&uiPackStatus,15,1)


		
#define bUTC			Read_Bit_Data(uiBatStatus,0)     //充电低温保护
#define bOTC			Read_Bit_Data(uiBatStatus,1)    //充电高温保护
#define bUTD			Read_Bit_Data(uiBatStatus,2)    //放电低温保护
#define bOTD			Read_Bit_Data(uiBatStatus,3)    //放电高温保护


		
#define bUTC_FALSE			  Write_Bit_Data(&uiBatStatus,0,0)
#define bOTC_FALSE			  Write_Bit_Data(&uiBatStatus,1,0)
#define bUTD_FALSE			  Write_Bit_Data(&uiBatStatus,2,0)
#define bOTD_FALSE			  Write_Bit_Data(&uiBatStatus,3,0)
#define bOV_FALSE	   	  Write_Bit_Data(&uiBatStatus,8,0)       ///而这个要表达的是过压保护
#define bUV_FALSE			  Write_Bit_Data(&uiBatStatus,9,0)        ///我觉得他是不是想要表达的是欠压保护             //  充电高温保护???  44H的第2位    //怎么感觉它又写反了
#define bOCD1_FALSE			Write_Bit_Data(&uiBatStatus,10,0)
#define bOCD2_FALSE			Write_Bit_Data(&uiBatStatus,11,0)
#define bOCC_FALSE			  Write_Bit_Data(&uiBatStatus,12,0)
#define bSC_FALSE			  Write_Bit_Data(&uiBatStatus,13,0)
#define bPF_FALSE			  Write_Bit_Data(&uiBatStatus,14,0)



#define bCHGEnd_FALSE      Write_Bit_Data(&uiPackConfig,8,0)         //FLASH 设定    1110 0000    //也就是,,充电需要不要人来控制
#define bDSGEnd_FALSE      Write_Bit_Data(&uiPackConfig,9,0)
#define bEnEEPRomBK_FALSE  Write_Bit_Data(&uiPackConfig,11,0)        
#define bLEDNum0_FALSE     Write_Bit_Data(&uiPackConfig,12,0)
#define bLEDNum1_FALSE     Write_Bit_Data(&uiPackConfig,13,0)       //定义有多少盏灯
#define bTempNum0_FALSE    Write_Bit_Data(&uiPackConfig,14,0)
#define bTempNum1_FALSE    Write_Bit_Data(&uiPackConfig,15,0)    //定义采集温度的数量




		
#define  bFD_FALSE		  Write_Bit_Data(&uiPackStatus,0,0)  ///现在是纠正回来的状态    ////充电的标志位,,,但是按照45H,,应该是放电的状态位
#define  bFC_FALSE	 	  Write_Bit_Data(&uiPackStatus,1,0)  ///这个位会不会对照错了,,,,这个位对照45H ,,应该是在充电mos的状态位
#define bVDQ_FALSE			Write_Bit_Data(&uiPackStatus,2,0)
//#define bOverLoad		=	3;
#define bBLEOPEN_FALSE		Write_Bit_Data(&uiPackStatus,3,0)
#define bCAL_FALSE		  Write_Bit_Data(&uiPackStatus,4,0)  //是否校正完成标志位  , 完成则校为1
#define bDSG_FET_FALSE		Write_Bit_Data(&uiPackStatus,8,0)
#define bCHG_FET_FALSE		Write_Bit_Data(&uiPackStatus,9,0)
#define bPCHG_FET_FALSE		Write_Bit_Data(&uiPackStatus,10,0)
#define bL0V_FALSE			  Write_Bit_Data(&uiPackStatus,11,0)
#define bAFE_ERR_FALSE		Write_Bit_Data(&uiPackStatus,12,0)     //标志位.只要有关EEPROM 烧写时遇到的错误
#define bDSGING_FALSE		  Write_Bit_Data(&uiPackStatus,14,0)  //代表  有电流流经的标志位   
#define bCHGING_FALSE		  Write_Bit_Data(&uiPackStatus,15,0)




		
#define bUTC_SUCCESS			  Write_Bit_Data(&uiBatStatus,0,1)
#define bOTC_SUCCESS			  Write_Bit_Data(&uiBatStatus,1,1)
#define bUTD_SUCCESS			  Write_Bit_Data(&uiBatStatus,2,1)
#define bOTD_SUCCESS			  Write_Bit_Data(&uiBatStatus,3,1)
#define bOV_SUCCESS	   	  Write_Bit_Data(&uiBatStatus,8,1)       ///而这个要表达的是过压保护
#define bUV_SUCCESS			  Write_Bit_Data(&uiBatStatus,9,1)        ///我觉得他是不是想要表达的是欠压保护             //  充电高温保护???  44H的第2位    //怎么感觉它又写反了
#define bOCD1_SUCCESS			Write_Bit_Data(&uiBatStatus,10,1)
#define bOCD2_SUCCESS			Write_Bit_Data(&uiBatStatus,11,1)
#define bOCC_SUCCESS			  Write_Bit_Data(&uiBatStatus,12,1)
#define bSC_SUCCESS			  Write_Bit_Data(&uiBatStatus,13,1)
#define bPF_SUCCESS			  Write_Bit_Data(&uiBatStatus,14,1)



//00H   系统配置寄存器1
#define  SCONF1_Config         ENPCH1| ENMOS0|OCPM1|BAL1|CH05

#define  ENPCH1   0X80    //启用预充电功能
#define  ENPCH0   0X00    // 禁用预充电功能
#define  ENMOS1   0X40   //启用充电MOSFET恢复控制位。当过充电/温度保护关闭充电MOSFET后，如果检测到放电过流1或者放电状态，则开启充电MOSFET
#define  ENMOS0   0X00   //禁用充电MOSFET恢复控制位
#define  OCPM1    0X20   //充放电过流关闭充放电MOSFET
#define  OCPM0    0X00  //充电过流只关闭充电MOSFET; 放电过流只关闭放电MOSFET
#define  BAL1     0X10  //:平衡开启由外部MCU控制，平衡时序仍由SH367309内部逻辑控制
#define  BAL0     0X00  //平衡开启由SH367309内部逻辑控制
////串数配置
#define  CH05     0x05  //5串电芯应用
#define  CH06     0x06
#define  CH07     0x07
#define  CH08     0x08
#define  CH09     0x09
#define  CH10     0x0A  //10串电芯应用
#define  CH11     0x0B
#define  CH12     0x0C
#define  CH13     0x0D
#define  CH14     0x0E
#define  CH15     0x0F
#define  CH16     0x00  // 16串电芯应用


/////////////////////////////////////////////////////////////////////////////////
//0x01H   系统寄存器2的配置
#define  SCONF2_Config          EOVB1|UV_OP0|DIS_PF1|CTL_Valid|OCRA0|EUVR0
#define  EOVB1                  0X80    //1:开启“禁止低压电芯充电”功能
#define  EOVB0                  0X00    // 关闭“禁止低压电芯充电”功能
#define  UV_OP1                 0X20   //1:过放电关闭充放电MOSFET
#define  UV_OP0                 0X00  //0: 过放电只关闭放电MOSFET;
#define  DIS_PF1                0X10  //:1:禁止二次过充电保护
#define  DIS_PF0                0X00  //0:启用二次过充电保护
#define  CTL_Valid              0X00  //充放电和预充电MOSFET由内部逻辑控制，CTL管脚输入无效
#define  CTL_CH_RECH            0X04  //控制充电和预充电MOSFET。CTL输入VL-CTL电平时强制关闭充电和预充电MOSFET; CTL输入VH-CTL电平时充电和预充电MOSFET由内部逻辑控制
#define   CTL_DI                0X08   //控制放电MOSFET。CTL输入V-cn电平时强制关闭放电MOSFET; CTL输入VH-CTL电平时，放电MOSFET由内部逻辑控制
#define   CTL_CH_RECH_DI        0X0C  //控制充放电和预充电MOSFET。CTL输入VL-CTL电平时强制关闭充放电和预充电MOSFET; CTL输入VH-CTL电平时，充放电和预态电MOSFET由内部逻辑控制
#define    OCRA1                0X02  //1: 允许电流保护定时恢复
#define    OCRA0                0X00  //不允许电流保护定时恢复
#define    EUVR1                0X01  //1:过放电保护状态释放还需负载释放
#define    EUVR0                0X00  //过放电保护状态释放与负载释放无关




////////////////////////////////////////////////////////////////////////////////
///02H   OVh的定义
#define   OV_H_Config         Overcharge_Protect_Time_1s|LOAD_Release_Time_100ms|OV_H_9_8           
#define   Overcharge_Protect_Time_100ms    0X00    //OVTI3:01 = 0000:过充电保护延时 = 100mS
#define   Overcharge_Protect_Time_200ms    0X10 
#define   Overcharge_Protect_Time_300ms    0X20 
#define   Overcharge_Protect_Time_400ms    0X30 
#define   Overcharge_Protect_Time_600ms    0X40 
#define   Overcharge_Protect_Time_800ms    0X50 
#define   Overcharge_Protect_Time_1s       0X60 
#define   Overcharge_Protect_Time_2s       0X70 
#define   Overcharge_Protect_Time_3s       0X80 
#define   Overcharge_Protect_Time_4s       0X90 
#define   Overcharge_Protect_Time_6s       0XA0 
#define   Overcharge_Protect_Time_8s       0XB0 
#define   Overcharge_Protect_Time_10s      0XC0 
#define   Overcharge_Protect_Time_20s      0XD0 
#define   Overcharge_Protect_Time_30s      0XE0 
#define   Overcharge_Protect_Time_40s      0XF0        //OVT[3:0] = 1111:过充电保护延时 = 40S


#define   LOAD_Release_Time_100ms          0X00     //LDRTI1:0] = 00: 负载释放时 = 100mS
#define   LOAD_Release_Time_500ms          0X04
#define   LOAD_Release_Time_1000ms         0X08
#define   LOAD_Release_Time_2000ms         0X0C    //LDRT[1:0] = 11: 负截释放延时 = 2000mS
 
 
 //过充电保护电压:过充电保护电压，计算方式:寄存器值(9-0) X 5mv
#define   OV_H_9_8                        0X03
#define   OV_L_7_0                        0X52    //过充电保护值为4250mv

///////////////////////////////////////////////////////////////////////////////////////////////
//////03h  OVL  过充电保护电压L
#define  OV_L_Config     OV_L_7_0



////////////////////////////////////////////////////////////////////////////////
///04H   OVh的定义
#define   OVR_H_Config         OverDischarge_Protect_Time_1s|OVR_H_9_8           
#define   OverDischarge_Protect_Time_100ms    0X00    //OVrTI3:01 = 0000:过放电保护延时 = 100mS
#define   OverDischarge_Protect_Time_200ms    0X10 
#define   OverDischarge_Protect_Time_300ms    0X20 
#define   OverDischarge_Protect_Time_400ms    0X30 
#define   OverDischarge_Protect_Time_600ms    0X40 
#define   OverDischarge_Protect_Time_800ms    0X50 
#define   OverDischarge_Protect_Time_1s       0X60 
#define   OverDischarge_Protect_Time_2s       0X70 
#define   OverDischarge_Protect_Time_3s       0X80 
#define   OverDischarge_Protect_Time_4s       0X90 
#define   OverDischarge_Protect_Time_6s       0XA0 
#define   OverDischarge_Protect_Time_8s       0XB0 
#define   OverDischarge_Protect_Time_10s      0XC0 
#define   OverDischarge_Protect_Time_20s      0XD0 
#define   OverDischarge_Protect_Time_30s      0XE0 
#define   OverDischarge_Protect_Time_40s      0XF0        //OVT[3:0] = 1111:过放电保护延时 = 40S


 
 //过充电电恢复电压:计算方式:寄存器值(9-0) X 5mv
#define   OVR_H_9_8                        0X03
#define   OVR_L_7_0                        0X34    //过充电恢复电压为4100mv

///////////////////////////////////////////////////////////////////////////////////////////////
//////05h  OVL  过充电保护电压L
#define  OVR_L_Config     OVR_L_7_0           


/////////06H  UV 过放电保护电压设置寄存器
#define   Uv_Config       OverDischarge_Protect_2800

#define   OverDischarge_Protect_2800          0x8c   // 寄存器值*20mV   为2800mV


////////07H  UVR  过放电恢复电压设置

#define   UVR_Config      OverDischarge_Recover_3000
#define   OverDischarge_Recover_3000     0x96      //寄存器*20mV    为3000mV


//////08H   BALV  平衡开启电压设置寄存器
#define   BALV_Config      Balanced_turn_on_voltage_4200
#define   Balanced_turn_on_voltage_4200     0xD2    //寄存器*20mV      4200



/////09h     PREV   预充电电压设置寄存器
#define    PREV_Config         Pre_charge_Voltage_2500
#define    Pre_charge_Voltage_2500      0x7d    //    //寄存器*20mV      2500 
   

/////0Ah  L0V      低电压禁止充电电压设置寄存器
#define     L0V_Config  Low_voltage_prohibits_charging_Voltage_1500
#define    Low_voltage_prohibits_charging_Voltage_1500    0x4b          ///寄存器*20mV       1500


//////0B    PFV   二次过充电保护电压
#define      PFV_Config        Secondary_cha_pro_vol_4500
#define   Secondary_cha_pro_vol_4500       0xE1        //寄存器*20mV     4500


/////0CH   OCD1V/OCD1T  过放电流1保护电压/过放电流1的保护延时
#define      OCD1V_OCD1T_Config      Discharge1_Overcurrent_Protect_Voltage_70mV|Discharge1_Overcurrent_Protect_Time_1s    

//过放电流1保护电压设置控制位
#define   Discharge1_Overcurrent_Protect_Voltage_20mV    0x00
#define   Discharge1_Overcurrent_Protect_Voltage_30mV    0x10
#define   Discharge1_Overcurrent_Protect_Voltage_40mV    0x20
#define   Discharge1_Overcurrent_Protect_Voltage_50mV    0x30
#define   Discharge1_Overcurrent_Protect_Voltage_60mV    0x40
#define   Discharge1_Overcurrent_Protect_Voltage_70mV    0x50
#define   Discharge1_Overcurrent_Protect_Voltage_80mV    0x60
#define   Discharge1_Overcurrent_Protect_Voltage_90mV    0x70
#define   Discharge1_Overcurrent_Protect_Voltage_100mV   0x80
#define   Discharge1_Overcurrent_Protect_Voltage_110mV   0x90
#define   Discharge1_Overcurrent_Protect_Voltage_120mV   0xA0
#define   Discharge1_Overcurrent_Protect_Voltage_130mV   0xB0
#define   Discharge1_Overcurrent_Protect_Voltage_140mV   0xC0
#define   Discharge1_Overcurrent_Protect_Voltage_160mV   0xD0
#define   Discharge1_Overcurrent_Protect_Voltage_180mV   0xE0
#define   Discharge1_Overcurrent_Protect_Voltage_200mV   0xF0


///放电过流1保护延时设置控制位
#define   Discharge1_Overcurrent_Protect_Time_50ms    0x00
#define   Discharge1_Overcurrent_Protect_Time_100ms   0x01
#define   Discharge1_Overcurrent_Protect_Time_200ms   0x02
#define   Discharge1_Overcurrent_Protect_Time_400ms   0x03
#define   Discharge1_Overcurrent_Protect_Time_600ms   0x04
#define   Discharge1_Overcurrent_Protect_Time_800ms   0x05
#define   Discharge1_Overcurrent_Protect_Time_1s      0x06
#define   Discharge1_Overcurrent_Protect_Time_2s      0x07
#define   Discharge1_Overcurrent_Protect_Time_4s      0x08
#define   Discharge1_Overcurrent_Protect_Time_6s      0x09
#define   Discharge1_Overcurrent_Protect_Time_8s      0x0A
#define   Discharge1_Overcurrent_Protect_Time_10s     0x0B
#define   Discharge1_Overcurrent_Protect_Time_15s     0x0C
#define   Discharge1_Overcurrent_Protect_Time_20s     0x0D
#define   Discharge1_Overcurrent_Protect_Time_30s     0x0E
#define   Discharge1_Overcurrent_Protect_Time_40s     0x0F



/////0DH   OCD2V/OCD2T  过放电流1保护电压/过放电流1的保护延时
#define      OCD2V_OCD2T_Config      Discharge2_Overcurrent_Protect_Voltage_200mV|Discharge2_Overcurrent_Protect_Time_4s    

//过放电流2保护电压设置控制位
#define   Discharge2_Overcurrent_Protect_Voltage_30mV    0x00
#define   Discharge2_Overcurrent_Protect_Voltage_40mV    0x10
#define   Discharge2_Overcurrent_Protect_Voltage_50mV    0x20
#define   Discharge2_Overcurrent_Protect_Voltage_60mV    0x30
#define   Discharge2_Overcurrent_Protect_Voltage_70mV    0x40
#define   Discharge2_Overcurrent_Protect_Voltage_80mV    0x50
#define   Discharge2_Overcurrent_Protect_Voltage_90mV    0x60
#define   Discharge2_Overcurrent_Protect_Voltage_100mV    0x70
#define   Discharge2_Overcurrent_Protect_Voltage_120mV   0x80
#define   Discharge2_Overcurrent_Protect_Voltage_140mV   0x90
#define   Discharge2_Overcurrent_Protect_Voltage_160mV   0xA0
#define   Discharge2_Overcurrent_Protect_Voltage_180mV   0xB0
#define   Discharge2_Overcurrent_Protect_Voltage_200mV   0xC0
#define   Discharge2_Overcurrent_Protect_Voltage_300mV   0xD0
#define   Discharge2_Overcurrent_Protect_Voltage_400mV   0xE0
#define   Discharge2_Overcurrent_Protect_Voltage_500mV   0xF0


///放电过流2保护延时设置控制位
#define   Discharge2_Overcurrent_Protect_Time_50ms    0x00
#define   Discharge2_Overcurrent_Protect_Time_100ms   0x01
#define   Discharge2_Overcurrent_Protect_Time_200ms   0x02
#define   Discharge2_Overcurrent_Protect_Time_400ms   0x03
#define   Discharge2_Overcurrent_Protect_Time_600ms   0x04
#define   Discharge2_Overcurrent_Protect_Time_800ms   0x05
#define   Discharge2_Overcurrent_Protect_Time_1s      0x06
#define   Discharge2_Overcurrent_Protect_Time_2s      0x07
#define   Discharge2_Overcurrent_Protect_Time_4s      0x08
#define   Discharge2_Overcurrent_Protect_Time_6s      0x09
#define   Discharge2_Overcurrent_Protect_Time_8s      0x0A
#define   Discharge2_Overcurrent_Protect_Time_10s     0x0B
#define   Discharge2_Overcurrent_Protect_Time_15s     0x0C
#define   Discharge2_Overcurrent_Protect_Time_20s     0x0D
#define   Discharge2_Overcurrent_Protect_Time_30s     0x0E
#define   Discharge2_Overcurrent_Protect_Time_40s     0x0F




///// 0E  短路保护设置寄存器
#define   SCV_SCT_Config             Short_circuit_Protection_Voltage_320mV|Short_circuit_Protection_Time_256us      
//短路保护保护电压设置控制位
#define   Short_circuit_Protection_Voltage_50mV     0x00
#define   Short_circuit_Protection_Voltage_80mV     0x10
#define   Short_circuit_Protection_Voltage_110mV    0x20
#define   Short_circuit_Protection_Voltage_140mV    0x30
#define   Short_circuit_Protection_Voltage_170mV    0x40
#define   Short_circuit_Protection_Voltage_200mV    0x50
#define   Short_circuit_Protection_Voltage_230mV    0x60
#define   Short_circuit_Protection_Voltage_260mV    0x70
#define   Short_circuit_Protection_Voltage_290mV    0x80
#define   Short_circuit_Protection_Voltage_320mV    0x90
#define   Short_circuit_Protection_Voltage_350mV    0xA0
#define   Short_circuit_Protection_Voltage_400mV    0xB0
#define   Short_circuit_Protection_Voltage_500mV    0xC0
#define   Short_circuit_Protection_Voltage_600mV    0xD0
#define   Short_circuit_Protection_Voltage_800mV    0xE0
#define   Short_circuit_Protection_Voltage_1000mV   0xF0


///短路保护保护延时设置控制位
#define   Short_circuit_Protection_Time_0us       0x00
#define   Short_circuit_Protection_Time_64us      0x01
#define   Short_circuit_Protection_Time_128us     0x02
#define   Short_circuit_Protection_Time_192us     0x03
#define   Short_circuit_Protection_Time_256us     0x04
#define   Short_circuit_Protection_Time_320us     0x05
#define   Short_circuit_Protection_Time_384us     0x06
#define   Short_circuit_Protection_Time_448us     0x07
#define   Short_circuit_Protection_Time_512us     0x08
#define   Short_circuit_Protection_Time_576us     0x09
#define   Short_circuit_Protection_Time_640us     0x0A
#define   Short_circuit_Protection_Time_704us     0x0B
#define   Short_circuit_Protection_Time_768us     0x0C
#define   Short_circuit_Protection_Time_832us     0x0D
#define   Short_circuit_Protection_Time_896us     0x0E
#define   Short_circuit_Protection_Time_960us     0x0F



/////0FH   OCCV/OCCT    充电过流保护电压/充电过流保护延时
#define      OCCV_OCCT_Config      Charge_Overcurrent_Protect_Voltage_20mV|Charge_Overcurrent_Protect_Time_1s    

//充电过流保护电压保护电压设置控制位
#define   Charge_Overcurrent_Protect_Voltage_20mV    0x00
#define   Charge_Overcurrent_Protect_Voltage_30mV    0x10
#define   Charge_Overcurrent_Protect_Voltage_40mV    0x20
#define   Charge_Overcurrent_Protect_Voltage_50mV    0x30
#define   Charge_Overcurrent_Protect_Voltage_60mV    0x40
#define   Charge_Overcurrent_Protect_Voltage_70mV    0x50
#define   Charge_Overcurrent_Protect_Voltage_80mV    0x60
#define   Charge_Overcurrent_Protect_Voltage_90mV    0x70
#define   Charge_Overcurrent_Protect_Voltage_100mV   0x80
#define   Charge_Overcurrent_Protect_Voltage_110mV   0x90
#define   Charge_Overcurrent_Protect_Voltage_120mV   0xA0
#define   Charge_Overcurrent_Protect_Voltage_130mV   0xB0
#define   Charge_Overcurrent_Protect_Voltage_140mV   0xC0
#define   Charge_Overcurrent_Protect_Voltage_160mV   0xD0
#define   Charge_Overcurrent_Protect_Voltage_180mV   0xE0
#define   Charge_Overcurrent_Protect_Voltage_200mV   0xF0


///充电过流保护电压保护延时设置控制位
#define   Charge_Overcurrent_Protect_Time_10ms      0x00
#define   Charge_Overcurrent_Protect_Time_20ms      0x01
#define   Charge_Overcurrent_Protect_Time_40ms      0x02
#define   Charge_Overcurrent_Protect_Time_60ms      0x03
#define   Charge_Overcurrent_Protect_Time_80ms      0x04
#define   Charge_Overcurrent_Protect_Time_100ms     0x05
#define   Charge_Overcurrent_Protect_Time_200ms     0x06
#define   Charge_Overcurrent_Protect_Time_400ms     0x07
#define   Charge_Overcurrent_Protect_Time_600ms     0x08
#define   Charge_Overcurrent_Protect_Time_800ms     0x09
#define   Charge_Overcurrent_Protect_Time_1s        0x0A
#define   Charge_Overcurrent_Protect_Time_2s        0x0B
#define   Charge_Overcurrent_Protect_Time_4s        0x0C
#define   Charge_Overcurrent_Protect_Time_8s        0x0D
#define   Charge_Overcurrent_Protect_Time_10s       0x0E
#define   Charge_Overcurrent_Protect_Time_20s       0x0F


//////10H    充放电过流自动恢复/二次过充电保护延时设置寄存器
#define   MOST_OCRT_PFT    CHS1_CHS0|MOST1_MOST0|OCRT1_OCRT0|PFT1_PFT_Conf
#define   CHS1_CHS0     Char_DisChar_Status_Check_Voltage_1000uV
#define   Char_DisChar_Status_Check_Voltage_200uV    0x00    //充放电状态检测电压 200uV
#define   Char_DisChar_Status_Check_Voltage_500uv    0x40 
#define   Char_DisChar_Status_Check_Voltage_1000uV   0x80
#define   Char_DisChar_Status_Check_Voltage_2000uv   0xC0 

#define   MOST1_MOST0   Char_DisChar_Mos_Delay_Time_64us
#define   Char_DisChar_Mos_Delay_Time_64us       0x00    //充放电mos开启延时   64us
#define   Char_DisChar_Mos_Delay_Time_128us      0x10
#define   Char_DisChar_Mos_Delay_Time_256us      0x20
#define   Char_DisChar_Mos_Delay_Time_512us      0x30 


#define   OCRT1_OCRT0    Char_DisChar_OverCurrent_Recover_Delay_Time_8s
#define   Char_DisChar_OverCurrent_Recover_Delay_Time_8s    0x00     //充放电过流自恢复延时  8s
#define   Char_DisChar_OverCurrent_Recover_Delay_Time_16s   0x04
#define   Char_DisChar_OverCurrent_Recover_Delay_Time_32s   0x08
#define   Char_DisChar_OverCurrent_Recover_Delay_Time_64s   0x0C
 
#define   PFT1_PFT_Conf            Secondary_Overcharge_Protect_Delay_Time_8s     
#define   Secondary_Overcharge_Protect_Delay_Time_8s      0x00    //二次过充电保护延时  8s
#define   Secondary_Overcharge_Protect_Delay_Time_16s     0x01
#define   Secondary_Overcharge_Protect_Delay_Time_32s     0x02
#define   Secondary_Overcharge_Protect_Delay_Time_64s     0x03




#define  OTC_Config     0x3b   //11H    充电高温保护设置寄存器     59
#define  OTCR_Config    0x36   //12H     充电高温保护释放寄存器     54
#define  UTC_Config     0xff   //13H     充电低温保护设置寄存器      255
#define  UTCR_Config    0x04   //14H     充电低温保护释放设置寄存器   4
#define  OTD_Config     0x45   //15H     放电高温保护设置寄存器       69
#define  OTDR_Config    0x40   //16H     放电高温保护释放寄存器       64
#define  UTD_Config     0xfa   //17H      放电低温保护设置寄存器     
#define  UTDR_Config    0xFF   //18H    放电低温保护释放阈值

#define  TR_Config      0x46    //19H        温度内部参考电阻系数   //需要注意的是这个是只读的.!!!!!!!!!!!!

/***********************EEprom外置的标志位******************/
extern ErrorStatus  EEprom_Written;
extern ErrorStatus  EEprom_Error_AFE;   //SUCCESS  代表有错误,,false  无错误

























//*****************************BIT MEMORY START***************************//

extern uint16_t       uiPackConfig;				//0x000,0x0E0   对照E2uiPackConfigMap的值
extern uint16_t       uiPackStatus;				
extern uint16_t       uiBatStatus;





extern ErrorStatus bWakeupFlg;						//唤醒标志，系统从低功耗被唤醒
extern ErrorStatus bCADCFlg;						//CADC转码完成标志
extern ErrorStatus bCalibrationFlg;				//上位机发送校准命令后置位该标志
extern ErrorStatus bWrFlashFlg;					//写FLASH标志
extern ErrorStatus bE2PProcessFlg;					//EEPROM处理标志
extern ErrorStatus bISPFlg;						//ISP升级标志，进入ISP程序
extern ErrorStatus bTimerFlg;						//1s定时器标志
extern ErrorStatus bIdleTimerFlg;					//5s定时器标志
extern ErrorStatus bHalfHzFlg;						//0.5HZ标志（用于LED显示蓝牙状态）
extern ErrorStatus b2HzFlg;						//2HZ标志（用于LED显示蓝牙状态）
extern ErrorStatus bIdleFlg;						//系统进入IDLE标志
extern ErrorStatus bSleepFlg;						//系统进入SLEEP标志
extern ErrorStatus bPCSleepFlg;					//PC通知系统进入SLEEP标志
extern ErrorStatus bLEDOpen;						//LED电量显示标志
extern ErrorStatus bLEDFlg;						//LED电量显示过程中
extern ErrorStatus bLongKeyFlg;					//按键长按检测标志
extern ErrorStatus bBleOnOffFlg;					//蓝牙启停标志
extern ErrorStatus bUartSndAckFlg;					//UART已经发送ACK给主机
extern ErrorStatus bUartNeedAckFlg;				//UART需要发送ACK给主机
extern ErrorStatus bCHGClosedFlg;					//充电结束关闭充电MOS标志
extern ErrorStatus bDSGClosedFlg;					//放电结束关闭放电MOS标志
extern ErrorStatus bProtectFlg;					//保护发生标志，需要从低功耗唤醒(未置位，恒为0)
extern ErrorStatus bAFEFlg;						//AFE的ALARM发生标志

extern ErrorStatus bDsgToChgFlg;					//放电转换为充电，需要备份数据
extern ErrorStatus bChgToDsgFlg;					//充电转换为放电，需要备份数据
extern ErrorStatus bLVBkFlg;						//LV低电压标志，需要备份信息到外挂EEPROM
extern ErrorStatus bE2PBKDsgEnd;					//放电结束标志，需要备份信息到外挂EEPROM
extern ErrorStatus bE2PBKChgStop;					//充电结束标志，需要备份信息到外挂EEPROM
extern ErrorStatus bE2PBKChgStart;					//充电开始标志，需要备份信息到外挂EEPROM
extern ErrorStatus bE2PBKRtc;						//RTC定时备份标志，需要备份信息到外挂EEPROM
extern ErrorStatus bE2PErase;						//擦除外挂EEPROM标志
extern ErrorStatus bE2PRdData;						//读取外挂EEPROM标志
extern ErrorStatus bRTCRdTime;						//读取RTC时间标志
//extern ErrorStatus bE2ON;				            //E2ON(0：外挂E2需初始化。1：外挂E2无需初始化。)
//extern ErrorStatus bRTCON;							//RTCON(0：外挂RTC需初始化。1：外挂RTC无需初始化。)

extern uint16_t     NTC103AT[161];				//热敏电阻NTC103AT阻值表

//*****************************     MEMORY START***************************//
extern uint8_t    STACK[];		//堆栈

extern uint8_t       ucResetFlag;				//PC to send a software reset instruction
extern uint8_t       ucTimer0Cnt;				//Timer0 counter, Every 20ms +1
extern uint8_t       ucTimer0Cnt1;				
extern uint8_t       ucFlashWrValid;				//Write flash protect flag
extern uint8_t       ucKeyDownCnt;				//Key Down state counter
extern uint8_t        ucCellNum;					//For storage cell num
extern uint16_t      uiCellVmax;					//The maximum value of all the Cell
extern uint16_t      uiCellVmin;					//The minimum value of all the Cell
extern uint8_t       ucUartTimeCnt;				//Uart no communication timing, for enter sleep or idle
extern uint8_t       ucIdleTimeCnt;				//idle counter
extern int16_t       siCurBuf[12];				//for storage CADC value, Is used to calculate the mean Within 1s
extern uint8_t       ucCadcTimeCnt;				//for storage CADC value, Is used to calculate the mean Within 1s
extern uint8_t       ucChgEndTimeCnt;			//Charging cut-off delay count
extern uint8_t       ucChgEndRTimeCnt;
extern uint8_t       ucDsgEndTimeCnt;			//Discharging cut-off delay count
extern uint8_t       ucDsgEndRTimeCnt;			//Discharging cut-off delay count
extern uint8_t       ucBalanceTimeCnt[16];		//Balance time counter(for each cell)
extern uint8_t       ucBalUpdateTimeCnt;			//Balance update time counter
extern uint16_t      uiBalanceChannel;			//Balance Channel
extern uint8_t       ucLEDTimeCnt;				//LED display delay count

extern uint8_t        ucExtcaliSwitch1;			//calibration flag      //校准标志位
extern uint8_t        ucExtcaliFlag;				//calibration flag
extern uint32_t       ulExtVPack;				//During calibration, the received total voltage
extern uint32_t       slExtCur;					//During calibration, the received current
extern uint16_t       uiExtTemp1;				//During calibration, the received ttemperature1
extern uint16_t       uiExtTemp2;				//During calibration, the received ttemperature2
extern uint16_t       uiExtTemp3;				//During calibration, the received ttemperature3
extern uint8_t        ucTempeMiddle;				//Record the current temperature resistance corresponding address, for the next quick look
extern uint8_t        ucExtRTC[6];				//During calibration, the received RTC Time


extern uint8_t        ucMTPConfVal;				//for MTP CONF Register

extern uint32_t       ulRCCharge;				//Charge capacity statistics
extern uint32_t       ulRCDischarge;				//Discharge capacity statistics
extern uint32_t       ulDsgCycleCount;			//Discharge capacity statistics, for update E2uiCycleCount
extern uint32_t       ulFCCCount;				//The effective discharge capacity statistics, for updating E2ulFCC    //放电容量

extern uint16_t       uiE2PDataAddr;
extern uint8_t        ucRTCBKTime1;
extern uint16_t       uiRTCBKTime2;
extern uint8_t        ucRTCBuf[];
extern uint8_t    ucUpDataLimitTime;

extern uint16_t       uiCHGValidTime;

extern ErrorStatus bUartReadFlg;
extern ErrorStatus bUartWriteFlg;
extern uint8_t       ucSubClassID;
extern uint8_t       ucUartBufPT;			//Pointing to the current UART Buffer
extern uint8_t       ucUartSndLength;		//UART Buffer send length
extern uint8_t       ucUartTimeoutCnt;		//UART timerout cnt, If not Uart communication within 2s, then clear ucUartBufPT
extern uint8_t       ucUartBuf[];			//For UART transmit or acceptance buffer




//*****************************      MEMORY START***************************//
//系统参数，子命令号：0x00
extern uint16_t       E2uiPackConfigMap;
extern uint16_t       E2uiVOC[11];   //初始化时  用来表示容量的大小,通过逼近法去逼近;
extern uint32_t       E2ulDesignCap;
extern uint32_t       E2ulFCC;
extern uint32_t       E2ulCycleThreshold;
extern uint16_t       E2uiCycleCount;
extern uint16_t       E2uiNearFCC;
extern uint16_t       E2siLearnLowTemp;
extern uint16_t       E2siDfilterCur;
extern uint8_t        E2ucSleepDelay;
extern uint8_t        E2ucIdleDelay;
extern uint8_t        E2ucCommOffDelay;
extern uint8_t        E2ucChgBKDelay;
extern uint16_t       E2siChgBKCur;
extern uint8_t        E2ucRTCBKDelay;
extern uint8_t        E2ucRamCheckFlg1;

//用户自定义A区，子命令号：0x01
extern uint16_t       E2uiSWVersion;
extern uint16_t       E2uiHWVersion;
extern uint8_t        E2ucID;
extern uint8_t        E2ucMNFName[];
extern uint32_t       E2ulMNFDate;
extern uint16_t       E2uiSerialNum;
extern uint8_t        E2ucDeviceName[];
extern uint8_t        E2ucDeviceChem[];
extern uint16_t       E2uiChemID;
extern uint8_t        E2ucRamCheckFlg2;

//充电参数，子命令号：0x02
extern uint16_t       E2uiChgEndVol;
extern uint16_t       E2siChgEndCur;
extern uint8_t        E2ucChgEndDelay;
extern uint8_t        E2ucRamCheckFlg3;

//平衡参数，子命令号：0x08
extern uint16_t       E2uiBalanceVol;
extern uint16_t       E2siBalanceCur;
extern uint16_t       E2uiBalanceVolDiff;      //最大和最小的电压  ,相差最大的值
extern uint8_t        E2ucBalanceDelay;
extern uint8_t        E2ucRamCheckFlg4;

//放电参数，子命令号：0x03
extern uint16_t       E2uiDsgEndVol;
extern uint8_t        E2ucDsgEndDelay;
extern uint8_t        E2ucRamCheckFlg5;
extern float  RES_SENSE;
//AFE参数，子命令号：0x0A
extern uint8_t        ucMTPBuffer[26];      //存放着EEprom里面的指令,非常的重要,需要被写到EEprom里面
extern uint8_t        E2ucRamCheckFlg6;

//校准参数，子命令号：0x0B
extern uint16_t       E2uiVPackGain;
extern float          E2siCadcGain_Cha;
extern float          E2siCadcGain_Dio;
extern uint16_t       E2siCadcZero;
extern uint16_t       E2siTempe1Offset;
extern uint16_t       E2siTempe2Offset;
extern uint16_t       E2siTempe3Offset;
extern uint8_t        E2ucCalibrated;
extern uint8_t        E2ucRamCheckFlg7;

//类E2写入OK标志
extern uint16_t       E2uiCheckFlag;






typedef struct	_SYSINFOR_							
{
	uint16_t		VCell[16];      //用于记录对应的电压值,而这个每个串数值,即数组存放的数据是累加的
	uint32_t		Voltage;             //存放最高串的电压值
	int32_t		CurCadc;             // 存放测量的电流值              ///s32
	uint16_t		Temperature1;                  //记录由SH367数组40H 的温度数据计算后值,或许可以记录其他的值
	uint16_t		Temperature2;
	uint16_t		Temperature3;
	uint32_t		E2ulFCC;                 ///可能是总容量    ,,//也有可能是充电冲的电量                 
	uint32_t		RC;                     //采集::::安时积分 然后乘以百分比获取的容量  ,此时的容量    ,,,,,单位是毫安时,可能单位会不会不对
	uint16_t		RSOC;            //此时电池的容量     0   10  20  30来记录   
	uint16_t		E2uiCycleCount;
	uint16_t		PackStatus;                  //系统状态
	uint16_t		BatStatus;
	uint16_t		PackConfig;
	uint16_t		ManufactureAccess;
}SYSINFOR;

extern SYSINFOR		Info;

typedef struct	_AFEDATA_
{
	uint16_t Temp1;       //记录电压的值
	uint16_t Temp2;
	uint16_t Temp3;
	uint16_t Cur1;
	uint16_t Cell[16];   //记录每个串数电压的值,这个是乱序插的
	uint16_t Cadc;
}AFEDATA;      //数组,存放有关电压平衡的数据

extern AFEDATA  AFE;


typedef struct _RTC_VAR_					//BCD Type
{
	uint8_t Second;
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Week;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
}RTC_VAR;
extern RTC_VAR  RTC_data;
extern uint16_t   uiE2PDataAddr;
extern uint8_t    ucRTCBKTime1;
extern uint16_t   uiRTCBKTime2;
extern uint8_t    ucRTCBuf[];


void  Write_Bit_Data(uint16_t *Status_Flag,uint8_t wei,uint16_t Action);
ErrorStatus  Read_Bit_Data(uint16_t Status_Flag,uint8_t wei);




void Memory_SysInit_Assign(void);




















#endif











