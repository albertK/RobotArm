#ifndef ROBOTSTATES
#define ROBOTSTATES

#include <vector>

#include <eigen3/Eigen/Dense>

#include "rcl/common/parameters.h"

//Ref http://stackoverflow.com/questions/2133250/does-not-name-a-type-error-in-c
class RobotArm;

namespace rcl
{
    class RobotStates
    {
    protected:
	std::vector<float> current_joint_position_;
	std::vector<float> current_joint_velocity_;
	std::vector<float> current_joint_torque_;
	std::vector<Eigen::Matrix4f> current_link_pose_;
	Eigen::Matrix4f current_eef_pose_;
	Eigen::Vector3f current_eef_position_;
	Eigen::Vector3f current_eef_orientation_;
	Eigen::Vector4f current_eef_quaternion_;
	Eigen::Matrix<float, 6, Parameters::Common::dof> jacobian_;
	
	Eigen::Matrix<float, 6, Parameters::Common::dof> mass_;
	Eigen::Matrix<float, 6, Parameters::Common::dof> centrifugal_;
	Eigen::Matrix<float, 6, Parameters::Common::dof_lc> coriolis_;
	std::vector<float> gravity_;
	
	std::vector<float> target_joint_position_;
	std::vector<float> target_joint_velocity_;
	std::vector<float> target_joint_torque_;
	Eigen::Matrix4f target_eef_pose_;
	Eigen::Vector3f target_eef_position_;
	Eigen::Vector3f target_eef_orientation_;
	Eigen::Vector4f target_eef_quaternion_;
	
    
    public:
	std::vector<float> getCurrentJointPposition();
	std::vector<float> getCurrentJointVelocity();
	std::vector<float> getCurrentJointTorque();
	std::vector<Eigen::Matrix4f> getCurrentLinkPose();
	Eigen::Matrix4f getCurrentEEFPose();
	Eigen::Vector3f getCurrentEEFPosition();
	Eigen::Vector3f getCurrentEEFOrientation();
	Eigen::Vector4f getCurrentEEFQuaternion();
	Eigen::Matrix<float, 6, Parameters::Common::dof> getJacobian();
	
	Eigen::Matrix<float, 6, Parameters::Common::dof> getMass();
	Eigen::Matrix<float, 6, Parameters::Common::dof> getCentrifugal();
	Eigen::Matrix<float, 6, Parameters::Common::dof_lc> getCoriolis();
	std::vector<float> getGravity();
	
	std::vector<float> getTargetJointPosition();
	std::vector<float> getTargetJointVelocity();
	std::vector<float> getTargetJointTorque();
	Eigen::Matrix4f getTargetEEFPose();
	Eigen::Vector3f getTargetEEFPosition();
	Eigen::Vector3f getTargetEEFOrientation();
	Eigen::Vector4f getTargetEEFQuaternion();
    };
};

#endif