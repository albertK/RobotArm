#ifndef PARAMETERS
#define PARAMETERS

#include <vector>
#include <string>

#include "msw-enc600.h"

namespace rcl
{
    namespace Parameters
    {
	namespace Common
	{
	    const int sampling_time = 1;//ms
	    const int dof = 7;
	    const int dof_lc = dof*(dof-1)/2;//for dynamics coriolis term
	};
	
	namespace CommunicationInterface
	{
	    //device name of analog output card.
	    const std::string ao_dev = "/dev/ixpio3";
	    const int channel = 8;
	    
	    //6-axis encoder card
	    const int enc_card_0 = 0;
	    //3-axis encoder card
	    const int enc_card_1 = 1;
	    const int mode = ENC_QUADRANT;
	};
	
	namespace MotorJoint
	{
	    //joint limit
	    std::vector<float> p_min;
	    std::vector<float> p_max;
	    std::vector<float> v_min;
	    std::vector<float> v_max;
	    std::vector<float> t_min;
	    std::vector<float> t_max;
	    
	    //controller PID parameters
	    std::vector<float> pp;
	    std::vector<float> pi;
	    std::vector<float> pd;
	    std::vector<float> vp;
	    std::vector<float> vi;
	    std::vector<float> vd;
	    
	    std::vector<float> gear_ratio;
	};
    };
};

#endif