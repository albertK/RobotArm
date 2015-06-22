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
	    static const int enc_6x = 0;
	    static const std::string enc_6x_dev = "/dev/ixpio1";
	    //3-axis encoder card
	    static const int enc_3x = 2;
	    static const std::string enc_3x_dev = "/dev/ixpio2";
	    
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
	    
	    //torque constant. in mNm/A
	    static const float torq_const[] = {0.0385, 0.0385, 0.0302, 0.0302, 0.0259, 0.0259, 0.0208};
	    
	    //maximun allowable current for each motor. in A
	    static const float max_current[] = {10.0, 10.0, 6.0, 6.0, 3.5, 3.5, 1.5};
	    
	    static const int enc_count[] = {2000, 2000, 2000, 2000, 2000, 2000, 2000};
	    static const int gear_ratio[] = {483, 483, 404, 404, 404, 404, 204};
	    static const int reduction[] = {enc_count[0]*gear_ratio[0], enc_count[1]*gear_ratio[1], enc_count[2]*gear_ratio[2], enc_count[3]*gear_ratio[3], enc_count[4]*gear_ratio[4], enc_count[5]*gear_ratio[5], enc_count[6]*gear_ratio[6]};
	    static const float deg_per_count[] = {360.0/reduction[0], 360.0/reduction[1], 360.0/reduction[2], 360.0/reduction[3], 360.0/reduction[4], 360.0/reduction[5], 360.0/reduction[6]};
	    static const float count_per_deg[] = {reduction[0]/360.0, reduction[1]/360.0, reduction[2]/360.0, reduction[3]/360.0, reduction[4]/360.0, reduction[5]/360.0, reduction[6]/360.0};
	    
	    //reference position for each joint. in degree
	    static const float home[] = {0.0, -90.0, 0.0, 180.0, 0.0, 0.0, 0.0};
	    
	    static const int dir[] = {-1, 1, -1, 1, -1, 1, -1};
	};
    };
};

#endif