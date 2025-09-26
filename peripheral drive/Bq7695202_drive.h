#ifndef  _Bq7695202_drive_H
#define  _Bq7695202_drive_H

#include "stm32f10x.h"




#define  Current_Mode_Set              0x00      //100mA  //3 0.1mA  2 1mA  1 10mA  0  100mA
#define  Cell_Voltage_Limit_Low        2700      //mV
#define  Cell_Voltage_Limit_High       3500      //mV
#define  Tol_Vol_Alarm_Low             41000     //41V=41000mV
#define  Tol_Vol_Alarm_High            56000     //56V=56000mV 
#define  Tol_Vol_Pro_Low             39500     //41V=41000mV
#define  Tol_Vol_Pro_High            57620     //56V=56000mV 
#define  Charge_Current_Alarm_High     45000     //45A  
#define  Discha_Current_Alarm_High     -90000     //90A
#define  Tempt_Alarm_Low               -10        //50摄氏度  //报警
#define  Tempt_Alarm_High              50       //-10摄氏度 //报警
#define  Env_Tempt_Alarm_Low            -15     //环境报警
#define  Env_Tempt_Alarm_High            60     //环境报警
#define  Env_Tempt_Pro_Low             -20      //环境低温保护
#define  Env_Tempt_Pro_High            70       //环境高温保护
#define  Mos_Temp_Alarm_High           100     //MOS报警
#define  SOC_LOW                        5
#define  SOC_High                      98

typedef enum 
{
	Vol_Check,
  Cur_Check,
	Tempt_Check,
	Bit_Check,
}Battery_Enum;


typedef enum 
{
	Commute_Error=0, //通讯异常
  Task_OK=1,      //完成正常
	Mode_Error=2,   //未退出CFGR模式
	Write_Error=3,    //写入错误
	Flash_Erase_Error=4,
	Flash_Write_Error=5,
	Flash_Match_Error=6,
}Init_Error_Enum;



typedef enum 
{
	Init_Setting=0,      //初始设置   //取消设置
  Flash_Setting=1,     //flash设置
	Change_Setting=2,    //上位机设置
	BQ_Stdio_Ready=3,   //battery_Manage setting  //准备完成
	BQ_Stdio_Set_Done=4,    //进行设置   //设置完成
}IC_Setting_Mode;




typedef enum
{
 Inttem_Num=0,
 CFETOFFtem_Num,
 DFETOFFtem_Num,
 ALERTtem_Num,
 TS1tem_Num,
 TS2tem_Num,
 TS3tem_Num,
 HDQtem_Num,
 DCHGtem_Num,
 DDSGtem_Num,
}Temp_Num_Enum;

// 模拟量数据结构
typedef struct 
{
	  uint8_t Command;              //同ADDR，02H
	  uint8_t  Cell_Number;         //电池单体个数
    uint16_t cell_voltages[16];   // 单体电压（nV）
	  uint8_t  Tempt_Number;        //监测温度个数
    float temperatures[10];     // 温度（0.1K）
    int16_t pack_current;         // 电流（10mA）
    uint16_t pack_voltage;        // 总电压（nV）
    uint16_t remaining_capacity;  // 剩余容量（10mAh）
	  uint8_t  Ramdom_Number;       //03H
    uint16_t full_capacity;       // 满充容量（10mAh）
	  uint16_t cycle_count;         // 循环次数
    uint16_t design_capacity;     // 设计容量（10mAh）  
    uint16_t Stack_Voltage;
	  uint16_t LD_Voltage;
	  uint16_t Pack_Voltage;
	  float    Ideal_SOC;               //理想SOC
	  float    Actual_SOC;              //实际SOC
	  uint16_t CB_Cells_Index;
}BatteryData; 

typedef struct 
{
		union {
        uint8_t Safety_Alert_A;   //在触发启用的安全警报时提供单独的警报信号。S
			struct {
           	uint8_t reserved : 2; 
						uint8_t CUV : 1;    // 芯欠压保护
						uint8_t COV : 1;       // 电芯过压保护
						uint8_t OCC :1;//充电过流保护
						uint8_t OCD1 : 1;// 放电过流 1 级保护
						uint8_t OCD2 : 1; // 放电过流 2 级保护
						uint8_t  SCD : 1;  // 放电短路保护
        } Safety_Alert_A_bits;
    };	
		union {
        uint8_t Safety_Satus_A; 
			struct {
					uint8_t reserved : 2; 
				  uint8_t CUV : 1;    // 芯欠压保护
				  uint8_t COV : 1;       // 电芯过压保护
				  uint8_t OCC :1;//充电过流保护
				  uint8_t OCD1 : 1;// 放电过流 1 级保护
				  uint8_t OCD2 : 1; // 放电过流 2 级保护
				  uint8_t  SCD : 1;  // 放电短路保护
        } Safety_Satus_A_bits;
    };
		union {
        uint8_t Safety_Alert_B; 
			struct {
         uint8_t UTC : 1;   //充电欠温
				 uint8_t UTD : 1;    // 放电欠温
				 uint8_t UTINT : 1;       // 内部欠温
				 uint8_t reserved : 1; 
				 uint8_t OTC :1;//充电过热
				 uint8_t OTD : 1;// 放电过热
				 uint8_t OTINT : 1; // 内部过热
				 uint8_t  OTF : 1;  // FET 过热
        } Safety_Alert_B_bits;
    };	
		union {
        uint8_t Safety_Satus_B; 
			struct {
         uint8_t UTC : 1;   //充电欠温
				 uint8_t UTD : 1;    // 放电欠温
				 uint8_t UTINT : 1;       // 内部欠温
				 uint8_t reserved : 1; 
				 uint8_t OTC :1;//充电过热
				 uint8_t OTD : 1;// 放电过热
				 uint8_t OTINT : 1; // 内部过热
				 uint8_t  OTF : 1;  // FET 过热
        } Safety_Satus_B_bits;
    };
		union {
        uint8_t Safety_Alert_C; 
			struct {
				 uint8_t reserved3 : 3;
				 uint8_t PTOS : 1;   //预充电超时				
				 uint8_t COVL :1;//电芯过压锁存				
				 uint8_t OCDL : 1;// 放电过流锁存
				 uint8_t SCDL : 1; // 放电短路锁存
         uint8_t OCD3 : 1;  // 放电过流 3 级保护  
        } Safety_Alert_C_bits;
    };
		union {
        uint8_t Safety_Satus_C; 
			struct {
         uint8_t reserved2 : 1;
				 uint8_t HWDL : 1;   //主机看门狗故障
				 uint8_t PTO : 1;   //预充电超时		
         uint8_t reserved1 : 1;				
				 uint8_t COVL :1;//电芯过压锁存	
				 uint8_t OCDL : 1;// 放电过流锁存
				 uint8_t SCDL : 1; // 放电短路锁存
         uint8_t OCD3 : 1;  // 放电过流 3 级保护  
        } Safety_Satus_C_bits;
    };
		uint8_t  PF_Alert_A;
		uint8_t  PF_Status_A;
		uint8_t  PF_Alert_B;
		union {
        uint8_t PF_Status_B;             //用于使 ALERT 引脚生效的锁存信号。向某个位写入高电平以清除锁存
			struct {
				uint8_t CFET : 1;         //充电MOS FET
				uint8_t DFET : 1;          //放电MOS FET
				uint8_t V2LVL : 1;            //二级保护器永久失效
				uint8_t VIMR : 1;        //静态模式电压不平衡永久失效
				uint8_t VIMA : 1;          //激活模式电压不平衡永久失效
				uint8_t Reservr3:3;        //reserve 位
        } PF_Status_B_Bits;
     };
		uint8_t  PF_Alert_C;
		uint8_t  PF_Status_C;
		uint8_t  PF_Alert_D;
		uint8_t  PF_Status_D;   //  PFStatusD 0x11
		union {
	  	uint16_t Bat_Sta;       //	BatteryStatus 0x12
			struct {
				uint16_t CFGR_Update:1;
				uint16_t RESERVE :15;
			}Bat_Sta_bits;
		};
			union {
        uint16_t Alarm_Sta;             //用于使 ALERT 引脚生效的锁存信号。向某个位写入高电平以清除锁存
			struct {
				uint16_t WAKE : 1;          //当器件从 SLEEP 模式唤醒时会设置该位
				uint16_t ADSCAN : 1;        //电压 ADC 扫描完成
				uint16_t CB : 1;            //当电芯平衡处于活动状态时会设置该位
				uint16_t FUSE : 1;          //驱动 FUSE 引脚。FUSE 引脚由器件或次级保护器驱动。
				uint16_t SHUTV : 1;         //电池组电压低于 Power:Shutdown:Shutdown Stack Voltage。
				uint16_t XDSG : 1;          //当 DSG FET 关断时会设置该位。
				uint16_t XCHG : 1;          //当 CHG FET 关断时会设置该位。
				uint16_t FULLSCAN : 1;      //完整电压扫描完成
				uint16_t Reserved1 :1;      //
				uint16_t INITCOMP : 1;      // 初始化已完成
				uint16_t INITSTART : 1;     //初始化已开始
				uint16_t MSK_PFALERT : 1;   //当永久失效警报被触发， 
				uint16_t MSK_SFALERT  :1;   //当安全警报被触发
				uint16_t PF : 1;            // 当触发启用的永久失效故障时，会设置该位。
				uint16_t SSA : 1;           // 当 Safety Status A() 中设置了某个位时，会设置该位
		  	uint16_t  SSBC : 1;         // 当 Safety Status B() 或 Safety Status C() 中设置了某个位时，会设置该位	
        } Alarm_Sta_bits;
    };
		uint16_t Alarm_Raw_Sta;
		uint16_t Alarm_Enable;
		union {
        uint8_t FET_Status; 
			struct {
				 uint8_t  reserved1 : 1;  //
				 uint8_t ALRT_PIN : 1;    // 指示 ALERT 引脚的状态。
				 uint8_t DDSG_PIN : 1;    // 指示 DDSG 引脚的状态。
				 uint8_t DCHG_PIN  :1;    //指示 DCHG 引脚的状态
				 uint8_t PDSG_FET : 1;    //指示 PDSG FET 的状态。
				 uint8_t DSG_FET : 1;     //指示 DSG FET 的状态
				 uint8_t PCHG_FET : 1;    // 指示 PCHG FET 的状态。
				 uint8_t CHG_FET : 1;     //指示 CHG FET 的状态。
        } FET_Status_bits;
    };
		union {
        uint8_t Bata_Flag; 
			struct {
            uint8_t  Pro_Tri : 1;  //触发了保护
            uint8_t Reserved : 7;  // 
        } Bata_Flag_bits;};	
}Battery_Status_Str;




// 告警量数据结构
typedef struct {
    uint8_t Command;                    //同ADDR，02H
	  uint8_t Cell_Number;                //电池单体个数
	  uint8_t cell_alarms[16];           // 单体电压告警
	  uint8_t Tempt_Number;               //监测温度个数
    uint8_t temp_alarms[8];             // 温度告警
    uint8_t charge_current_alarm;       //充电电流警告
    uint8_t pack_voltage_alarm;         //pack总电压警告
    uint8_t discharge_current_alarm;    //放电电流警告
	union {
        uint8_t protection_status1;  // 表A.17
        struct {
            uint8_t single_cell_overvoltage : 1;  // BIT0: 单体过压保护
            uint8_t single_cell_undervoltage : 1; // BIT1: 单体过放保护
            uint8_t total_voltage_overvoltage : 1;// BIT2: 总压过压保护
            uint8_t total_voltage_undervoltage :1;// BIT3: 总压过放保护
            uint8_t charge_overcurrent : 1;       // BIT4: 充电过流保护
            uint8_t discharge_overcurrent : 1;    // BIT5: 放电过流保护
            uint8_t short_circuit : 1;            // BIT6: 短路保护
            uint8_t reserved1 : 1;                // BIT7: 预留
        } protection_status1_bits;
    };

    union {
        uint8_t protection_status2;  // 表A.18
        struct {
            uint8_t charge_high_temp_protect : 1; // BIT0: 充电高温保护(电芯)
            uint8_t discharge_high_temp_protect :1;// BIT1: 放电高温保护(电芯)
            uint8_t charge_low_temp_protect : 1;  // BIT2: 充电低温保护(电芯)
            uint8_t discharge_low_temp_protect :1;// BIT3: 放电低温保护(电芯)
            uint8_t mos_high_temp_protect : 1;    // BIT4: MOS高温保护
            uint8_t env_high_temp_protect : 1;    // BIT5: 环境高温保护
            uint8_t env_low_temp_protect : 1;     // BIT6: 环境低温保护
            uint8_t fully_charged : 1;            // BIT7: 充满状态
        } protection_status2_bits;
    };

    union {
        uint8_t indication_status;   // 表A.19
        struct {
            uint8_t current_limit : 1;    // BIT0: 限流指示
            uint8_t CFET_Status : 1;      // BIT1: CFET指示
            uint8_t DFET_Status : 1;      // BIT2: DFET指示
            uint8_t pack_power_supply : 1;// BIT3: Pack供电指示
            uint8_t reverse_charge : 1;   // BIT4: 充电器反接指示
            uint8_t ac_input : 1;         // BIT5: AC输入指示
            uint8_t reserved2 : 1;        // BIT6: 预留
            uint8_t heating_film : 1;     // BIT7: 加热膜指示
        } indication_status_bits;
    };

    union {
        uint8_t control_status;     // 表A.20
        struct {
            uint8_t buzzer_enable : 1;    // BIT0: 蜂鸣器使能
            uint8_t reserved3 : 3;        // BIT1-4: 预留
            uint8_t charge_current_limit :1;// BIT5: 充电限流功能
            uint8_t led_alarm_disable : 1;// BIT6: LED告警屏蔽
            uint8_t reserved4 : 2;        // BIT7: 预留
        } control_status_bits;
    };

    union {
        uint8_t fault_status;       // 表A.21
        struct {
            uint8_t charge_mos_fault : 1; // BIT0: 充电MOS故障
            uint8_t discharge_mos_fault :1;// BIT1: 放电MOS故障
            uint8_t NTC_Fault : 1;        // BIT2: 温度传感器故障
            uint8_t reserved5 : 1;        // BIT3: 预留
            uint8_t cell_fault : 1;       // BIT4: 电芯故障
            uint8_t sampling_fault : 1;    // BIT5: 采样故障
            uint8_t reserved6 : 2;        // BIT6-7: 预留
        } fault_status_bits;
    };
     uint8_t Cell_Balance1_8;
		 uint8_t Cell_Balance9_16;
    union {
        uint8_t alarm_status1;     // 表A.22
        struct {
            uint8_t single_cell_overvoltage_alarm :1;  // BIT0: 单体过压告警
            uint8_t single_cell_undervoltage_alarm :1;// BIT1: 单体低压告警
            uint8_t total_voltage_overvoltage_alarm :1;// BIT2: 总压过压告警
            uint8_t total_voltage_undervoltage_alarm :1;// BIT3: 总压低压告警
            uint8_t charge_overcurrent_alarm :1;      // BIT4: 充电过流告警
            uint8_t discharge_overcurrent_alarm :1;   // BIT5: 放电过流告警
					  uint8_t Short_Current_Alarm:1;              //Bit6:短路保护告警
            uint8_t reserved7 :1;                    // BIT7: 预留
        } alarm_status1_bits;
    };

    union {
        uint8_t alarm_status2;     // 表A.23
        struct {
            uint8_t charge_high_temp_alarm :1;  // BIT0: 充电高温告警(电芯)
            uint8_t discharge_high_temp_alarm :1;// BIT1: 放电高温告警(电芯)
            uint8_t charge_low_temp_alarm :1;   // BIT2: 充电低温告警(电芯)
            uint8_t discharge_low_temp_alarm :1;// BIT3: 放电低温告警(电芯)
					  uint8_t mos_high_temp_alarm :1;     // BIT6: MOS高温告警
            uint8_t env_high_temp_alarm :1;     // BIT4: 环境高温告警
            uint8_t env_low_temp_alarm :1;      // BIT5: 环境低温告警
            uint8_t low_soc_alarm :1;           // BIT7: 低电量告警
        } alarm_status2_bits;
    };
} PackAlarmData;


extern BatteryData         BatData;
extern PackAlarmData       AlarmData;
//extern Battery_Flag        Bat_Flag;
extern Battery_Status_Str  Battery_Sta_G;
extern uint8_t             RX_Ser_Byte[128];

#define  Set_2byte_Num    24
#define  Set_1byte_Num    36



#define  Write_Page_Num 14

#define  Write_Done_Sre1   0x56282690
#define  Write_Done_Sre2   0x74643468

#define DEV_ADDR  0x10  // BQ769x2 address is 0x10 including R/W bit or 0x8 as 7-bit address
#define CRC_Mode 0  // 0 for disabled, 1 for enabled
#define MAX_BUFFER_SIZE 10
#define R 0 // Read; Used in DirectCommands and Subcommands functions
#define W 1 // Write; Used in DirectCommands and Subcommands functions
#define W2 2 // Write data with two bytes; Used in Subcommands function
/* USER CODE END PD */



#define    CFET_Contr_GPIO   GPIOB
#define    CFET_Contr_PIN    GPIO_Pin_4

#define    DFET_Contr_GPIO   GPIOB
#define    DFET_Contr_PIN    GPIO_Pin_5

#define    AFE_Re_Shutdown_GPIO   GPIOB
#define    AFE_Re_Shutdown_PIN    GPIO_Pin_3

#define  BQ76952_Offset1    0x9180





//Data	Memory	registers	Name in TRM
#define Cell1Gain 0x9180      //Calibration:Voltage:Cell 1 Gain			
#define Cell2Gain 0x9182      //Calibration:Voltage:Cell 2 Gain			
#define Cell3Gain 0x9184      //Calibration:Voltage:Cell 3 Gain			
#define Cell4Gain 0x9186      //Calibration:Voltage:Cell 4 Gain			
#define Cell5Gain 0x9188      //Calibration:Voltage:Cell 5 Gain			
#define Cell6Gain 0x918A      //Calibration:Voltage:Cell 6 Gain			
#define Cell7Gain 0x918C      //Calibration:Voltage:Cell 7 Gain			
#define Cell8Gain 0x918E      //Calibration:Voltage:Cell 8 Gain			
#define Cell9Gain 0x9190      //Calibration:Voltage:Cell 9 Gain			
#define Cell10Gain 0x9192      //Calibration:Voltage:Cell 10 Gain			
#define Cell11Gain 0x9194      //Calibration:Voltage:Cell 11 Gain			
#define Cell12Gain 0x9196      //Calibration:Voltage:Cell 12 Gain			
#define Cell13Gain 0x9198      //Calibration:Voltage:Cell 13 Gain			
#define Cell14Gain 0x919A      //Calibration:Voltage:Cell 14 Gain			
#define Cell15Gain 0x919C      //Calibration:Voltage:Cell 15 Gain			
#define Cell16Gain 0x919E      //Calibration:Voltage:Cell 16 Gain			
#define PackGain 0x91A0      //Calibration:Voltage:Pack Gain			
#define TOSGain 0x91A2      //Calibration:Voltage:TOS Gain			
#define LDGain 0x91A4      //Calibration:Voltage:LD Gain			
#define ADCGain 0x91A6      //Calibration:Voltage:ADC Gain			
#define CCGain 0x91A8      //Calibration:Current:CC Gain			
#define CapacityGain 0x91AC      //Calibration:Current:Capacity Gain			
#define VcellOffset 0x91B0      //Calibration:Vcell Offset:Vcell Offset			
#define VdivOffset 0x91B2      //Calibration:V Divider Offset:Vdiv Offset			
#define CoulombCounterOffsetSamples 0x91C6      //Calibration:Current Offset:Coulomb Counter Offset Samples			
#define BoardOffset 0x91C8      //Calibration:Current Offset:Board Offset			
#define InternalTempOffset 0x91CA      //Calibration:Temperature:Internal Temp Offset			
#define CFETOFFTempOffset 0x91CB      //Calibration:Temperature:CFETOFF Temp Offset			
#define DFETOFFTempOffset 0x91CC      //Calibration:Temperature:DFETOFF Temp Offset			
#define ALERTTempOffset 0x91CD      //Calibration:Temperature:ALERT Temp Offset			
#define TS1TempOffset 0x91CE      //Calibration:Temperature:TS1 Temp Offset			
#define TS2TempOffset 0x91CF      //Calibration:Temperature:TS2 Temp Offset			
#define TS3TempOffset 0x91D0      //Calibration:Temperature:TS3 Temp Offset			
#define HDQTempOffset 0x91D1      //Calibration:Temperature:HDQ Temp Offset			
#define DCHGTempOffset 0x91D2      //Calibration:Temperature:DCHG Temp Offset			
#define DDSGTempOffset 0x91D3      //Calibration:Temperature:DDSG Temp Offset		





#define IntGain 0x91E2      //Calibration:Internal Temp Model:Int Gain			
#define Intbaseoffset 0x91E4      //Calibration:Internal Temp Model:Int base offset			
#define IntMaximumAD 0x91E6      //Calibration:Internal Temp Model:Int Maximum AD			
#define IntMaximumTemp 0x91E8      //Calibration:Internal Temp Model:Int Maximum Temp			
#define T18kCoeffa1 0x91EA      //Calibration:18K Temperature Model:Coeff a1			
#define T18kCoeffa2 0x91EC      //Calibration:18K Temperature Model:Coeff a2			
#define T18kCoeffa3 0x91EE      //Calibration:18K Temperature Model:Coeff a3			
#define T18kCoeffa4 0x91F0      //Calibration:18K Temperature Model:Coeff a4			
#define T18kCoeffa5 0x91F2      //Calibration:18K Temperature Model:Coeff a5			
#define T18kCoeffb1 0x91F4      //Calibration:18K Temperature Model:Coeff b1			
#define T18kCoeffb2 0x91F6      //Calibration:18K Temperature Model:Coeff b2			
#define T18kCoeffb3 0x91F8      //Calibration:18K Temperature Model:Coeff b3			
#define T18kCoeffb4 0x91FA      //Calibration:18K Temperature Model:Coeff b4			
#define T18kAdc0 0x91FE      //Calibration:18K Temperature Model:Adc0			
#define T180kCoeffa1 0x9200      //Calibration:180K Temperature Model:Coeff a1			
#define T180kCoeffa2 0x9202      //Calibration:180K Temperature Model:Coeff a2			
#define T180kCoeffa3 0x9204      //Calibration:180K Temperature Model:Coeff a3			
#define T180kCoeffa4 0x9206      //Calibration:180K Temperature Model:Coeff a4			
#define T180kCoeffa5 0x9208      //Calibration:180K Temperature Model:Coeff a5			
#define T180kCoeffb1 0x920A      //Calibration:180K Temperature Model:Coeff b1			
#define T180kCoeffb2 0x920C      //Calibration:180K Temperature Model:Coeff b2			
#define T180kCoeffb3 0x920E      //Calibration:180K Temperature Model:Coeff b3			
#define T180kCoeffb4 0x9210      //Calibration:180K Temperature Model:Coeff b4			
#define T180kAdc0 0x9214      //Calibration:180K Temperature Model:Adc0			
#define CustomCoeffa1 0x9216      //Calibration:Custom Temperature Model:Coeff a1			
#define CustomCoeffa2 0x9218      //Calibration:Custom Temperature Model:Coeff a2			
#define CustomCoeffa3 0x921A      //Calibration:Custom Temperature Model:Coeff a3			
#define CustomCoeffa4 0x921C      //Calibration:Custom Temperature Model:Coeff a4			
#define CustomCoeffa5 0x921E      //Calibration:Custom Temperature Model:Coeff a5			
#define CustomCoeffb1 0x9220      //Calibration:Custom Temperature Model:Coeff b1			
#define CustomCoeffb2 0x9222      //Calibration:Custom Temperature Model:Coeff b2			
#define CustomCoeffb3 0x9224      //Calibration:Custom Temperature Model:Coeff b3			
#define CustomCoeffb4 0x9226      //Calibration:Custom Temperature Model:Coeff b4			
#define CustomRc0 0x9228      //Calibration:Custom Temperature Model:Rc0			
#define CustomAdc0 0x922A      //Calibration:Custom Temperature Model:Adc0			
#define CoulombCounterDeadband 0x922D      //Calibration:Current Deadband:Coulomb Counter Deadband			
#define CUVThresholdOverride 0x91D4      //Calibration:CUV:CUV Threshold Override			
#define COVThresholdOverride 0x91D6      //Calibration:COV:COV Threshold Override			
#define MinBlowFuseVoltage 0x9231      //Settings:Fuse:Min Blow Fuse Voltage			
#define FuseBlowTimeout 0x9233      //Settings:Fuse:Fuse Blow Timeout			
#define PowerConfig 0x9234      //Settings:Configuration:Power Config			
#define REG12Config 0x9236      //Settings:Configuration:REG12 Config			
#define REG0Config 0x9237      //Settings:Configuration:REG0 Config			
#define HWDRegulatorOptions 0x9238      //Settings:Configuration:HWD Regulator Options			
#define CommType 0x9239      //Settings:Configuration:Comm Type			
#define I2CAddress 0x923A      //Settings:Configuration:I2C Address			
#define SPIConfiguration 0x923C      //Settings:Configuration:SPI Configuration			
#define CommIdleTime 0x923D      //Settings:Configuration:Comm Idle Time			
#define CFETOFFPinConfig 0x92FA      //Settings:Configuration:CFETOFF Pin Config			
#define DFETOFFPinConfig 0x92FB      //Settings:Configuration:DFETOFF Pin Config			
#define ALERTPinConfig 0x92FC      //Settings:Configuration:ALERT Pin Config			
#define TS1Config 0x92FD      //Settings:Configuration:TS1 Config			
#define TS2Config 0x92FE      //Settings:Configuration:TS2 Config			
#define TS3Config 0x92FF      //Settings:Configuration:TS3 Config			
#define HDQPinConfig 0x9300      //Settings:Configuration:HDQ Pin Config			
#define DCHGPinConfig 0x9301      //Settings:Configuration:DCHG Pin Config			
#define DDSGPinConfig 0x9302      //Settings:Configuration:DDSG Pin Config			
#define DAConfiguration 0x9303      //Settings:Configuration:DA Configuration			
#define VCellMode 0x9304      //Settings:Configuration:Vcell Mode			
#define CC3Samples 0x9307      //Settings:Configuration:CC3 Samples			
#define ProtectionConfiguration 0x925F      //Settings:Protection:Protection Configuration			

#define  EnabledProtectionsA 0x9261      //Settings:Protection:Enabled Protections A			
#define  EnabledProtectionsA_Set    EnabledProtectionsA_SCD|EnabledProtectionsA_OCD1|EnabledProtectionsA_OCC|\
                                    EnabledProtectionsA_COV|EnabledProtectionsA_CUV
																		
#define  EnabledProtectionsA_SCD    0x80
#define  EnabledProtectionsA_OCD2   0x40
#define  EnabledProtectionsA_OCD1   0x20
#define  EnabledProtectionsA_OCC    0x10
#define  EnabledProtectionsA_COV    0x08
#define  EnabledProtectionsA_CUV    0x04


#define EnabledProtectionsB 0x9262      //Settings:Protection:Enabled Protections B	
#define EnabledProtectionsB_Set   EnabledProtectionsB_OTF|EnabledProtectionsB_OTINT|EnabledProtectionsB_OTD|\
                                  EnabledProtectionsB_OTC|EnabledProtectionsB_UTINT|EnabledProtectionsB_UTD|EnabledProtectionsB_UTC
#define EnabledProtectionsB_OTF    0x80
#define EnabledProtectionsB_OTINT  0x40
#define EnabledProtectionsB_OTD    0x20
#define EnabledProtectionsB_OTC    0x10
#define EnabledProtectionsB_UTINT  0x04
#define EnabledProtectionsB_UTD    0x02
#define EnabledProtectionsB_UTC    0x01



#define EnabledProtectionsC 0x9263      //Settings:Protection:Enabled Protections C			
#define CHGFETProtectionsA 0x9265      //Settings:Protection:CHG FET Protections A			
#define CHGFETProtectionsB 0x9266      //Settings:Protection:CHG FET Protections B			
#define CHGFETProtectionsC 0x9267      //Settings:Protection:CHG FET Protections C			
#define DSGFETProtectionsA 0x9269      //Settings:Protection:DSG FET Protections A			
#define DSGFETProtectionsB 0x926A      //Settings:Protection:DSG FET Protections B			
#define DSGFETProtectionsC 0x926B      //Settings:Protection:DSG FET Protections C			
#define BodyDiodeThreshold 0x9273      //Settings:Protection:Body Diode Threshold		



#define   DefaultAlarmMask              0x926D      //Settings:Alarm:Default Alarm Mask
#define   DefaultAlarmMask_Set          DefaultAlarmMask_SSBC|DefaultAlarmMask_SSA|DefaultAlarmMask_PF|DefaultAlarmMask_MSK_SFALERT|\
                                        DefaultAlarmMask_MSK_PFALERT|DefaultAlarmMask_FullScan|DefaultAlarmMask_ADSCAN|DefaultAlarmMask_CB

#define   DefaultAlarmMask_SSBC         0x8000      //当 Safety Status B() 或 Safety Status C() 中设置了某个位时
#define   DefaultAlarmMask_SSA          0x4000      //当 Safety Status A() 中设置了某个位时，
#define   DefaultAlarmMask_PF           0x2000      //当触发启用的永久失效故障时，
#define   DefaultAlarmMask_MSK_SFALERT  0x1000      //当安全警报被触发
#define   DefaultAlarmMask_MSK_PFALERT  0x0800      //当永久失效警报被触发
#define   DefaultAlarmMask_INITSTART    0x0400
#define   DefaultAlarmMask_INITCOMP     0x0200

#define   DefaultAlarmMask_FullScan     0x0080         //完整电压扫描完成
#define   DefaultAlarmMask_XCHG         0x0040
#define   DefaultAlarmMask_XDSG         0x0020
#define   DefaultAlarmMask_SHUTV        0x0010
#define   DefaultAlarmMask_Fuse         0x0008
#define   DefaultAlarmMask_CB           0x0004
#define   DefaultAlarmMask_ADSCAN       0x0002        //电压 ADC 扫描完成。
#define   DefaultAlarmMask_WAKE         0x0001       //当器件从 SLEEP 模式唤醒时会设置该位。


#define SFAlertMaskA 0x926F      //Settings:Alarm:SF Alert Mask A   //选择哪些保护会触发alarm
#define SFAlertMaskB 0x9270      //Settings:Alarm:SF Alert Mask B			
#define SFAlertMaskC 0x9271      //Settings:Alarm:SF Alert Mask C			
#define PFAlertMaskA 0x92C4      //Settings:Alarm:PF Alert Mask A			
#define PFAlertMaskB 0x92C5      //Settings:Alarm:PF Alert Mask B			
#define PFAlertMaskC 0x92C6      //Settings:Alarm:PF Alert Mask C			
#define PFAlertMaskD 0x92C7      //Settings:Alarm:PF Alert Mask D			
#define EnabledPFA 0x92C0      //Settings:Permanent Failure:Enabled PF A			
#define EnabledPFB 0x92C1      //Settings:Permanent Failure:Enabled PF B			
#define EnabledPFC 0x92C2      //Settings:Permanent Failure:Enabled PF C			
#define EnabledPFD 0x92C3      //Settings:Permanent Failure:Enabled PF D			
#define FETOptions 0x9308      //Settings:FET:FET Options			
#define ChgPumpControl 0x9309      //Settings:FET:Chg Pump Control			
#define PrechargeStartVoltage 0x930A      //Settings:FET:Precharge Start Voltage			
#define PrechargeStopVoltage 0x930C      //Settings:FET:Precharge Stop Voltage			
#define PredischargeTimeout 0x930E      //Settings:FET:Predischarge Timeout			
#define PredischargeStopDelta 0x930F      //Settings:FET:Predischarge Stop Delta			
#define DsgCurrentThreshold 0x9310      //Settings:Current Thresholds:Dsg Current Threshold			
#define ChgCurrentThreshold 0x9312      //Settings:Current Thresholds:Chg Current Threshold			
#define CheckTime 0x9314      //Settings:Cell Open-Wire:Check Time			
#define Cell1Interconnect 0x9315      //Settings:Interconnect Resistances:Cell 1 Interconnect			
#define Cell2Interconnect 0x9317      //Settings:Interconnect Resistances:Cell 2 Interconnect			
#define Cell3Interconnect 0x9319      //Settings:Interconnect Resistances:Cell 3 Interconnect			
#define Cell4Interconnect 0x931B      //Settings:Interconnect Resistances:Cell 4 Interconnect			
#define Cell5Interconnect 0x931D      //Settings:Interconnect Resistances:Cell 5 Interconnect			
#define Cell6Interconnect 0x931F      //Settings:Interconnect Resistances:Cell 6 Interconnect			
#define Cell7Interconnect 0x9321      //Settings:Interconnect Resistances:Cell 7 Interconnect			
#define Cell8Interconnect 0x9323      //Settings:Interconnect Resistances:Cell 8 Interconnect			
#define Cell9Interconnect 0x9325      //Settings:Interconnect Resistances:Cell 9 Interconnect			
#define Cell10Interconnect 0x9327      //Settings:Interconnect Resistances:Cell 10 Interconnect			
#define Cell11Interconnect 0x9329      //Settings:Interconnect Resistances:Cell 11 Interconnect			
#define Cell12Interconnect 0x932B      //Settings:Interconnect Resistances:Cell 12 Interconnect			
#define Cell13Interconnect 0x932D      //Settings:Interconnect Resistances:Cell 13 Interconnect			
#define Cell14Interconnect 0x932F      //Settings:Interconnect Resistances:Cell 14 Interconnect			
#define Cell15Interconnect 0x9331      //Settings:Interconnect Resistances:Cell 15 Interconnect			
#define Cell16Interconnect 0x9333      //Settings:Interconnect Resistances:Cell 16 Interconnect			
#define MfgStatusInit 0x9343           //Settings:Manufacturing:Mfg Status Init		
                                       //0x0050  开启制造模式   
#define BalancingConfiguration 0x9335      //Settings:Cell Balancing Config:Balancing Configuration			
#define MinCellTemp 0x9336      //Settings:Cell Balancing Config:Min Cell Temp			
#define MaxCellTemp 0x9337      //Settings:Cell Balancing Config:Max Cell Temp			
#define MaxInternalTemp 0x9338      //Settings:Cell Balancing Config:Max Internal Temp			
#define CellBalanceInterval 0x9339      //Settings:Cell Balancing Config:Cell Balance Interval			
#define CellBalanceMaxCells 0x933A      //Settings:Cell Balancing Config:Cell Balance Max Cells			
#define CellBalanceMinCellVCharge 0x933B      //Settings:Cell Balancing Config:Cell Balance Min Cell V (Charge)	
                                  //0x0C80    //0x3200       // 均衡电压  
#define CellBalanceMinDeltaCharge 0x933D      //Settings:Cell Balancing Config:Cell Balance Min Delta (Charge)		
                                  //0x1E  30mV
#define CellBalanceStopDeltaCharge 0x933E      //Settings:Cell Balancing Config:Cell Balance Stop Delta (Charge)	
                                  //0x0A  10mV
#define CellBalanceMinCellVRelax 0x933F      //Settings:Cell Balancing Config:Cell Balance Min Cell V (Relax)
                                 ////0x0C80    //0x3200       // 均衡电压 
#define CellBalanceMinDeltaRelax 0x9341      //Settings:Cell Balancing Config:Cell Balance Min Delta (Relax)	
																	//0x1E  30mV
#define CellBalanceStopDeltaRelax 0x9342      //Settings:Cell Balancing Config:Cell Balance Stop Delta (Relax)
																//0x0A  10mV
#define ShutdownCellVoltage 0x923F      //Power:Shutdown:Shutdown Cell Voltage			
#define ShutdownStackVoltage 0x9241      //Power:Shutdown:Shutdown Stack Voltage			
#define LowVShutdownDelay 0x9243      //Power:Shutdown:Low V Shutdown Delay			
#define ShutdownTemperature 0x9244      //Power:Shutdown:Shutdown Temperature			
#define ShutdownTemperatureDelay 0x9245      //Power:Shutdown:Shutdown Temperature Delay			
#define FETOffDelay 0x9252      //Power:Shutdown:FET Off Delay			
#define ShutdownCommandDelay 0x9253      //Power:Shutdown:Shutdown Command Delay			
#define AutoShutdownTime 0x9254      //Power:Shutdown:Auto Shutdown Time			
#define RAMFailShutdownTime 0x9255      //Power:Shutdown:RAM Fail Shutdown Time			
#define SleepCurrent 0x9248      //Power:Sleep:Sleep Current			
#define VoltageTime 0x924A      //Power:Sleep:Voltage Time			
#define WakeComparatorCurrent 0x924B      //Power:Sleep:Wake Comparator Current			
#define SleepHysteresisTime 0x924D      //Power:Sleep:Sleep Hysteresis Time			
#define SleepChargerVoltageThreshold 0x924E      //Power:Sleep:Sleep Charger Voltage Threshold			
#define SleepChargerPACKTOSDelta 0x9250      //Power:Sleep:Sleep Charger PACK-TOS Delta			
#define ConfigRAMSignature 0x91E0      //System Data:Integrity:Config RAM Signature			
#define CUVThreshold 0x9275            //Protections:CUV:Threshold
                                       //0x31      49*50.6=2500mV
#define CUVDelay 0x9276                //Protections:CUV:Delay
                                       //0x012C   300*3.3+6.6  =996.6 mS
#define CUVRecoveryHysteresis 0x927B   //Protections:CUV:Recovery Hysteresis
                                       //0X37     55*50.6=2783mV
#define   COVThreshold        0x9278     //Protections:COV:Threshold
                                         // 0X48   72*50.6c=3643V  //过压保护设置
#define   COVDelay            0x9279     //Protections:COV:Delay	
                                         //0x012C  x*3.3ms+6.6ms
#define COVRecoveryHysteresis 0x927C     //Protections:COV:Recovery Hysteresis		
                                         //0X46   70 *50.6=3542V   //

#define COVLLatchLimit 0x927D      //Protections:COVL:Latch Limit			
#define COVLCounterDecDelay 0x927E      //Protections:COVL:Counter Dec Delay


#define COVLRecoveryTime 0x927F      //Protections:COVL:Recovery Time			
#define OCCThreshold 0x9280      //Protections:OCC:Threshold			
#define OCCDelay 0x9281      //Protections:OCC:Delay			
#define OCCRecoveryThreshold 0x9288      //Protections:OCC:Recovery Threshold			
#define OCCPACKTOSDelta 0x92B0      //Protections:OCC:PACK-TOS Delta			
#define OCD1Threshold 0x9282      //Protections:OCD1:Threshold			
#define OCD1Delay 0x9283      //Protections:OCD1:Delay			
#define OCD2Threshold 0x9284      //Protections:OCD2:Threshold			
#define OCD2Delay 0x9285      //Protections:OCD2:Delay			
#define SCDThreshold 0x9286      //Protections:SCD:Threshold			
#define SCDDelay 0x9287      //Protections:SCD:Delay			
#define SCDRecoveryTime 0x9294      //Protections:SCD:Recovery Time			
#define OCD3Threshold 0x928A      //Protections:OCD3:Threshold			
#define OCD3Delay 0x928C      //Protections:OCD3:Delay			
#define OCDRecoveryThreshold 0x928D      //Protections:OCD:Recovery Threshold			
#define OCDLLatchLimit 0x928F      //Protections:OCDL:Latch Limit			
#define OCDLCounterDecDelay 0x9290      //Protections:OCDL:Counter Dec Delay			
#define OCDLRecoveryTime 0x9291      //Protections:OCDL:Recovery Time			
#define OCDLRecoveryThreshold 0x9292      //Protections:OCDL:Recovery Threshold			
#define SCDLLatchLimit 0x9295      //Protections:SCDL:Latch Limit			
#define SCDLCounterDecDelay 0x9296      //Protections:SCDL:Counter Dec Delay			
#define SCDLRecoveryTime 0x9297      //Protections:SCDL:Recovery Time			
#define SCDLRecoveryThreshold 0x9298      //Protections:SCDL:Recovery Threshold			
#define OTCThreshold 0x929A      //Protections:OTC:Threshold			
#define OTCDelay 0x920B      //Protections:OTC:Delay			
#define OTCRecovery 0x929C      //Protections:OTC:Recovery			
#define OTDThreshold 0x929D      //Protections:OTD:Threshold			
#define OTDDelay 0x929E      //Protections:OTD:Delay			
#define OTDRecovery 0x929F      //Protections:OTD:Recovery			
#define OTFThreshold 0x92A0      //Protections:OTF:Threshold			
#define OTFDelay 0x92A1      //Protections:OTF:Delay			
#define OTFRecovery 0x92A2      //Protections:OTF:Recovery			
#define OTINTThreshold 0x92A3      //Protections:OTINT:Threshold			
#define OTINTDelay 0x92A4      //Protections:OTINT:Delay			
#define OTINTRecovery 0x92A5      //Protections:OTINT:Recovery			
#define UTCThreshold 0x92A6      //Protections:UTC:Threshold			
#define UTCDelay 0x92A7      //Protections:UTC:Delay			
#define UTCRecovery 0x92A8      //Protections:UTC:Recovery			
#define UTDThreshold 0x92A9      //Protections:UTD:Threshold			
#define UTDDelay 0x92AA      //Protections:UTD:Delay			
#define UTDRecovery 0x92AB      //Protections:UTD:Recovery			
#define UTINTThreshold 0x92AC      //Protections:UTINT:Threshold			
#define UTINTDelay 0x92AD      //Protections:UTINT:Delay			
#define UTINTRecovery 0x92AE      //Protections:UTINT:Recovery			
#define ProtectionsRecoveryTime 0x92AF      //Protections:Recovery:Time			
#define HWDDelay 0x92B2      //Protections:HWD:Delay			
#define LoadDetectActiveTime 0x92B4      //Protections:Load Detect:Active Time			
#define LoadDetectRetryDelay 0x92B5      //Protections:Load Detect:Retry Delay			
#define LoadDetectTimeout 0x92B6      //Protections:Load Detect:Timeout			
#define PTOChargeThreshold 0x92BA      //Protections:PTO:Charge Threshold			
#define PTODelay 0x92BC      //Protections:PTO:Delay			
#define PTOReset 0x92BE      //Protections:PTO:Reset			
#define CUDEPThreshold 0x92C8      //Permanent Fail:CUDEP:Threshold			
#define CUDEPDelay 0x92CA      //Permanent Fail:CUDEP:Delay			
#define SUVThreshold 0x92CB      //Permanent Fail:SUV:Threshold			
#define SUVDelay 0x92CD      //Permanent Fail:SUV:Delay			
#define SOVThreshold 0x92CE      //Permanent Fail:SOV:Threshold			
#define SOVDelay 0x92D0      //Permanent Fail:SOV:Delay			
#define TOSSThreshold 0x92D1      //Permanent Fail:TOS:Threshold			
#define TOSSDelay 0x92D3      //Permanent Fail:TOS:Delay			
#define SOCCThreshold 0x92D4      //Permanent Fail:SOCC:Threshold			
#define SOCCDelay 0x92D6      //Permanent Fail:SOCC:Delay			
#define SOCDThreshold 0x92D7      //Permanent Fail:SOCD:Threshold			
#define SOCDDelay 0x92D9      //Permanent Fail:SOCD:Delay			
#define SOTThreshold 0x92DA      //Permanent Fail:SOT:Threshold			
#define SOTDelay 0x92DB      //Permanent Fail:SOT:Delay			
#define SOTFThreshold 0x92DC      //Permanent Fail:SOTF:Threshold			
#define SOTFDelay 0x92DD      //Permanent Fail:SOTF:Delay			
#define VIMRCheckVoltage 0x92DE      //Permanent Fail:VIMR:Check Voltage			
#define VIMRMaxRelaxCurrent 0x92E0      //Permanent Fail:VIMR:Max Relax Current			
#define VIMRThreshold 0x92E2      //Permanent Fail:VIMR:Threshold			
#define VIMRDelay 0x92E4      //Permanent Fail:VIMR:Delay			
#define VIMRRelaxMinDuration 0x92E5      //Permanent Fail:VIMR:Relax Min Duration			
#define VIMACheckVoltage 0x92E7      //Permanent Fail:VIMA:Check Voltage			
#define VIMAMinActiveCurrent 0x92E9      //Permanent Fail:VIMA:Min Active Current			
#define VIMAThreshold 0x92EB      //Permanent Fail:VIMA:Threshold			
#define VIMADelay 0x92ED      //Permanent Fail:VIMA:Delay			
#define CFETFOFFThreshold 0x92EE      //Permanent Fail:CFETF:OFF Threshold			
#define CFETFOFFDelay 0x92F0      //Permanent Fail:CFETF:OFF Delay			
#define DFETFOFFThreshold 0x92F1      //Permanent Fail:DFETF:OFF Threshold			
#define DFETFOFFDelay 0x92F3      //Permanent Fail:DFETF:OFF Delay			
#define VSSFFailThreshold 0x92F4      //Permanent Fail:VSSF:Fail Threshold			
#define VSSFDelay 0x92F6      //Permanent Fail:VSSF:Delay			
#define PF2LVLDelay 0x92F7      //Permanent Fail:2LVL:Delay			
#define LFOFDelay 0x92F8      //Permanent Fail:LFOF:Delay			
#define HWMXDelay 0x92F9      //Permanent Fail:HWMX:Delay			
#define SecuritySettings 0x9256      //Security:Settings:Security Settings			
#define UnsealKeyStep1 0x9257      //Security:Keys:Unseal Key Step 1			
#define UnsealKeyStep2 0x9259      //Security:Keys:Unseal Key Step 2			
#define FullAccessKeyStep1 0x925B      //Security:Keys:Full Access Key Step 1			
#define FullAccessKeyStep2 0x925D      //Security:Keys:Full Access Key Step 2			

//Direct Commands 
#define ControlStatus 0x00
#define SafetyAlertA 0x02
#define SafetyStatusA 0x03
#define SafetyAlertB 0x04
#define SafetyStatusB 0x05
#define SafetyAlertC 0x06
#define SafetyStatusC 0x07
#define PFAlertA 0x0A
#define PFStatusA 0x0B
#define PFAlertB 0x0C
#define PFStatusB 0x0D
#define PFAlertC 0x0E
#define PFStatusC 0x0F
#define PFAlertD 0x10
#define PFStatusD 0x11
#define BatteryStatus 0x12
#define Cell1Voltage 0x14
#define Cell2Voltage 0x16
#define Cell3Voltage 0x18
#define Cell4Voltage 0x1A
#define Cell5Voltage 0x1C
#define Cell6Voltage 0x1E
#define Cell7Voltage 0x20
#define Cell8Voltage 0x22
#define Cell9Voltage 0x24
#define Cell10Voltage 0x26
#define Cell11Voltage 0x28
#define Cell12Voltage 0x2A
#define Cell13Voltage 0x2C
#define Cell14Voltage 0x2E
#define Cell15Voltage 0x30
#define Cell16Voltage 0x32
#define StackVoltage 0x34
#define PACKPinVoltage 0x36
#define LDPinVoltage 0x38
#define CC2Current 0x3A
#define AlarmStatus 0x62
#define AlarmRawStatus 0x64
#define AlarmEnable 0x66
#define IntTemperature 0x68
#define CFETOFFTemperature 0x6A
#define DFETOFFTemperature 0x6C
#define ALERTTemperature 0x6E
#define TS1Temperature 0x70
#define TS2Temperature 0x72
#define TS3Temperature 0x74
#define HDQTemperature 0x76
#define DCHGTemperature 0x78
#define DDSGTemperature 0x7A
#define FETStatus 0x7F

//Subcommands 
#define DEVICE_NUMBER 0x0001
#define FW_VERSION 0x0002
#define HW_VERSION 0x0003
#define IROM_SIG 0x0004
#define STATIC_CFG_SIG 0x0005
#define PREV_MACWRITE 0x0007
#define DROM_SIG 0x0009
#define SECURITY_KEYS 0x0035
#define SAVED_PF_STATUS 0x0053
#define MANUFACTURINGSTATUS 0x0057
#define MANU_DATA 0x0070
#define DASTATUS1 0x0071
#define DASTATUS2 0x0072
#define DASTATUS3 0x0073
#define DASTATUS4 0x0074
#define DASTATUS5 0x0075
#define DASTATUS6 0x0076
#define DASTATUS7 0x0077
#define CUV_SNAPSHOT 0x0080
#define COV_SNAPSHOT 0X0081
#define CB_ACTIVE_CELLS 0x0083
#define CB_SET_LVL 0x0084
#define CBSTATUS1 0x0085
#define CBSTATUS2 0x0086
#define CBSTATUS3 0x0087
#define FET_CONTROL 0x0097
#define REG12_CONTROL 0x0098
#define OTP_WR_CHECK 0x00A0
#define OTP_WRITE 0x00A1
#define READ_CAL1 0xF081
#define CAL_CUV 0xF090
#define CAL_COV 0xF091

// Command Only Subcommands 
#define EXIT_DEEPSLEEP 0x000E
#define DEEPSLEEP 0x000F
#define SHUTDOWN 0x0010
#define BQ769x2_RESET 0x0012 //"RESET" in documentation
#define PDSGTEST 0x001C
#define FUSE_TOGGLE 0x001D
#define PCHGTEST 0x001E
#define CHGTEST 0x001F
#define DSGTEST 0x0020
#define FET_ENABLE 0x0022
#define PF_ENABLE 0x0024
#define PF_RESET 0x0029
#define SEAL 0x0030
#define RESET_PASSQ 0x0082
#define PTO_RECOVER 0x008A
#define SET_CFGUPDATE 0x0090
#define EXIT_CFGUPDATE 0x0092
#define DSG_PDSG_OFF 0x0093
#define CHG_PCHG_OFF 0x0094
#define ALL_FETS_OFF 0x0095
#define ALL_FETS_ON 0x0096
#define SLEEP_ENABLE 0x0099
#define SLEEP_DISABLE 0x009A
#define OCDL_RECOVER 0x009B
#define SCDL_RECOVER 0x009C
#define LOAD_DETECT_RESTART 0x009D
#define LOAD_DETECT_ON 0x009E
#define LOAD_DETECT_OFF 0x009F
#define CFETOFF_LO 0x2800
#define DFETOFF_LO 0x2801
#define ALERT_LO 0x2802
#define HDQ_LO 0x2806
#define DCHG_LO 0x2807
#define DDSG_LO 0x2808
#define CFETOFF_HI 0x2810
#define DFETOFF_HI 0x2811
#define ALERT_HI 0x2812
#define HDQ_HI 0x2816
#define DCHG_HI 0x2817
#define DDSG_HI 0x2818
#define PF_FORCE_A 0x2857
#define PF_FORCE_B 0x29A3
#define SWAP_COMM_MODE 0x29BC
#define SWAP_TO_I2C 0x29E7
#define SWAP_TO_SPI 0x7C35
#define SWAP_TO_HDQ 0x7C40


void  Bat_Bit_Flag_Set(void);
Init_Error_Enum Set_BQ76952_Data(uint16_t* Address,uint16_t Length,uint8_t bytes_Num,uint8_t Page_Number);			
uint8_t CRC8(uint8_t *ptr, uint8_t len);
Init_Error_Enum BQ769x2_Init(IC_Setting_Mode  Flash_Empty);
unsigned char Checksum(unsigned char *ptr, unsigned char len);
uint8_t I2C_WriteReg(uint8_t reg_addr, uint8_t *reg_data,uint8_t size);
uint8_t I2C_ReadData(uint8_t reg_addr, uint8_t *reg_data, uint8_t size);
uint8_t BQ769x2_SetRegister(uint16_t reg_addr, uint8_t *reg_data, uint8_t datalen);
uint8_t CommandSubcommands(uint16_t command);
void Subcommands(uint16_t command, uint16_t data, uint8_t type);  
uint8_t DirectCommands(uint8_t command, uint16_t data, uint8_t type,uint8_t Size);
uint16_t BQ769x2_ReadVoltage(uint8_t command,uint8_t Number);
void BQ769x2_ReadPassQ(void);
Init_Error_Enum Write_Page_Data(uint8_t Page_Number,uint8_t* Regis_Data);
float  BQ769x2_ReadTemperature(uint8_t command);
void   BQ769x2_ReadAllVoltages(void);
void   BQ769x2_ReadPFStatus(void);
Init_Error_Enum Confirm_Exit_CFGU_Mode(void);
void   Read_BQ76952_Abnormal_Status(void);
void   BQ769x2_ReadSafetyStatus(void);
void   BQ769x2_ReadAlarmStatus(void);
void   BQ769x2_ReadALLTemperature(void);
void   BQ769x2_ReadCurrent(void); 
void   BQ769x2_ReleaseShutdownPin(void);
void   BQ769x2_ShutdownPin(void); 
void   BQ769x2_ReadFETStatus(void);
void   BQ769x2_RESET_BOTHOFF (void);
void   BQ769x2_BOTHOFF (void);
void   BQ769x2_ReadCurrent(void);
void   EVE_dispatch(void);

#endif /*_BQ769x2Header_h */




