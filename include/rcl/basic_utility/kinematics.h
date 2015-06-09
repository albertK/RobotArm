#ifndef KINEMATICS
#define KINEMATICS

#include <vector>

#include <eigen3/Eigen/Dense>

#include "rcl/common/parameters.h"

namespace rcl
{
    class Kinematics
    {
    public:
	static Eigen::Matrix4f fk(std::vector<float> joint_angle);
	static std::vector<float> ik(Eigen::Matrix4f eef_pose);
	static Eigen::Matrix<float, 6, Parameters::Common::dof> jacobian(std::vector<float> joint_angle);
    };
};

#endif