#ifndef MOTORJOINT
#define MOTORJOINT

#include <vector>

#include "rcl/common/robot_arm.h"

namespace rcl
{
    class MotorJoint
    {
    protected:
	RobotArm* root_;
	
	//motor control mode
	char mode_;
	
	//reference position for each joint. in degree
	std::vector<float> home_;
	
	//target position command
	std::vector<float> target_pos_;
	std::vector<float> target_vel_;
	std::vector<float> target_torq;
	
	//current position read from encoder
	std::vector<float> current_pos_;
	std::vector<float> current_vel_;
	std::vector<float> current_torq_;
    public:
	MotorJoint();//do not use this default constructor
	MotorJoint(RobotArm* root);
	
	/*
	 * initialize the robot
	 * home: the reference position. in degree
	 */
	void init(std::vector<float> home);
	
	//calculate and send the command through communication interface
	void update();
	
	//release each motor. set the output torque of each joint to zero
	void release();
	
	//halt each motor. the motor should stop at its current position immediately
	void halt();
	
	//release resources, do garbage collection. call when exit the program
	void quit();
	
	/*
	 * position control, velocity control, or torque control of the motor
	 * mode: p=position control
	 * 	 v=velocity control
	 * 	 t=torque control
	 */
	void setControlMode(char mode);
	
	/*
	 * set target position for each joint
	 * pos: target position for each joint. in degree
	 * ff_vel: feedforward velocity for each joint. in degree/sec
	 * ff_torq: feedforward torque for each joint. in mN
	 */
	void setTargetPosition(std::vector<float> pos, std::vector<float> ff_vel, std::vector<float> ff_torq);
	
	/*
	 * set target velocity for each joint
	 * vel: target velocity for each joint. in degree/sec
	 * ff_torq: feedforward torque for each joint.  in mN
	 */
	void setTargetVelocity(std::vector<float> vel, std::vector<float> ff_torq);
	
	/*
	 * set target torque for each joint
	 * torq: target torque for each joint.  in mN
	 */
	void setTargetTorque(std::vector<float> torq);
	
	//get current position of each joint. in degree
	std::vector<float> getCurrentPosition();
	
	//get current velocity of each joint. in degree/sec
	std::vector<float> getCurrentVelocity();
	
	//get current torque of each joint.  in mN
	std::vector<float> getCurrentTorque();

    };
};

#endif