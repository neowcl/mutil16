#include "system_clock_configuration.h" 


/*@brief 以XTAL晶振进行的时钟配置
*@  X: C8M                    C8M；8MHZ晶振
*/

//void  AHB_HXTAL72M(uint16_t X)             
//{
//	  AHBCLOCK_confi_struct CL72M={0,0,0};
//switch(X)	
//{
//	case(1):                   //8M
//               {
//            
//              CL72M.PREDV0= RCU_PREDV0_DIV1;                            //RCU_PREDV0_DIVx, x = 1,2
//              CL72M.PLLMF= RCU_PLL_MUL2;                               // RCU_PLL_MULx (XD series x = 2..32, CL series x = 2..14, 6.5, 16..32)
//              CL72M.AHB_PRESCALER=RCU_AHB_CKSYS_DIV1;                                //RCU_AHB_CKSYS_DIVx, x=1, 2, 4, 8, 16, 64, 128, 256, 512
//               break;
//							 }
//	}
//  AHB_clock(&CL72M);

//}



//void  AHB_clock(AHBCLOCK_confi_struct* AHB_struct)
//{
//	rcu_predv0_config(AHB_struct->PREDV0);   //  可能默认为HXTAL
//	rcu_pll_config(RCU_PLLSRC_HXTAL,AHB_struct->PLLMF);  //选择和配置
//	rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);   // 选择
//	rcu_ahb_clock_config(AHB_struct->AHB_PRESCALER); // 配置ahb prescaler
//}



//void rcu_periph_drive_clock_enable(rcu_periph_enum RCU_periph)
//{
//	rcu_periph_clock_enable(RCU_periph);
//}



