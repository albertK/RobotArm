#ifndef DYNAMICS
#define DYNAMICS

#include <vector>

#include <eigen3/Eigen/Dense>

#include "rcl/common/parameters.h"

namespace rcl
{
    class Dynamics
    {
    public:
	static Eigen::Matrix<float, 6, Parameters::Common::dof> mass(std::vector<float> joint_angle);
	static Eigen::Matrix<float, 6, Parameters::Common::dof> centrifugal(std::vector<float> joint_angle);
	static Eigen::Matrix<float, 6, Parameters::Common::dof_lc> coriolis(std::vector<float> joint_angle);
	static std::vector<float> gravity(std::vector<float> joint_angle);
    };
};

#endif