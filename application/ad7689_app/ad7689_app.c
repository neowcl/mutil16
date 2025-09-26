#include "ad7689_app.h"
#include "ad7689_interface.h"
uint16_t  acquisition_data[7]={0,0,0,0,0,0,0}; //共有8个通道，所以放8个数组，16位数据


void ad7689_acquisition()
{
ad7689_part1_converstion_start();
	while(1)
	{
    ad7689_converstion_getdata_inter(IN0,acquisition_data);
		ad7689_converstion_getdata_inter(IN1,acquisition_data);
		ad7689_converstion_getdata_inter(IN2,acquisition_data);
		ad7689_converstion_getdata_inter(IN3,acquisition_data);
		ad7689_converstion_getdata_inter(IN4,acquisition_data);
		ad7689_converstion_getdata_inter(IN5,acquisition_data);
		ad7689_converstion_getdata_inter(IN6,acquisition_data);
	  ad7689_converstion_getdata_inter(IN7,acquisition_data);
	}
}









