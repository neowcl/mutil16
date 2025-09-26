#include "Bq7695202_drive.h"
#include "IIC_hard_Drive.h"
#include "data_exchange.h"
#include "systick.h"
#include "string.h"
#include <stdio.h>
#include "GPIO_Par_Inter.h"
#include <stdbool.h>
#include "flash.h"
#include "Schedule.h"
#include "math.h "

BatteryData  BatData;

static uint16_t  Address_Set_2bytes[Set_2byte_Num]={COVDelay,0x012C,MfgStatusInit,0x0050,CUVDelay,0x012C,CellBalanceMinCellVCharge,0x0C80,VCellMode,0xFFFF\
,DefaultAlarmMask,DefaultAlarmMask_Set,CCGain,0x6C9B,CCGain+2,0x4172,CapacityGain,0xE997,CapacityGain+2,0x4A89};   

static uint16_t  Address_Set_1byte[Set_1byte_Num]={COVThreshold,0x48,CUVThreshold,0x31,CUVRecoveryHysteresis,0x37,\
CellBalanceMinDeltaCharge,0x1E,CellBalanceStopDeltaCharge,0x0A,CellBalanceMinDeltaRelax,0x1E,CellBalanceStopDeltaRelax,0x0A,\
CellBalanceMinCellVRelax,0x80,CellBalanceMinCellVRelax+1,0x0C,ALERTPinConfig,0x2A,EnabledProtectionsA,EnabledProtectionsA_Set,\
EnabledProtectionsB,EnabledProtectionsB_Set,TS1Config,0x07,TS3Config,0x07,HDQPinConfig,0x07,DDSGPinConfig,0x07,DCHGPinConfig,0x07	};

static  uint8_t Tempt_Number_Index[6]={0,4,6,7,8,9};

PackAlarmData  AlarmData;

Battery_Enum        Batcheck;
Battery_Status_Str  Battery_Sta_G;

uint8_t RX_Ser_Byte [128];
uint16_t Current=0;


uint16_t AlarmBits = 0x00;

uint8_t value_PFStatusA;   // Permanent Fail Status Register A
uint8_t value_PFStatusB;   // Permanent Fail Status Register B
uint8_t value_PFStatusC;   // Permanent Fail Status Register C
uint8_t FET_Status;  // FET Status register contents  - Shows states of FETs
uint16_t CB_ActiveCells;  // Cell Balancing Active Cells



uint8_t LD_ON = 0;	// Load Detect status bit
uint8_t DSG = 0;   // discharge FET state
uint8_t CHG = 0;   // charge FET state
uint8_t PCHG = 0;  // pre-charge FET state
uint8_t PDSG = 0;  // pre-discharge FET state

uint32_t AccumulatedCharge_Int; // in BQ769x2_READPASSQ func
uint32_t AccumulatedCharge_Frac;// in BQ769x2_READPASSQ func
uint32_t AccumulatedCharge_Time;// in BQ769x2_READPASSQ func





/*计算CRC校验码*/
uint8_t CRC8(uint8_t *ptr, uint8_t len)
//Calculates CRC8 for passed bytes. Used in i2c read and write functions 
{
	uint8_t i;
	uint8_t crc=0;
	while(len--!=0) 
	{
		for(i=0x80; i!=0; i/=2)
		{
			if((crc & 0x80) != 0)
			{
				crc *= 2;
				crc ^= 0x107;
			}
			else
				crc *= 2;

			if((*ptr & i)!=0)
				crc ^= 0x107;
		}
		ptr++;
	}
	return(crc);
}

/*计算Ram区，进行chceckSum校验*/
unsigned char Checksum(unsigned char *ptr, unsigned char len)
// Calculates the checksum when writing to a RAM register. The checksum is the inverse of the sum of the bytes.	
{
	unsigned char i;
	unsigned char checksum = 0;

	for(i=0; i<len; i++)
		checksum += ptr[i];

	checksum = 0xff & ~checksum;

	return(checksum);
}









uint8_t I2C_WriteReg(uint8_t reg_addr, uint8_t *reg_data,uint8_t size)
{ 
	  uint16_t i =0;
	  uint8_t  I2C_Tx_Tempt[100];
	  uint8_t Data_check[3]={DEV_ADDR,reg_addr,reg_data[0]};
		I2C_Tx_Tempt[0]=reg_addr;
		I2C_Tx_Tempt[1]=*reg_data;
		I2C_Tx_Tempt[2]=CRC8(Data_check,3);
    // 2. 将数据拷贝到缓冲区后续位置
    for ( i = 1; i < size; i++) 
	 {
			I2C_Tx_Tempt[i*2+1]=*(reg_data+i);
      I2C_Tx_Tempt[i*2+2]=CRC8((reg_data+i),1);
    }
	  if(I2C_Write_DMA(I2C_Tx_Tempt,size*2+1)!=1)
		{
			return 0;
		}
		*reg_data=Checksum(reg_data, size);   //第一个数组
		//*reg_data=Checksum(reg_data+1, size*2); 
		return 1;
}


/**
  * @brief  I2C主设备接收数据
  * @param  dev_addr: 从设备地址
  * @param  reg_addr:要读取的寄存器地址
  * @param  reg_data: 需要存放的位置
	* @param  size: 要读取的数据大小
  * @retval 校验码是否正确？
  */
uint8_t I2C_ReadData(uint8_t reg_addr, uint8_t *reg_data, uint8_t size)
{
	uint8_t I2C_Rx_Tempt[128];
	uint8_t i=0;
	uint8_t Data_check[4]={DEV_ADDR,reg_addr,DEV_ADDR|0x01,0x00};
	memset(I2C_Rx_Tempt,0,sizeof(I2C_Rx_Tempt));
	if(!I2C_ReadData_DMA(reg_addr,I2C_Rx_Tempt,size*2)){
	return 0;}
	Data_check[3]=*I2C_Rx_Tempt;
	if(*(I2C_Rx_Tempt+1)!=CRC8(Data_check,4)){
	return 0;}
	*reg_data=I2C_Rx_Tempt[0];
	for(i=1;i<size;i++){
		if(*(I2C_Rx_Tempt+1+i*2)!=CRC8((I2C_Rx_Tempt+2*i),1)){
			return 0;}
		*(reg_data+i)=I2C_Rx_Tempt[i*2];
	}
	return 1;
}





/**
  * @brief  对Ram区进行设定操作
  * @param  dev_addr: 从设备地址
  * @param  reg_addr:要读取的寄存器地址
  * @param  reg_data: 需要存放的位置
	* @param  datalen: 要读取的数据大小
  * @retval 
  */
uint8_t BQ769x2_SetRegister(uint16_t reg_addr, uint8_t *reg_data, uint8_t datalen)
{
	uint8_t   TX_Buffer[2] = {0x00, 0x00};
	uint8_t   TX_RegData[100];
  uint16_t  Time_Out=0;
	uint8_t    i=0;
	//TX_RegData in little endian format,设定地址，例如0x9180
	TX_RegData[0] = reg_addr & 0xff;      //往  0x3E地址写
	TX_RegData[1] = (reg_addr >> 8) & 0xff;   //王0x3F地址写
	for(i=0;i<datalen;i++)
	{
		TX_RegData[i+2] = reg_data[i];      
	}
	if(I2C_WriteReg(0x3E, TX_RegData, 2+datalen)==0)     //只写入一个byte
	{
		return 0;
	}
	Time_Out=0x0FFF;
		while(Time_Out!=0)
	{
		Time_Out--;
	}
	TX_Buffer[0] =TX_RegData[0];
	//TX_Buffer[1] = (2+datalen+2)*2; //combined length of register address and data
	TX_Buffer[1] = 4+datalen;
  if(I2C_WriteReg(0x60, TX_Buffer, 2)==0) // Write the checksum and length
	{
		return 0;
	}
	Time_Out=0x0FFF;
		while(Time_Out!=0)
	{
		Time_Out--;
	}
	return 1;
}


/**
  * @brief 访问直接命令
  * @param  command: 需要发送的指令
 */

uint8_t CommandSubcommands(uint16_t command) //For Command only Subcommands
// See the TRM or the BQ76952 header file for a full list of Command-only subcommands
{	//For DEEPSLEEP/SHUTDOWN subcommand you will need to call this function twice consecutively
  uint8_t TX_Reg[2] = {0x00, 0x00};
	//TX_Reg in little endian format
	TX_Reg[0] = command & 0xff;
	TX_Reg[1] = (command >> 8) & 0xff;
	if(I2C_WriteReg(0x3E,TX_Reg,2)==0)
	{
		delay_1us(100);
		if(I2C_WriteReg(0x3E,TX_Reg,2)==0)   //再次写入，写入错误
		{
			delay_1us(100);
			return 0;   
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
	return 1;
}


/**
  * @brief  进行2bytes的命令
  * @param  command: 从设备地址
  * @param  data:进行
  * @param  type: 进行写入还是读取 
  */

void Subcommands(uint16_t command, uint16_t data, uint8_t type)   
// See the TRM or the BQ76952 header file for a full list of Subcommands
{
	//security keys and Manu_data writes dont work with this function (reading these commands works)
	//max readback size is 32 bytes i.e. DASTATUS, CUV/COV snapshot
	uint8_t TX_Reg[4] = {0x00, 0x00, 0x00, 0x00};
	uint8_t TX_Buffer[2] = {0x00, 0x00};

	//TX_Reg in little endian format
	TX_Reg[0] = command & 0xff;
	TX_Reg[1] = (command >> 8) & 0xff; 

	if (type == R) {//read
		I2C_WriteReg(0x3E,TX_Reg,2);
		delay_1us(2000);
		I2C_ReadData(0x40, RX_Ser_Byte, 32); //RX_Ser_Byte is a global variable
	}
	else if (type == W) {
		//FET_Control, REG12_Control
		TX_Reg[2] = data & 0xff; 
		I2C_WriteReg(0x3E,TX_Reg,3);
		delay_1us(50);
		TX_Buffer[0] = Checksum(TX_Reg, 3);
		TX_Buffer[1] = 0x05; //combined length of registers address and data
		I2C_WriteReg(0x60, TX_Buffer, 2);
		delay_1us(50); 
	}
	else if (type == W2){ //write data with 2 bytes
		//CB_Active_Cells, CB_SET_LVL
		TX_Reg[2] = data & 0xff; 
		TX_Reg[3] = (data >> 8) & 0xff;
		I2C_WriteReg(0x3E,TX_Reg,4);
		delay_1us(1000);
		TX_Buffer[0] = Checksum(TX_Reg, 4); 
		TX_Buffer[1] = 0x06; //combined length of registers address and data
		I2C_WriteReg(0x60, TX_Buffer, 2);
		delay_1us(1000); 
	}
}




uint8_t DirectCommands(uint8_t command, uint16_t data, uint8_t type,uint8_t Size)
// See the TRM or the BQ76952 header file for a full list of Direct Commands
{	//type: R = read, W = write
	uint8_t TX_data[2] = {0x00, 0x00};
	if (type == R) {//Read
		if(!I2C_ReadData(command, RX_Ser_Byte, Size))
		{
			delay_1us(200);
			if(!I2C_ReadData(command, RX_Ser_Byte, Size))
			{
				delay_1us(200);
				return 0;
			}
		}
		return 1;
	}
	if (type == W) {//write
    //Control_status, alarm_status, alarm_enable all 2 bytes long
		
			//little endian format
	  TX_data[0] = (uint8_t)(data & 0x00FF);
	  TX_data[1] = (uint8_t)((data >> 8) & 0x00FF);
//		TX_data[1]=0x00;
//		TX_data[0]=0xFF;
		I2C_WriteReg(command,TX_data,Size);
		//delay_1us(2000);
	}
	return 1;
}
	



Init_Error_Enum BQ769x2_Init(IC_Setting_Mode  Flash_Empty) {
  uint8_t Page_Number=0;     //每个32个寄存器为一页的页面
	uint8_t Regis_Data[40];    //读取的寄存器的值 
	uint8_t Regis_Data_Tempt[40];
	uint8_t kk=0;
	Init_Error_Enum Flag_Case;
	memset(Regis_Data,0,sizeof(Regis_Data));  
	//任务挂起后  //其他位进行标记   //先判断标志位   //然后进行判断处理
	if(Flash_Empty==Flash_Setting)   //如果Flash没有对应的密码标志位，则进行初始设定
	{
		FLASH_Read(Bq76952_Set_SADDR+(Write_Page_Num+2)*0x20,Regis_Data,8);
		if(((*(volatile uint32_t*)(Regis_Data))==Write_Done_Sre1)\
			&&((*(volatile uint32_t*)(Regis_Data+4))==Write_Done_Sre2))
		{
			Flash_Empty=Flash_Setting;       //flash设定
		}
		else
		{
			Flash_Empty=Init_Setting;   //初始设定
		}
	}
	Flash_Empty=Init_Setting;   //初始设定
	switch(Flash_Empty)
	{
		case(Init_Setting):    //读取初始状态，写入芯片，读数据，写到flash，校准
		{
			for(Page_Number=0;Page_Number<=Write_Page_Num;Page_Number++)
			{		
				kk=0x02;
				if((Flag_Case=Set_BQ76952_Data(Address_Set_2bytes,Set_2byte_Num,0x02,Page_Number))!=Task_OK)
				{
					return Flag_Case;
				}
				kk=0x01;
				if((Flag_Case=Set_BQ76952_Data(Address_Set_1byte,Set_1byte_Num,0x01,Page_Number))!=Task_OK)
				{
					return Flag_Case;
				}
			}
			if(FLASH_Erase_Page(Bq76952_Set_Page))   //如果擦除失败
			{
				 for(Page_Number=0;Page_Number<=Write_Page_Num;Page_Number++)
				{
					//读取寄存器信息
					memset(Regis_Data,0,sizeof(Regis_Data));  
					//读取32位数据  //
					if(BQ769x2_SetRegister((0x9180+Page_Number*(0x0020)),0x00,0)==0){
						return Commute_Error;}
					if(I2C_ReadData(0x40,Regis_Data,34)==0){   //读取32位，后两位为长度和checksum
						return Commute_Error;}
					//读取Flash的数据   //
					if(FLASH_Write(Bq76952_Set_SADDR+Page_Number*0x20,(uint32_t*)Regis_Data,32)==1)
					{
						FLASH_Read(Bq76952_Set_SADDR+Page_Number*0x20,Regis_Data_Tempt,32);
						for(kk=0;kk<32;kk++)
						{
							if(Regis_Data_Tempt[kk]!=Regis_Data[kk])
							{
								return Flash_Match_Error;
							}
						}
					}
					else{
						return Flash_Write_Error;}
				}
				*(volatile uint32_t*)(Regis_Data)=Write_Done_Sre1;
        *(volatile uint32_t*)(Regis_Data+4)=Write_Done_Sre2;
				if(FLASH_Write(Bq76952_Set_SADDR+(Page_Number+1)*0x20,(uint32_t*)Regis_Data,8)!=1)  //往里面写密码代表写入完成
				{
					return Flash_Write_Error;
				}
			}
			else
			{
				return Flash_Erase_Error;
			}
			break;
		}
		case(Flash_Setting):    //
		{
			for(Page_Number=0;Page_Number<Write_Page_Num;Page_Number++)
			{
				//读取flash信息
				memset(Regis_Data,0,sizeof(Regis_Data));
				FLASH_Read(Bq76952_Set_SADDR+Page_Number*0x20,Regis_Data,32);
				//读取IC信息///
				//1.确认退出CFGR模式			
				if((Flag_Case=Confirm_Exit_CFGU_Mode())!=Task_OK)
				{
					return Flag_Case;
				}
				//2.确认退出CFGR模式后，读取参数
				memset(Regis_Data_Tempt,0,sizeof(Regis_Data_Tempt));
				if(BQ769x2_SetRegister((0x9180+Page_Number*(0x0020)),0x00,0)==0){
					return Commute_Error;}
				if(I2C_ReadData(0x40,Regis_Data_Tempt,34)==0){   //读取32位，后两位为长度和checksum
					return Commute_Error;}	
				for(kk=0;kk<32;kk++)
				{
					if(Regis_Data_Tempt[kk]!=Regis_Data[kk])
					{
						//写入数据
						if((Flag_Case=Write_Page_Data(Page_Number,Regis_Data))!=Task_OK)
						{
							return Flag_Case;
						}
					}
				}
				//读取数据，并进行比较
				memset(Regis_Data_Tempt,0,sizeof(Regis_Data_Tempt));
				if(BQ769x2_SetRegister((0x9180+Page_Number*(0x0020)),0x00,0)==0){
					return Commute_Error;}
				if(I2C_ReadData(0x40,Regis_Data_Tempt,34)==0){   //读取32位，后两位为长度和checksum
					return Commute_Error;}	
				for(kk=0;kk<32;kk++)
				{
					if(Regis_Data_Tempt[kk]!=Regis_Data[kk])
					{
						return Flash_Write_Error;
					}
				}
			}
			break;
		}
		case(Change_Setting):   //使用上位机设定
		{
			
			
			break;
		}
		case(BQ_Stdio_Ready):
		{
			//停止访问BQ76952信息   //把线程关闭   //需要另外
		//	EVE_Suspend_By_Ptr(&Task_Gauge[RS485_Response_Data_Task]);
		//	EVE_Suspend_By_Ptr(&Task_Gauge[BQ769x2_ReadSafetyStatus_Task]);
			break;
		}
		case(BQ_Stdio_Set_Done):
		{
				//擦除flash信息，准备写入
				if(FLASH_Erase_Page(Bq76952_Set_Page))   //如果擦除失败
			{
				 for(Page_Number=0;Page_Number<Write_Page_Num;Page_Number++)
				{
					//读取寄存器信息
					memset(Regis_Data,0,sizeof(Regis_Data));  
					//读取32位数据  //
					if(BQ769x2_SetRegister((0x9180+Page_Number*(0x0020)),0x00,0)==0){
						return Commute_Error;}
					if(I2C_ReadData(0x40,Regis_Data,34)==0){   //读取32位，后两位为长度和checksum
						return Commute_Error;}
					//读取Flash的数据   //
					if(FLASH_Write(Bq76952_Set_SADDR+Page_Number*0x20,(uint32_t*)Regis_Data,32)==1)
					{
						FLASH_Read(Bq76952_Set_SADDR+Page_Number*0x20,Regis_Data_Tempt,32);
						for(kk=0;kk<32;kk++)
						{
							if(Regis_Data_Tempt[kk]!=Regis_Data[kk])
							{
								return Flash_Match_Error;
							}
						}
					}
					else{
						return Flash_Write_Error;}
				}
				//写入密码地址，进行读取写入
				*(volatile uint32_t*)(Regis_Data)=Write_Done_Sre1;
        *(volatile uint32_t*)(Regis_Data+4)=Write_Done_Sre2;
				if(FLASH_Write(Bq76952_Set_SADDR+(Page_Number+2)*0x20,(uint32_t*)Regis_Data,8)!=1)  //往里面写密码代表写入完成
				{
					return Flash_Write_Error;
				}
			}
		//	EVE_Resume_By_Ptr(&Task_Gauge[RS485_Response_Data_Task]);
		//	EVE_Resume_By_Ptr(&Task_Gauge[BQ769x2_ReadSafetyStatus_Task]);
			break;
		}
		default:
		{
			break;
		}
	}
	//Regis_Data[0]=0x0f;
	//BQ769x2_SetRegister(REG12Config,Regis_Data,1);
	////设定这个系统的串数--------读取VCellMode的寄存器值/////////
	if(BQ769x2_SetRegister(VCellMode,0x00,0)==0){
		return Commute_Error;}
	if(I2C_ReadData(0x40,Regis_Data_Tempt,4)==0){   //读取32位，后两位为长度和checksum
		return Commute_Error;}	
	BatData.Cell_Number=0;
	for(kk=0;kk<=15;kk++)
	{
		if(((*(volatile uint16_t*)(Regis_Data_Tempt)>>kk)&(0x0001))==1)               //待校验
		{
			 BatData.Cell_Number++;
		}
	}
	return  Task_OK;
}

//  ********************************* FET Control Commands  ***************************************


Init_Error_Enum Confirm_Exit_CFGU_Mode(void)
{
	uint8_t Tempt=0;
	Tempt=2;
  do
	{
			//将替换完成的参数写入到IC的flash
		if(CommandSubcommands(EXIT_CFGUPDATE)==0){
			return Commute_Error;}
		delay_1us(200);
		memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
		if(DirectCommands(BatteryStatus, 0x00, R,2)==0){   //读取标志位
			return Commute_Error; }
		Battery_Sta_G.Bat_Sta=RX_Ser_Byte[1]*256 + RX_Ser_Byte[0];
		if(Battery_Sta_G.Bat_Sta_bits.CFGR_Update==1)   //如果未退出 CFGR_Update模式
		{
			delay_1us(100);
			if(CommandSubcommands(EXIT_CFGUPDATE)==0){  //需要退出CFGUPDATE模式
			return Commute_Error;}
			Tempt--;
		}
	}while((Battery_Sta_G.Bat_Sta_bits.CFGR_Update==1)&&(Tempt!=0));
	if(Battery_Sta_G.Bat_Sta_bits.CFGR_Update==1)   //如果还没退出CFGR模式
	{
		return Mode_Error;   //直接退出  //
	}
	return Task_OK;
}	
	
	
Init_Error_Enum Set_BQ76952_Data(uint16_t* Address,uint16_t Length,uint8_t bytes_Num,uint8_t Page_Number)
{
	uint16_t        Index_Num=0;
	Init_Error_Enum Flag1_Case;
	uint8_t         Regis1_Data[40];    //读取的寄存器的值 
	uint8_t         Regis1_Data_Tempt[40];
	uint16_t        Change_Addr=0;
	uint8_t         data_Tempt[2]; 
	uint8_t         i;
	uint8_t         Write_part_Index[20];
	uint8_t         Wri_Index;
	uint8_t         Need_Write;
	////////////////进行搜索，有无需要进行写入的数据
	Wri_Index=0;
	memset(Write_part_Index,0,sizeof(Write_part_Index));
	for(Index_Num=0;Index_Num<(Length/2);Index_Num++)   //代表对应地址的引索
	{
		
		if((Address[Index_Num*2]<(0x9180+(Page_Number+1)*0x0020))&&\
			(Address[Index_Num*2]>=(0x9180+(Page_Number)*0x0020)))   //如果地址在这个范围内
		{
			Write_part_Index[Wri_Index]=Index_Num*2;   //代表在数据中地址的具体位数
			Wri_Index++;   //如果有修改的需要加一
		}
	}
	if(Wri_Index!=0)   //表示有需要修改的参数
	{
		//进行读取参数，确保退出CFGR模式
		if((Flag1_Case=Confirm_Exit_CFGU_Mode())!=1)
		{
			return Flag1_Case;
		}
	 //进行读取并对照数据
		if(Battery_Sta_G.Bat_Sta_bits.CFGR_Update==0)   //只有退出退出CFGUPDATE模式
		{
			memset(Regis1_Data,0,sizeof(Regis1_Data));  
			if(BQ769x2_SetRegister((0x9180+Page_Number*(0x0020)),0x00,0)==0){
				return Commute_Error;}
			if(I2C_ReadData(0x40,Regis1_Data,34)==0){   //读取32位，后两位为长度和checksum
				return Commute_Error;}
			//将参数进行替换赋值
			Need_Write=0;  //先复位
			for(Index_Num=0;Index_Num<Wri_Index;Index_Num++)   //处理三位
			{	
				//处理2位数据
				Change_Addr=Address[Write_part_Index[Index_Num]]-0x9180-0x20*Page_Number;   //需要替换的地址
				if(bytes_Num==1)
				{
					data_Tempt[0]=(uint8_t)((Address[Write_part_Index[Index_Num]+1])&0x00FF);	
					 if(data_Tempt[0]!=Regis1_Data[Change_Addr])
					{
						Regis1_Data[Change_Addr]=data_Tempt[0];
						Need_Write=1; //表示需要写   //表示需要写
					}
				}
				else if(bytes_Num==2)
				{
					data_Tempt[0]=(uint8_t)((Address[Write_part_Index[Index_Num]+1])&0x00FF);   //代表高位
          data_Tempt[1]=(uint8_t)((Address[Write_part_Index[Index_Num]+1]>>8)&0x00FF);  //代表低位
					 if(data_Tempt[0]!=Regis1_Data[Change_Addr]||data_Tempt[1]!=Regis1_Data[Change_Addr+1])
					{
						Regis1_Data[Change_Addr]=data_Tempt[0];     //表示高位
						Regis1_Data[Change_Addr+1]=data_Tempt[1];
						Need_Write=1; //表示需要写   //表示需要写
					}
				}
			}
			if(Need_Write==1)   //  代表需要写
			{
				//进行写操作
				 //写入数据
					if((Flag1_Case=Write_Page_Data(Page_Number,Regis1_Data))!=Task_OK)
					{
						return Flag1_Case;
					}
					///写完成
					/////读取信息进行校验是否写入正常////
					memset(Regis1_Data_Tempt,0,sizeof(Regis1_Data_Tempt));  
					if(BQ769x2_SetRegister((0x9180+Page_Number*(0x0020)),0x00,0)==0){
						 return Commute_Error;}
					if(I2C_ReadData(0x40,Regis1_Data_Tempt,34)==0){   //读取32位，后两位为长度和checksum
						 return Commute_Error;}
					for(i=0;i<32;i++)
					{
						//如果写入信息与读取信息不一致
						if(Regis1_Data_Tempt[i]!=Regis1_Data_Tempt[i])   
						{
							return Write_Error;    
						}
					}
				}
			}
		else   //
		{
			return Mode_Error;   //直接退出。没有退出CFGR的模式
		}	 
	}	
	return  Task_OK;
}



Init_Error_Enum Write_Page_Data(uint8_t Page_Number,uint8_t* Regis_Data)
{
	 if(CommandSubcommands(SET_CFGUPDATE)==0){
	 return Commute_Error;}
	 delay_1us(100);
	 if(BQ769x2_SetRegister(0x9180+Page_Number*0x20, Regis_Data, 32)==0){
		 return Commute_Error; }
   if(Confirm_Exit_CFGU_Mode()!=Task_OK)
	 {
		 return Mode_Error;
	 }
	 return Task_OK;
}






void BQ769x2_BOTHOFF (void) {
	// Disables all FETs using the DFETOFF (BOTHOFF) pin
	// The DFETOFF pin on the BQ76952EVM should be connected to the MCU board to use this function
	GPIO_ResetBits(DFET_Contr_GPIO, DFET_Contr_PIN);  // DFETOFF pin (BOTHOFF) set high  4c
}

void BQ769x2_RESET_BOTHOFF (void) {
	// Resets DFETOFF (BOTHOFF) pin
	// The DFETOFF pin on the BQ76952EVM should be connected to the MCU board to use this function
	GPIO_SetBits(DFET_Contr_GPIO, DFET_Contr_PIN);  // DFETOFF pin (BOTHOFF) set low  5d
}

void BQ769x2_ReadFETStatus(void) { 
	// Read FET Status to see which FETs are enabled
	if(DirectCommands(FETStatus, 0x00, R,1)){
		Battery_Sta_G.FET_Status=RX_Ser_Byte[0];
	}
}

// ********************************* End of FET Control Commands *********************************

// ********************************* BQ769x2 Power Commands   *****************************************

void BQ769x2_ShutdownPin(void) {
	// Puts the device into SHUTDOWN mode using the RST_SHUT pin
	// The RST_SHUT pin on the BQ76952EVM should be connected to the MCU board to use this function	
	GPIO_SetBits(AFE_Re_Shutdown_GPIO, AFE_Re_Shutdown_PIN);  // Sets RST_SHUT pin
}

void BQ769x2_ReleaseShutdownPin(void) {
	// Releases the RST_SHUT pin
	// The RST_SHUT pin on the BQ76952EVM should be connected to the MCU board to use this function	
	GPIO_ResetBits(AFE_Re_Shutdown_GPIO, AFE_Re_Shutdown_PIN);  // Resets RST_SHUT pin
}

// ********************************* End of BQ769x2 Power Commands   *****************************************


// ********************************* BQ769x2 Status and Fault Commands   *****************************************

void Read_BQ76952_Abnormal_Status(void)
{
	BQ769x2_ReadSafetyStatus();
	BQ769x2_ReadPFStatus();
}


void BQ769x2_ReadAlarmStatus(void) { 
	// Read this register to find out why the ALERT pin was asserted
	uint8_t x=0;
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(AlarmStatus,0x00, R,6))
	{
		for(x=0;x<3;x++){
			*((&(Battery_Sta_G.Alarm_Sta))+x)=RX_Ser_Byte[x*2+1]*256+RX_Ser_Byte[x*2];
		}
	}
	else
	{
	}
}

void BQ769x2_ReadSafetyStatus(void) { //good example functions
	uint8_t x=0;
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(SafetyAlertA, 0x00, R,6)){
		for(x=0;x<6;x++){
			*((&(Battery_Sta_G.Safety_Alert_A))+x)=RX_Ser_Byte[x];}}
	else{}
	if ((Battery_Sta_G.Safety_Satus_A + Battery_Sta_G.Safety_Satus_B + Battery_Sta_G.Safety_Satus_C) > 1) {
		Battery_Sta_G.Bata_Flag_bits.Pro_Tri = 1; }
	else {
		Battery_Sta_G.Bata_Flag_bits.Pro_Tri = 0; }
}

void BQ769x2_ReadPFStatus(void) {
	uint8_t x=0;
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(PFAlertA, 0x00, R,10))
	{
		for(x=0;x<8;x++)
		{
			*((&(Battery_Sta_G.PF_Alert_A))+x)=RX_Ser_Byte[x];
		}
		Battery_Sta_G.Bat_Sta=RX_Ser_Byte[9]*256 + RX_Ser_Byte[8];
	}
	else{
	}
}

// ********************************* End of BQ769x2 Status and Fault Commands   *****************************************


// ********************************* BQ769x2 Measurement Commands   *****************************************


//uint16_t BQ769x2_ReadVoltage(uint8_t command,uint8_t Number)
//// This function can be used to read a specific cell voltage or stack / pack / LD voltage
//{
//	//RX_data is global var
//	if(DirectCommands(command, 0x00, R,Number)==1){
//		return 1;}
//	return 0;
//}


void BQ769x2_ReadAllVoltages(void)
// Reads all cell voltages, Stack voltage, PACK pin voltage, and LD pin voltage
{
	uint8_t x=0;
  uint8_t cellvoltageholder = Cell1Voltage; //Cell1Voltage is 0x14
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(cellvoltageholder,0x00,R,32)){
		for ( x = 0; x < 16; x++){
			BatData.cell_voltages[x]=RX_Ser_Byte[x*2+1]*256+RX_Ser_Byte[x*2];}}
	else{
		/////////////
		}
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(StackVoltage,0x00,R,2))
		BatData.Stack_Voltage=(RX_Ser_Byte[1]*256+RX_Ser_Byte[0])*10;
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(PACKPinVoltage,0x00,R,2))
		BatData.Pack_Voltage=(RX_Ser_Byte[1]*256+RX_Ser_Byte[0])*10;
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(LDPinVoltage,0x00,R,2))
		BatData.LD_Voltage=(RX_Ser_Byte[1]*256+RX_Ser_Byte[10])*10;
	//LED_Do();
}

// Reads PACK current
void BQ769x2_ReadCurrent(void)  
{
	int16_t Data_k=0;
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	DirectCommands(CC2Current, 0x00, R,2);
	Data_k=RX_Ser_Byte[1]*256 + RX_Ser_Byte[0]; 
	if((Data_k<30)&&(Data_k>(-30)))
	{
		Data_k=0;
	}
	BatData.pack_current=Data_k;  // current is reported in mA
}



void  BQ769x2_ReadALLTemperature(void) 
{
	uint8_t x=0;
	//LED_Do();
  uint8_t Tempttageholder = IntTemperature; //Temp_Num Cell1Voltage is 0x14
	//Temp_Num_Enum Temp_Num=Inttem_Num;
	memset(RX_Ser_Byte,0,sizeof(RX_Ser_Byte));
	if(DirectCommands(Tempttageholder, 0x00, R,20)==1){
			for ( x = 0; x <10; x++)
		{//Reads all cell temperature
			BatData.temperatures[x]=(0.1 * (float)(RX_Ser_Byte[x*2+1]*256 + RX_Ser_Byte[x*2])) - 273.15;
		}
	}
	else
	{
	}
}

void BQ769x2_ReadPassQ(void){ // Read Accumulated Charge and Time from DASTATUS6 
	Subcommands(DASTATUS6, 0x00, R);
	AccumulatedCharge_Int = ((RX_Ser_Byte[3]<<24) + (RX_Ser_Byte[2]<<16) + (RX_Ser_Byte[1]<<8) + RX_Ser_Byte[0]); //Bytes 0-3
	AccumulatedCharge_Frac = ((RX_Ser_Byte[7]<<24) + (RX_Ser_Byte[6]<<16) + (RX_Ser_Byte[5]<<8) + RX_Ser_Byte[4]); //Bytes 4-7
	AccumulatedCharge_Time = ((RX_Ser_Byte[11]<<24) + (RX_Ser_Byte[10]<<16) + (RX_Ser_Byte[9]<<8) + RX_Ser_Byte[8]); //Bytes 8-11
}


void  Bat_Bit_Flag_Set(void)
{
	uint8_t i=0;
	 //电压单体告警
	for(i=0;i<=15;i++)
	{
		if(BatData.cell_voltages[i]<=Cell_Voltage_Limit_Low){
			AlarmData.cell_alarms[i]=0x01;}
		else if(BatData.cell_voltages[i]>=Cell_Voltage_Limit_High){
			AlarmData.cell_alarms[i]=0x02;}
		else if((BatData.cell_voltages[i]>=Cell_Voltage_Limit_Low)&&\
			BatData.cell_voltages[i]<=Cell_Voltage_Limit_High){
			AlarmData.cell_alarms[i]=0x00;}
		else{
			AlarmData.cell_alarms[i]=0xF0;}
	}
	//2nb  pack总电压告警
	if(BatData.pack_voltage<=Tol_Vol_Alarm_Low){
		AlarmData.pack_voltage_alarm=0x01;}
	else if(BatData.pack_voltage>=Tol_Vol_Alarm_High){
		AlarmData.pack_voltage_alarm=0x02;}
	else if((BatData.pack_voltage>=Tol_Vol_Alarm_Low)&&\
		BatData.pack_voltage<=Tol_Vol_Alarm_High){
		AlarmData.pack_voltage_alarm=0x00;}
	else{
		AlarmData.pack_voltage_alarm=0xF0;}
	//2nb 电流告警
	if(BatData.pack_current>=0)
	{
		if(BatData.pack_current>=Charge_Current_Alarm_High){
			AlarmData.charge_current_alarm=0x02;}
		else{
			AlarmData.charge_current_alarm=0x00;}
	}
	else if(BatData.pack_current<=0)
	{
		if(BatData.pack_current<=Discha_Current_Alarm_High){
			AlarmData.charge_current_alarm=0x02;}
		else{
			AlarmData.charge_current_alarm=0x00;}
	}
	else
	{
		AlarmData.charge_current_alarm=0x00;
		AlarmData.discharge_current_alarm=0x00;
	}
	//温度告警
	for(i=0;i<=5;i++)
	{	
		if(BatData.temperatures[Tempt_Number_Index[i]]<=Tempt_Alarm_Low){
			AlarmData.temp_alarms[i]=0x01;}
		else if(BatData.temperatures[Tempt_Number_Index[i]]>=Tempt_Alarm_High){
			AlarmData.temp_alarms[i]=0x02;}
		else if((BatData.temperatures[Tempt_Number_Index[i]]>=Tempt_Alarm_Low)&&\
			BatData.temperatures[Tempt_Number_Index[i]]<=Tempt_Alarm_High){
			AlarmData.temp_alarms[i]=0x00;}
		else{
			AlarmData.temp_alarms[i]=0xF0;}
	}
	AlarmData.temp_alarms[6]=0x00;
	AlarmData.temp_alarms[7]=0x00;
}	

void Bat_Bit_Abnormal_Set(void)
{
	uint8_t i=0;
	Temp_Num_Enum Temp_Num_Index[6]={TS1tem_Num,TS3tem_Num,DCHGtem_Num,DDSGtem_Num,Inttem_Num,HDQtem_Num};
	
	//2nb    //
	//单体个数
	AlarmData.Cell_Number=BatData.Cell_Number;   
  //温度数量	
	AlarmData.Tempt_Number=6;

	// byte 6
	//过压保护  byte0
	 if(Battery_Sta_G.Safety_Alert_A_bits.COV==1){
  AlarmData.protection_status1_bits.single_cell_overvoltage=1;}
  else{AlarmData.protection_status1_bits.single_cell_overvoltage=0;}
	 //欠压保护 byte1
	if(Battery_Sta_G.Safety_Alert_A_bits.CUV==1){
	 AlarmData.protection_status1_bits.single_cell_undervoltage=1;}
	 else{AlarmData.protection_status1_bits.single_cell_undervoltage=0;}
	 //	总压过压 byte2
	if(BatData.Pack_Voltage>Tol_Vol_Pro_High){
	AlarmData.protection_status1_bits.total_voltage_overvoltage=1;}
	else{AlarmData.protection_status1_bits.total_voltage_overvoltage=0;}
	 //总压低压 byte3
	if(BatData.Pack_Voltage<Tol_Vol_Pro_Low){
	AlarmData.protection_status1_bits.total_voltage_undervoltage=1;}
	else{AlarmData.protection_status1_bits.total_voltage_undervoltage=0;}
	//充电过流 byte4
	if(Battery_Sta_G.Safety_Alert_A_bits.OCC==1){
	AlarmData.protection_status1_bits.charge_overcurrent=1;}
	else{AlarmData.protection_status1_bits.charge_overcurrent=0;}
	//放电过流 byte5
	if(Battery_Sta_G.Safety_Alert_A_bits.OCD1==1){
	AlarmData.protection_status1_bits.discharge_overcurrent=1;}
	else{AlarmData.protection_status1_bits.discharge_overcurrent=0;}
	//短路保护告警 byte6
	if(Battery_Sta_G.Safety_Alert_A_bits.SCD==1){
	AlarmData.protection_status1_bits.short_circuit=1;}
	else{AlarmData.protection_status1_bits.short_circuit=0;}
	//reserve  byte7
	AlarmData.protection_status1_bits.reserved1=0;

	//byte7
	//充电高温
	if(Battery_Sta_G.Safety_Alert_B_bits.OTC==1){
	AlarmData.protection_status2_bits.charge_high_temp_protect=1;}
	else{AlarmData.protection_status2_bits.charge_high_temp_protect=0;}
	//放电高温
	if(Battery_Sta_G.Safety_Alert_B_bits.OTD==1){
	AlarmData.protection_status2_bits.discharge_high_temp_protect=1;}
	else{AlarmData.protection_status2_bits.discharge_high_temp_protect=0;}
	//充电低温
	if(Battery_Sta_G.Safety_Alert_B_bits.UTC==1){
	AlarmData.protection_status2_bits.charge_low_temp_protect=1;}
	else{AlarmData.protection_status2_bits.charge_low_temp_protect=0;}
	//放电低温
	if(Battery_Sta_G.Safety_Alert_B_bits.UTD==1){
	AlarmData.protection_status2_bits.discharge_low_temp_protect=1;}
	else{AlarmData.protection_status2_bits.discharge_low_temp_protect=0;}
	//MOS高温保护
	if(Battery_Sta_G.Safety_Alert_B_bits.OTF==1){
	AlarmData.protection_status2_bits.mos_high_temp_protect=1;}
	else{AlarmData.protection_status2_bits.mos_high_temp_protect=0;};
	
  //环境高温保护
	if(BatData.temperatures[TS1tem_Num]>Env_Tempt_Pro_High){
	AlarmData.protection_status2_bits.env_high_temp_protect=1;}	
	else{AlarmData.protection_status2_bits.env_high_temp_protect=0;}
	//环境低温保护
	if(BatData.temperatures[TS1tem_Num]<Env_Tempt_Pro_Low){
	AlarmData.protection_status2_bits.env_low_temp_protect=1;}	
	else{AlarmData.protection_status2_bits.env_low_temp_protect=0;}
  //满充状态
	if(BatData.Ideal_SOC==100){
	AlarmData.protection_status2_bits.fully_charged=1;}
	else{AlarmData.protection_status2_bits.fully_charged=0;};
	
	
	//byte8
	//0限流状态
	AlarmData.indication_status_bits.current_limit=0;
	//CEFT 状态
	if(Battery_Sta_G.FET_Status_bits.CHG_FET==1){
	AlarmData.indication_status_bits.CFET_Status=1;}
	else{AlarmData.indication_status_bits.CFET_Status=0;}
	//DFET状态
	if(Battery_Sta_G.FET_Status_bits.DSG_FET==1){
	AlarmData.indication_status_bits.DFET_Status=1;}
	else{AlarmData.indication_status_bits.DFET_Status=0;}
	//pack供电指示
	AlarmData.indication_status_bits.pack_power_supply=0;
	//充电反接指示
	AlarmData.indication_status_bits.reverse_charge=0;
	//Acin指示
	AlarmData.indication_status_bits.ac_input=0;
	//reserve
	AlarmData.indication_status_bits.reserved2=0;
	//加热膜
	AlarmData.indication_status_bits.heating_film=0;
	
	
	
  //2nC指示   byte1
	AlarmData.control_status_bits.buzzer_enable=0;
	//充电限流功能
	AlarmData.control_status_bits.charge_current_limit=0;
	//LED报警
	AlarmData.control_status_bits.led_alarm_disable=0;
	//byte2
	//充电MOS故障
	if(Battery_Sta_G.PF_Status_B_Bits.CFET==1){
		AlarmData.fault_status_bits.charge_mos_fault=1;}
	else{AlarmData.fault_status_bits.charge_mos_fault=0;}
	//放电MOS故障
	if(Battery_Sta_G.PF_Status_B_Bits.DFET==1){
		AlarmData.fault_status_bits.discharge_mos_fault=1;}
	else{AlarmData.fault_status_bits.discharge_mos_fault=0;}
	//温度故障
	for(i=0;i<=5;i++)
	{
		if(BatData.temperatures[Temp_Num_Index[i]]<=(-270))
		{
			AlarmData.fault_status_bits.NTC_Fault=1;
			break;
		}
	}
 //电芯故障  //采样故障
	for(i=0;i<=15;i++)
	{
		if((BatData.cell_voltages[i]<=(500))||(BatData.cell_voltages[i]>=(5000)))
		{
			AlarmData.fault_status_bits.cell_fault=1;
			AlarmData.fault_status_bits.sampling_fault=1;
			break;
		}
	}
	
	//电压欠压告警
	for(i=0;i<=15;i++)
	{
		if(AlarmData.cell_alarms[i]==0x01)
		{
			AlarmData.alarm_status1_bits.single_cell_undervoltage_alarm=1;
			break;
		}	
		if(i==15)
		{
			AlarmData.alarm_status1_bits.single_cell_undervoltage_alarm=0;
		}
	}
	//电压过压告警
	for(i=0;i<=15;i++)
	{
		if(AlarmData.cell_alarms[i]==0x02)
		{
			AlarmData.alarm_status1_bits.single_cell_overvoltage_alarm=1;
			break;
		}	
		if(i==15)
		{
			AlarmData.alarm_status1_bits.single_cell_overvoltage_alarm=0;
		}
	}
	//总压过压告警
	//总压过压
	//总压欠压
	if(AlarmData.pack_voltage_alarm==0x01)
	{
		AlarmData.alarm_status1_bits.total_voltage_overvoltage_alarm=0;
		AlarmData.alarm_status1_bits.total_voltage_undervoltage_alarm=1;
	}
	else if(AlarmData.pack_voltage_alarm==0x02)
	{
		AlarmData.alarm_status1_bits.total_voltage_overvoltage_alarm=1;
		AlarmData.alarm_status1_bits.total_voltage_undervoltage_alarm=0;
	}
	else
	{
		AlarmData.alarm_status1_bits.total_voltage_overvoltage_alarm=0;
		AlarmData.alarm_status1_bits.total_voltage_undervoltage_alarm=0;
	}
	//充电过流告警
	if(AlarmData.charge_current_alarm==0x02)
	{
		AlarmData.alarm_status1_bits.charge_overcurrent_alarm=1;
	}
	else if(AlarmData.charge_current_alarm==0x00)
	{
		AlarmData.alarm_status1_bits.charge_overcurrent_alarm=0;
	}
	//放电过流告警
	if(AlarmData.discharge_current_alarm==0x02)
	{
		AlarmData.alarm_status1_bits.discharge_overcurrent_alarm=1;
	}
	else if(AlarmData.discharge_current_alarm==0x00)
	{
		AlarmData.alarm_status1_bits.discharge_overcurrent_alarm=0;
	}

	//byte6 
	//充电过温
	if(Battery_Sta_G.Safety_Alert_B_bits.OTC==1){
	AlarmData.alarm_status2_bits.charge_high_temp_alarm=1;}
	else{AlarmData.alarm_status2_bits.charge_high_temp_alarm=0;}
	//放电高温
	if(Battery_Sta_G.Safety_Alert_B_bits.OTD==1){
	AlarmData.alarm_status2_bits.discharge_high_temp_alarm=1;}
	else{AlarmData.alarm_status2_bits.discharge_high_temp_alarm=0;}
	//充电低温
	if(Battery_Sta_G.Safety_Alert_B_bits.UTC==1){
	AlarmData.alarm_status2_bits.charge_low_temp_alarm=1;}
	else{AlarmData.alarm_status2_bits.charge_low_temp_alarm=0;}
	//放电低温
	if(Battery_Sta_G.Safety_Alert_B_bits.UTD==1){
	AlarmData.alarm_status2_bits.discharge_low_temp_alarm=1;}
	else{AlarmData.alarm_status2_bits.discharge_low_temp_alarm=0;}
	//MOS温度保护
	if(BatData.temperatures[Temp_Num_Index[1]]>Mos_Temp_Alarm_High){
	AlarmData.alarm_status2_bits.mos_high_temp_alarm=1;}	
	else{AlarmData.alarm_status2_bits.mos_high_temp_alarm=0;}
	//环境高温告警
	if(BatData.temperatures[Temp_Num_Index[0]]>Env_Tempt_Alarm_High){
	AlarmData.alarm_status2_bits.env_high_temp_alarm=1;}	
	else{AlarmData.alarm_status2_bits.env_high_temp_alarm=0;}
	//环境低温告警
	if(BatData.temperatures[Temp_Num_Index[0]]<Env_Tempt_Alarm_Low){
	AlarmData.alarm_status2_bits.env_low_temp_alarm=1;}	
	else{AlarmData.alarm_status2_bits.env_low_temp_alarm=0;}
	//低电量告警
	if(BatData.Ideal_SOC<SOC_LOW){
		AlarmData.alarm_status2_bits.low_soc_alarm=1;}
	else{AlarmData.alarm_status2_bits.low_soc_alarm=0;};

}

































/*
void  Bat_Bit_Flag_Set(Battery_Enum  Batcheck)
{
	uint8_t i=0;
	switch(Batcheck)
	{
		case(Vol_Check):
		{
			for(i=0;i<=15;i++)
			{
				if(BatData.cell_voltages[i]<=Bat_Flag.Cell_Voltage_Limit[0]){
					AlarmData.cell_alarms[i]=0x01;}
				else if(BatData.cell_voltages[i]>=Bat_Flag.Cell_Voltage_Limit[1]){
					AlarmData.cell_alarms[i]=0x02;}
				else if((BatData.cell_voltages[i]>=Bat_Flag.Cell_Voltage_Limit[0])&&\
					BatData.cell_voltages[i]<=Bat_Flag.Cell_Voltage_Limit[1]){
				  AlarmData.cell_alarms[i]=0x00;}
				else{
					AlarmData.cell_alarms[i]=0xF0;}
			}
			if(BatData.pack_voltage<=Bat_Flag.Tol_Vol_Alarm[0]){
				AlarmData.cell_alarms[i]=0x01;}
			else if(BatData.pack_voltage>=Bat_Flag.Tol_Vol_Alarm[1]){
				AlarmData.cell_alarms[i]=0x02;}
			else if((BatData.pack_voltage>=Bat_Flag.Tol_Vol_Alarm[0])&&\
				BatData.pack_voltage<=Bat_Flag.Tol_Vol_Alarm[1]){
				AlarmData.cell_alarms[i]=0x00;}
			else{
				AlarmData.cell_alarms[i]=0xF0;}
			break;
		}
		case(Cur_Check):
		{
			if(BatData.pack_current>=0)
			{
				if(BatData.pack_current>=Bat_Flag.Charge_Current_Limit){
					AlarmData.charge_current_alarm=0x02;}
				else{
					AlarmData.charge_current_alarm=0x00;}
			}
			else if(BatData.pack_current<=0)
			{
				if(BatData.pack_current<=Bat_Flag.Discha_Current_Limit){
					AlarmData.charge_current_alarm=0x02;}
				else{
					AlarmData.charge_current_alarm=0x00;}
			}
			else
			{
				AlarmData.charge_current_alarm=0x00;
				AlarmData.discharge_current_alarm=0x00;
			}
			break;
		}
		case(Tempt_Check):
		{
			for(i=0;i<=7;i++)
			{
				if(BatData.temperatures[i]<=Bat_Flag.Tempt_Alarm[0]){
					AlarmData.cell_alarms[i]=0x01;}
				else if(BatData.temperatures[i]>=Bat_Flag.Tempt_Alarm[1]){
					AlarmData.cell_alarms[i]=0x02;}
				else if((BatData.temperatures[i]>=Bat_Flag.Tempt_Alarm[0])&&\
					BatData.cell_voltages[i]<=Bat_Flag.Tempt_Alarm[1]){
				  AlarmData.cell_alarms[i]=0x00;}
				else{
					AlarmData.cell_alarms[i]=0xF0;}
			}
			break;
		}
		case(Bit_Check):
		{
			break;
		}
		default:
		{
		}
	}	
}

*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






















