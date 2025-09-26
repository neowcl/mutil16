#include "Can_drive.h"






void  can_message_transmit_m_d(uint32_t canx,can_trans_message* transmit_message)
{
can_message_transmit(canx,transmit_message);
}







