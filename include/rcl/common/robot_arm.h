#ifndef ROBOTARM
#define ROBOTARM

#include "rcl/application/skill.h"
#include "rcl/application/default_mode.h"
#include "rcl/application/cartesian_mode.h"
#include "rcl/application/joint_mode.h"

#include "rcl/basic_utility/robot_states.h"
#include "rcl/basic_utility/motor_joint.h"
#include "rcl/basic_utility/kinematics.h"
#include "rcl/basic_utility/dynamics.h"

#include "rcl/common/parameters.h"
#include "rcl/hardware/analog_output.h"
#include "rcl/hardware/encoder.h"

namespace rcl
{
    class RobotArm
    {
    public:
	Skill* skill;
	DefaultMode default_mode;
	JointMode joint_mode;
	
	RobotStates robot_states;
	MotorJoint motor_joint;
	Kinematics kinematics;
	Dynamics dynamics;
	
	AnalogOutput ao;
	Encoder encoder;
    };
};

#endif