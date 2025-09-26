#include "IIC_Soft_Drive.h"
#include   "GPIO_Init.h"
#include   "systick.h"


uint8_t  delay_Time_us=10;    //用来定义延时多久


//输出模式将会使用
uint8_t   CRC8Table[]=
{							//120424-1			CRC Table     //CRC8的数组
	0x00,0x07,0x0E,0x09,0x1C,0x1B,0x12,0x15,0x38,0x3F,0x36,0x31,0x24,0x23,0x2A,0x2D,
	0x70,0x77,0x7E,0x79,0x6C,0x6B,0x62,0x65,0x48,0x4F,0x46,0x41,0x54,0x53,0x5A,0x5D,
	0xE0,0xE7,0xEE,0xE9,0xFC,0xFB,0xF2,0xF5,0xD8,0xDF,0xD6,0xD1,0xC4,0xC3,0xCA,0xCD,
	0x90,0x97,0x9E,0x99,0x8C,0x8B,0x82,0x85,0xA8,0xAF,0xA6,0xA1,0xB4,0xB3,0xBA,0xBD,
	0xC7,0xC0,0xC9,0xCE,0xDB,0xDC,0xD5,0xD2,0xFF,0xF8,0xF1,0xF6,0xE3,0xE4,0xED,0xEA,
	0xB7,0xB0,0xB9,0xBE,0xAB,0xAC,0xA5,0xA2,0x8F,0x88,0x81,0x86,0x93,0x94,0x9D,0x9A,
	0x27,0x20,0x29,0x2E,0x3B,0x3C,0x35,0x32,0x1F,0x18,0x11,0x16,0x03,0x04,0x0D,0x0A,
	0x57,0x50,0x59,0x5E,0x4B,0x4C,0x45,0x42,0x6F,0x68,0x61,0x66,0x73,0x74,0x7D,0x7A,
	0x89,0x8E,0x87,0x80,0x95,0x92,0x9B,0x9C,0xB1,0xB6,0xBF,0xB8,0xAD,0xAA,0xA3,0xA4,
	0xF9,0xFE,0xF7,0xF0,0xE5,0xE2,0xEB,0xEC,0xC1,0xC6,0xCF,0xC8,0xDD,0xDA,0xD3,0xD4,
	0x69,0x6E,0x67,0x60,0x75,0x72,0x7B,0x7C,0x51,0x56,0x5F,0x58,0x4D,0x4A,0x43,0x44,
	0x19,0x1E,0x17,0x10,0x05,0x02,0x0B,0x0C,0x21,0x26,0x2F,0x28,0x3D,0x3A,0x33,0x34,
	0x4E,0x49,0x40,0x47,0x52,0x55,0x5C,0x5B,0x76,0x71,0x78,0x7F,0x6A,0x6D,0x64,0x63,
	0x3E,0x39,0x30,0x37,0x22,0x25,0x2C,0x2B,0x06,0x01,0x08,0x0F,0x1A,0x1D,0x14,0x13,
	0xAE,0xA9,0xA0,0xA7,0xB2,0xB5,0xBC,0xBB,0x96,0x91,0x98,0x9F,0x8A,0x8D,0x84,0x83,
	0xDE,0xD9,0xD0,0xD7,0xC2,0xC5,0xCC,0xCB,0xE6,0xE1,0xE8,0xEF,0xFA,0xFD,0xF4,0xF3
};

uint8_t  CRC8cal(uint8_t *p, uint8_t counter)    		   //look-up table calculte CRC 
{    
    uint8_t crc8 = 0;    
    
	for( ; counter > 0; counter--)
	{    
		crc8 = CRC8Table[crc8^*p];    
	    p++;    
    }    
    return(crc8);    //返回CRC8值    
}  

void OUT_OUT(uint32_t Gpio_Out,uint32_t Pin_Out)
{
	uint16_t i=0;
	uint32_t reg=0;
	uint32_t temp_mode=0;
	temp_mode = (uint32_t)(GPIO_Mode_Out_PP & ((uint32_t)0x0FU));
	temp_mode |= (uint32_t)(GPIO_Speed_50MHz);
 for(i = 0U;i < 8U;i++)
	{
 if((1U << i) & Pin_Out)
	 {
            reg = GPIO_CTL0(Gpio_Out);
            reg &= ~GPIO_MODE_MASK(i);
            reg |= GPIO_MODE_SET(i, temp_mode);  
            GPIO_CTL0(Gpio_Out) = reg;
    }
   }
for(i = 8U;i < 16U;i++)
	 {
        if((1U << i) & Pin_Out)
					{
            reg = GPIO_CTL1(Gpio_Out);
            reg &= ~GPIO_MODE_MASK(i - 8U);
            reg |= GPIO_MODE_SET(i - 8U, temp_mode);
						GPIO_CTL1(Gpio_Out) = reg;
            }
            
     }
}
//通过位配置变为输入模式
void OUT_IN(uint32_t Gpio_Out,uint32_t Pin_Out)
{
	uint16_t i=0;
	uint32_t reg=0;
	uint32_t temp_mode=0;
	temp_mode = (uint32_t)(GPIO_Mode_IPU&((uint32_t)0x0FU));
	for(i = 0U;i < 8U;i++)
	{
 if((1U << i) & Pin_Out)
	 {
            reg = GPIO_CTL0(Gpio_Out);
            reg &= ~GPIO_MODE_MASK(i);
            reg |= GPIO_MODE_SET(i, temp_mode); 
		      //GPIO_BC(Gpio_Out) = (uint32_t)((1U << i) & Pin_Out);
            GPIO_BOP(Gpio_Out) = (uint32_t)((1U << i) & Pin_Out);
            GPIO_CTL0(Gpio_Out) = reg;
    }
   }
for(i = 8U;i < 16U;i++)
	 {
        if((1U << i) & Pin_Out)
					{
            reg = GPIO_CTL1(Gpio_Out);
            reg &= ~GPIO_MODE_MASK(i - 8U);
            reg |= GPIO_MODE_SET(i - 8U, temp_mode);
			    //GPIO_BC(Gpio_Out) = (uint32_t)((1U << i) & Pin_Out);     //down
            GPIO_BOP(Gpio_Out) = (uint32_t)((1U << i) & Pin_Out);    //up
						GPIO_CTL1(Gpio_Out) = reg;

               
            
            }
            
     }
}
/*******************************************************************************
Function:ErrorStatus  Analog_IIC_Write(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint16_t WrAddr,uint8_t Length,uint8_t  *WrBuf)
Description:IIC向外设写入数据,最底层的函数, SlaveID为外设名称,WrAddr寄存器地址,Length为长度(字节 8bits),WrBuf为数据
Input:  NULL	
Output: NULL
Others:是另一种写IIc的方式,是不需要发送CRC8的校验码,,,,可以服务于EEPROM
*******************************************************************************/
ErrorStatus  I2C_Write_One_BYTE(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t  WrBuf)
{
	IIC_Start(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//通讯开始
	SlaveID=SlaveID&0xFE;
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,SlaveID);//先发送从机的地址，寻址从机
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,WrAddr);//寻址这个器件中的相关寄存器
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,WrBuf);//发送一个字节
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
	return SUCCESS;
}




 /*******************************************************************************
FunctionErrorStatus:ErrorStatus  I2C_Read_BYTE_Mode1(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t  *RdWrBuf,uint8_t CRC8)
Description:根据地址访问数据,需要提供字节长度
Input:  NULL	
Output: NULL
 Others:也是主要服务于EEprom,不用 发送CRC8校验位
*******************************************************************************/
 ErrorStatus  I2C_Read_BYTE_Mode2(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t Length,uint8_t  *RdBuf)
{
	uint8_t i=0;
	IIC_Start(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//通讯开始
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,SlaveID);//先发送从机的地址，寻址从机
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
  I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯	
	return ERROR;
	}
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,WrAddr);//寻址这个器件中的相关寄存器
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯	
	return ERROR;
	}
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,Length);//只有SH 
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
  I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯	
	return ERROR;
	}
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,(SlaveID|0x01));//先发送从机的地址，寻址从机,并附带读的标志位
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
	return ERROR;
	}
	for(i=0;i<=Length;i++)    
	{
	I2C_Read (Gpio_SDA, Pin_SDA, Gpio_SCL, Pin_SCL, RdBuf);
	I2C_Ack( Gpio_SDA, Pin_SDA, Gpio_SCL, Pin_SCL);  //回复响应信号
	RdBuf++;
	}   //从原理上说,到达规定的字节后,应该是发送CRC8了,需要不需要现在发NONACK需要具体再看
	I2C_NoAck(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);  //表示无应答,即通信结束
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
  return SUCCESS;
}
 




/*******************************************************************************
Function:ErrorStatus  Analog_IIC_Write(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint16_t WrAddr,uint8_t Length,uint8_t  *WrBuf)
Description:IIC向外设写入数据,最底层的函数, SlaveID为外设名称,WrAddr寄存器地址,Length为长度(字节 8bits),WrBuf为数据
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
ErrorStatus  I2C_SEND_One_BYTE(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t  WrBuf)
 {
	uint8_t TempBuf[4];
	TempBuf[0]=SlaveID;
	TempBuf[1]=WrAddr;
	TempBuf[2]=WrBuf;     //
	TempBuf[3]=CRC8cal(TempBuf,3);   //求CRC8的值
	IIC_Start(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//通讯开始
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,SlaveID);//先发送从机的地址，寻址从机
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,WrAddr);//寻址这个器件中的相关寄存器
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,WrBuf);//发送一个字节
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,TempBuf[3]);//发送一个字节
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
	return SUCCESS;
 }

 /*******************************************************************************
FunctionErrorStatus:ErrorStatus  I2C_Read_BYTE(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t  *RdWrBuf,uint8_t CRC8)
Description:根据地址访问数据,需要提供字节长度
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
 ErrorStatus  I2C_Read_BYTE_Mode1(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint8_t WrAddr,uint8_t Length,uint8_t  *RdBuf)
{
	uint8_t i=0;
	uint8_t RdCrc=0;  //存放从设备返回的CRC校验位
	uint8_t TempBuf[60];
  TempBuf[0] = SlaveID;
  TempBuf[1] = WrAddr;
  TempBuf[2] = Length;
	TempBuf[3] = SlaveID|0x01;

	IIC_Start(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//通讯开始
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,SlaveID);//先发送从机的地址，寻址从机
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
  I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯	
	return ERROR;
	}
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,WrAddr);//寻址这个器件中的相关寄存器
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯	
	return ERROR;
	}
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,Length);//只有SH 
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
  I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯	
	return ERROR;
	}
	IIC_Start(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//通讯开始
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,SlaveID|0x01);//先发送从机的地址，寻址从机
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL)){//得到回应，说明，电路中有这个外设器件
  I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯	
	return ERROR;
	}
	for(i=0;i<Length;i++)    
	{
	I2C_Read (Gpio_SDA, Pin_SDA, Gpio_SCL, Pin_SCL, &TempBuf[4+i]);
	I2C_Ack( Gpio_SDA, Pin_SDA, Gpio_SCL, Pin_SCL);  //回复响应信号
	}   //从原理上说,到达规定的字节后,应该是发送CRC8了,需要不需要现在发NONACK需要具体再看
	I2C_Read (Gpio_SDA, Pin_SDA, Gpio_SCL, Pin_SCL, &RdCrc);
	if(RdCrc == CRC8cal(TempBuf, 4+Length))
	{
	  for(i=0; i<Length; i++)
    {
     *RdBuf = TempBuf[4+i];
	   RdBuf++;
	  }
  }
	else
	{
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
	 return ERROR;	
		
	}
	I2C_NoAck(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);  //表示无应答,即通信结束
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
  return SUCCESS;
}
 

 
 /*******************************************************************************
Function:ErrorStatus  Analog_IIC_Write(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint16_t WrAddr,uint8_t Length,uint8_t  *WrBuf)
Description:IIC向外设写入数据,最底层的函数, SlaveID为外设名称,WrAddr寄存器地址,Length为长度(字节 8bits),WrBuf为数据
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
 /*
ErrorStatus I2C_SEND_BYTES(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t SlaveID,uint16_t WrAddr,uint8_t Length,uint8_t  *WrBuf)
{
	uint8_t t=0;
  IIC_Start(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//通讯开始
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,SlaveID);//先发送从机的地址，寻址从机
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;
	I2C_SEND(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL,WrAddr);//寻址这个器件中的相关寄存器
	if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	return ERROR;

	for(t=0;t<Length;t++)//发送数组中的数据
	{
			if(!I2C_Wait_Ack(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL))//得到回应，说明，电路中有这个外设器件
	    return ERROR;
	}
	I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
  return SUCCESS;
}
*/ 
 
 /*******************************************************************************
Function:ErrorStatus  void IIC_Start(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL) 
Description:通讯函数开始函数,写入start位,在SCL高电平时,SDA有下降沿
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/
void IIC_Start(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL)  //通讯函数开始函数
{
	OUT_OUT(Gpio_SDA,Pin_SDA);//设置pin脚的方向是输出，意味着主机向从机发数据了
	High(Gpio_SCL,Pin_SCL);//先拉高时钟线
	High(Gpio_SDA,Pin_SDA);//再拉高数据线

	delay_1us(delay_Time_us);//延迟2us，延迟是有必要的，参照I2C协议写的
	Low(Gpio_SDA,Pin_SDA);//拉低数据线，触发通讯

	delay_1us(delay_Time_us);//延迟2us
	Low(Gpio_SCL,Pin_SCL);//拉低时钟线，方便数据线上的数据变化
}
 /*******************************************************************************
Function:ErrorStatus  void I2C_STOP(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL) 
Description:通讯函数结束函数,在SCL高电平时,SDA有上升沿,表示通讯结束
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/


void I2C_STOP(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL)
{
	OUT_OUT(Gpio_SDA,Pin_SDA);//设置pin脚的方向是输出，意味着主机向从机发数据了();//设置pin脚的方向是输出，意味着主机向从机发数据了
	Low(Gpio_SDA,Pin_SDA);//先拉底数据线
	High(Gpio_SCL,Pin_SCL);//再拉高时钟线

	delay_1us(delay_Time_us);//延迟2us
	High(Gpio_SDA,Pin_SDA);//拉高数据线，终止通讯
	delay_1us(delay_Time_us);//延迟2us
}
 /*******************************************************************************
Function:void I2C_SEND(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t byte)
Description:在下降沿,或者是SCL为低电平的时候,改变SDA电平...而在高电平的时候,为读取电压
Input:  NULL	
Output: NULL
Others:
*******************************************************************************/

void I2C_SEND(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t byte)
{
uint8_t	 t=0;
OUT_OUT(Gpio_SDA,Pin_SDA);//设置pin脚的方向是输出，意味着主机向从机发数据了();//设置pin脚的方向是输出，意味着主机向从机发数据了	
for(t=0;t<8;t++)//按位显示状态，传输一个字节，也就是8位状态
	{
		
		if(byte&0x80)//判断字节的最高位，如果为1，输出高电平，如果为0，输出低电平
		{
			High(Gpio_SDA,Pin_SDA);
		}
		else
		{
			Low(Gpio_SDA,Pin_SDA);;
		}
		byte<<=1;//移位操作，遍历总共的8位
		delay_1us(delay_Time_us);
		High(Gpio_SCL,Pin_SCL);//钳住数据，高电平数据线上的状态就改变不了了
		delay_1us(delay_Time_us);
		Low(Gpio_SCL,Pin_SCL);//置低位，为下次数据线上的状态改变做准备
	}
}

void I2C_Read(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL,uint8_t *byte)
{
	uint8_t i=0;
	uint8_t receive=0;
	OUT_IN(Gpio_SDA,Pin_SDA);
	for(i=0;i<8;i++)
		{
			Low(Gpio_SCL,Pin_SCL);//scl拉低，sda总线变化
			delay_1us(delay_Time_us);//
			High(Gpio_SCL,Pin_SCL);//scl拉高，sda总线锁死
			
			receive=(receive<<1)|Read_Data(Gpio_SDA,Pin_SDA);//读取数据总线的数据，按位来读取，从高位读到低位，移位顺延
			delay_1us(delay_Time_us);	
		}
		*byte=receive;
}



ErrorStatus I2C_Wait_Ack(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL)
{
	uint8_t   ucErrTime=0;  //记录超时的计数参数
	OUT_IN(Gpio_SDA,Pin_SDA);       //SDA设为输入，说明主机现在处于接收数据状态，等待从机发送数据
	Low(Gpio_SCL,Pin_SCL);delay_1us(delay_Time_us);
	High(Gpio_SCL,Pin_SCL);delay_1us(delay_Time_us);
	while(Read_Data(Gpio_SDA,Pin_SDA))//非应答时进入此状态,,,配置为上拉输入
	{
		ucErrTime++;//计数加
		if(ucErrTime>250)//计数大于250说明无响应，终止通讯
		{
	   I2C_STOP(Gpio_SDA,Pin_SDA,Gpio_SCL,Pin_SCL);//终止通讯
			return ERROR ;
		}
	}
//	High(Gpio_SCL,Pin_SCL);delay_1us(delay_Time_us);
	Low(Gpio_SCL,Pin_SCL);//scl拉低，sda总线变化
	delay_1us(delay_Time_us);
	return SUCCESS ;
}



void I2C_Ack(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL)
{
	Low(Gpio_SCL,Pin_SCL);//SCL线先置低，方便数据线上变化数据
	
	OUT_OUT(Gpio_SDA,Pin_SDA);//Sda端口变成输出模式
	Low(Gpio_SDA,Pin_SDA); ////SDA线置低，代表响应应答
	delay_1us(delay_Time_us);
	High(Gpio_SCL,Pin_SCL);//SCL钳住数据，数据不可变
	delay_1us(delay_Time_us);
	Low(Gpio_SCL,Pin_SCL);//结束响应的时段	
  High(Gpio_SDA,Pin_SDA);//CPU释放数据总线
}



void I2C_NoAck(uint32_t Gpio_SDA,uint32_t Pin_SDA,uint32_t Gpio_SCL,uint32_t Pin_SCL)
{
	Low(Gpio_SCL,Pin_SCL);//SCL线先置低，方便数据线上变化数据
	
	OUT_OUT(Gpio_SDA,Pin_SDA);//Sda端口变成输出模式
	High(Gpio_SDA,Pin_SDA); //SDA线置高，代表不响应应答
	delay_1us(delay_Time_us);
	High(Gpio_SCL,Pin_SCL);//SCL钳住数据，数据不可变
	delay_1us(delay_Time_us);
	Low(Gpio_SCL,Pin_SCL);//结束响应的时段	
  High(Gpio_SDA,Pin_SDA);//CPU释放数据总线
}
	


