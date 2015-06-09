#ifndef PARAMETERS
#define PARAMETERS

#include <vector>

namespace rcl
{
    namespace parameters
    {
	struct Common
	{
	    static int sampling_time = 1;//ms
	    static const int dof = 7;
	    static const int dof_lc = dof*(dof-1)/2;//for dynamics coriolis term
	};
	
	struct MotorJoint
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
	    
	    static std::vector<float> gear_ratio;
	};
    };
};

#endif