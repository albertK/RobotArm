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
	    static const int sampling_time = 1;//ms
	    static const int dof = 7;
	    static const int dof_lc = dof*(dof-1)/2;//for dynamics coriolis term
	};
	
	namespace CommunicationInterface
	{
	    //device name of analog output card.
	    static const std::string ao_dev = "/dev/ixpio3";
	    static const int channel = 8;
	    
	    //6-axis encoder card
	    static const int enc_card_0 = 0;
	    //3-axis encoder card
	    static const int enc_card_1 = 1;
	    
	    //encoder mode
	    static const int mode = ENC_QUADRANT;
	};
	
	namespace MotorJoint
	{
	    //joint limit
	    static std::vector<float> p_min;
	    static std::vector<float> p_max;
	    static std::vector<float> v_min;
	    static std::vector<float> v_max;
	    static std::vector<float> t_min;
	    static std::vector<float> t_max;
	    
	    //controller PID parameters
	    static std::vector<float> pp;
	    static std::vector<float> pi;
	    static std::vector<float> pd;
	    static std::vector<float> vp;
	    static std::vector<float> vi;
	    static std::vector<float> vd;
	    //TODO
	    static float accu_max;
	    
	    //TODO unit?
	    static float torq_const[] = {0.0385, 0.0385, 0.0302, 0.0302, 0.0259, 0.0259, 0.0208};
	    
	    static int enc_count[] = {2000, 2000, 2000, 2000, 2000, 2000, 2000};
	    static int gear_ratio[] = {483, 483, 404, 404, 404, 404, 204};
	    //reference position for each joint. in degree
	    static float home[] = {0.0, -90.0, 0.0, 180.0, 0.0, 0.0, 0.0};
	};
    };
};

#endif