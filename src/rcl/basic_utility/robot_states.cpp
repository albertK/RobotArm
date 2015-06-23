#include "rcl/basic_utility/robot_states.h"
#include "rcl/common/parameters.h"
#include "rcl/basic_utility/motor_joint.h"

using namespace rcl::Parameters::Common;

void rcl::RobotStates::update()
{
    //joint
    current_joint_position_ = motor_joint.getCurrentPosition();
    current_joint_velocity_ = motor_joint.getCurrentVelocity();
    current_joint_acceleration_ = motor_joint.getCurrentAcceleration();
    current_joint_torque_ = motor_joint.getCurrentTorque();
}

std::vector< float > rcl::RobotStates::getCurrentJointPosition()
{
    return current_joint_position_;
}

std::vector< float > rcl::RobotStates::getCurrentJointVelocity()
{
    return current_joint_velocity_;
}

std::vector< float > rcl::RobotStates::getCurrentJointAcceleration()
{
    return current_joint_acceleration_;
}

std::vector< float > rcl::RobotStates::getCurrentJointTorque()
{
    return current_joint_torque_;
}
