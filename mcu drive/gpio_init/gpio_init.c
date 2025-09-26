#include "./GPIO_Init/GPIO_Init.h" 
#include "./systick/systick.h" 

/*
@brief   主要是配置了io口，输入或者输出的模式，可以应用到有关输入或者输出的环境治中风，比如说
led的点亮，或者按键的输出情况。
@date：20220701
@aut：ma
*/
void gpio_mode_init(gpio_drive_init* GIOP_struct)
{
	GPIO_InitTypeDef  GPIO_Init_tempt;
	GPIO_Init_tempt.GPIO_Mode=GIOP_struct->GPIO_Mode;
	GPIO_Init_tempt.GPIO_Pin=GIOP_struct->GPIO_Pin;
	GPIO_Init_tempt.GPIO_Speed=GIOP_struct->GPIO_Speed;
	
	if(GIOP_struct->GPIO_Speed==ENABLE)      //判断是否需要管脚复用
	{
		//rcu_periph_clock_enable(GIOP_struct->fuyongpin);//管脚复用时钟alternate function clock使能
		delay_1ms(1);//等待1秒
		GPIO_PinRemapConfig(GIOP_struct->GPIO_Remap,ENABLE);
	}
//	rcu_periph_clock_enable(GIOP_struct->RCU_GPIO);
	
	GPIO_Init(GIOP_struct->GPIO,&GPIO_Init_tempt);//配置输出	
}
/*

@BRIEF   设置了GPIO 输出高电平和或者低电平的时间，以及对应的管脚、
@date     202207011654
*/



void GPIO_WORK_TIME(uint32_t ONTIME,uint32_t OFFTIME,GPIO_TypeDef* Gpiox,uint32_t Gpio_Pin)
{
	if((OFFTIME!=0)&&(ONTIME!=0))
	{
	gpio_bit_reset_drive(Gpiox,Gpio_Pin);
	delay_1us(OFFTIME);
	gpio_bit_set_drive(Gpiox,Gpio_Pin);    //高电平关闭LED 灯
	delay_1us(ONTIME);
	}
	else if(OFFTIME==0)
	{
		gpio_bit_set_drive(Gpiox,Gpio_Pin);    //高电平关闭LED 灯
	}
	else if(ONTIME==0)
	{
	gpio_bit_reset_drive(Gpiox,Gpio_Pin);
	}

}

/*
读取相应管脚的电平
*/
















