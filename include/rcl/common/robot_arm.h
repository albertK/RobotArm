#ifndef ROBOTARM
#define ROBOTARM

#include <string>

#include "rcl/application/skill.h"
#include "rcl/application/default_mode.h"
#include "rcl/application/cartesian_mode.h"
#include "rcl/application/joint_mode.h"
#include "rcl/application/intuive_teach.h"

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
    protected:
	std::string mode_;
	void clock1_update();
	void clock2_update();
	void clock3_update();
    public:
	//initialize the robot including all the sub modules and hardware
	void init();
	
	//after the call to init(), go to the ready pose
	void ready();
	
	/*
	 * choose what application to use now
	 * car: Cartesian Mode
	 * def: Default Mode
	 * int: Intuive Teach Mode
	 * joi: Joint Mode
	 */
	void setApplicationMode(std::string mode);
	
	//release resources, do garbage collection. call when exit the program
	void quit();
	
	//Skill* skill;
	//DefaultMode default_mode;
	//JointMode joint_mode;
	//CartesianMode cartesian_mode;
	//IntuiveTeach intuive_teach;
	
	//RobotStates robot_states;
	//MotorJoint motor_joint;
	//Kinematics kinematics;
	//Dynamics dynamics;
	
	AnalogOutput ao;
	//Encoder encoder;
    };
};

#endif