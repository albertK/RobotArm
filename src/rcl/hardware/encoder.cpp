#include "msw-enc600.h"

#include "rcl/hardware/encoder.h"
#include "rcl/common/parameters.h"

bool rcl::Encoder::init(int card, char mode)
{
    card_0_ = rcl::Parameters::CommunicationInterface::enc_card_0;
    card_1_ = rcl::Parameters::CommunicationInterface::enc_card_1;
    
    if(ENC6_REGISTRATION(card_0_, 0) && ENC6_REGISTRATION(card_1_, 0) != SUCCESS)
    {
	return false;
    }
    
    ENC6_INIT_CARD(card_0_, mode, mode, mode, mode, mode, mode);
    ENC6_INIT_CARD(card_1_, mode, mode, mode, mode, mode, mode);
    
    ENC6_RESET_ENCODER(card_0_, X1_axis);
    ENC6_RESET_ENCODER(card_0_, X2_axis);
    ENC6_RESET_ENCODER(card_0_, X3_axis);
    ENC6_RESET_ENCODER(card_0_, X4_axis);
    ENC6_RESET_ENCODER(card_0_, X5_axis);
    ENC6_RESET_ENCODER(card_0_, X6_axis);
    
    ENC6_RESET_ENCODER(card_1_, X1_axis);
    ENC6_RESET_ENCODER(card_1_, X2_axis);
    ENC6_RESET_ENCODER(card_1_, X3_axis);
}

void rcl::Encoder::quit()
{
    /*
     * WARNING
     * make sure that this will not close the analog device
     */
    closeDev();
}

long rcl::Encoder::getCount(int channel)
{
    long count;
    switch (channel)
    {
	case 0:
	    count = ENC6_GET_ENCODER(card_0_,X1_axis);
	    break;
	case 1:
	    count = ENC6_GET_ENCODER(card_0_,X2_axis);
	    break;
	case 2:
	    count = ENC6_GET_ENCODER(card_0_,X3_axis);
	    break;
	case 3:
	    count = ENC6_GET_ENCODER(card_0_,X4_axis);
	    break;
	case 4:
	    count = ENC6_GET_ENCODER(card_0_,X5_axis);
	    break;
	case 5:
	    count = ENC6_GET_ENCODER(card_0_,X6_axis);
	    break;
	case 6:
	    count = ENC6_GET_ENCODER(card_1_,X1_axis);
	    break;
    }
    
    return count;
}
