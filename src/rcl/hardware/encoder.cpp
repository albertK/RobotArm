#include <stdio.h>
#include <stdlib.h>
#include "msw-enc600.h"

#include "rcl/hardware/encoder.h"
#include "rcl/common/parameters.h"

using namespace rcl::Parameters::CommunicationInterface;

bool rcl::Encoder::init()
{
    if(!init_)
    {
	if(ENC6_REGISTRATION(enc_3x, enc_3x_dev.c_str()) && ENC6_REGISTRATION(enc_6x, enc_6x_dev.c_str()) != SUCCESS)
	{
	    return false;
	}
	
	ENC6_INIT_CARD(enc_3x, mode, mode, mode, mode, mode, mode);
	ENC6_INIT_CARD(enc_6x, mode, mode, mode, mode, mode, mode);
	
	ENC6_RESET_ENCODER(enc_6x, X1_axis);
	ENC6_RESET_ENCODER(enc_6x, X2_axis);
	ENC6_RESET_ENCODER(enc_6x, X3_axis);
	ENC6_RESET_ENCODER(enc_6x, X4_axis);
	ENC6_RESET_ENCODER(enc_6x, X5_axis);
	ENC6_RESET_ENCODER(enc_6x, X6_axis);
	
	ENC6_RESET_ENCODER(enc_3x, X1_axis);
	ENC6_RESET_ENCODER(enc_3x, X2_axis);
	ENC6_RESET_ENCODER(enc_3x, X3_axis);
	
	init_ = true;
    }
    
    return true;
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
	    count = ENC6_GET_ENCODER(enc_6x,X1_axis);
	    break;
	case 1:
	    count = ENC6_GET_ENCODER(enc_6x,X2_axis);
	    break;
	case 2:
	    count = ENC6_GET_ENCODER(enc_6x,X3_axis);
	    break;
	case 3:
	    count = ENC6_GET_ENCODER(enc_6x,X4_axis);
	    break;
	case 4:
	    count = ENC6_GET_ENCODER(enc_6x,X5_axis);
	    break;
	case 5:
	    count = ENC6_GET_ENCODER(enc_6x,X6_axis);
	    break;
	case 6:
	    count = ENC6_GET_ENCODER(enc_3x,X1_axis);
	    break;
    }
    
    return count;
}
