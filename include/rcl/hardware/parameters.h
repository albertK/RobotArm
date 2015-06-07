#ifndef PARAMETERS
#define PARAMETERS

#include <vector>

namespace rcl
{
    namespace parameters
    {
	struct Common
	{
	    float sampling_time;
	    float dof;
	};
	
	struct Mechanism
	{

	};
	
	struct MotorJoint
	{
	    std::vector<float> p_min;
	    std::vector<float> p_max;
	    std::vector<float> v_min;
	    std::vector<float> v_max;
	    std::vector<float> t_min;
	    std::vector<float> t_max;
	    
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