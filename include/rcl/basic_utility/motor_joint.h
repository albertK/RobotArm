#ifndef MOTORJOINT
#define MOTORJOINT

#include <vector>

#include "rcl/common/robot_arm.h"

//Ref http://stackoverflow.com/questions/2133250/does-not-name-a-type-error-in-c
class RobotArm;

namespace rcl
{
    class MotorJoint
    {
    protected:
	RobotArm* root_;
	
	//motor control mode
	char mode_;
	
	//accumulation of PID integrator
	std::vector<float> accumulator_;
	
	//target position command
	std::vector<float> target_pos_;//in deg
	std::vector<float> target_vel_;//in deg/s
	std::vector<float> target_torq_;//TODO unit?
	
	//current position read from encoder
	std::vector<float> current_pos_;//in deg
	std::vector<float> current_vel_;//in deg/s
	std::vector<float> current_torq_;//TODO unit?
    public:
	MotorJoint(){}//do not use this default constructor
	MotorJoint(RobotArm* root);
	
	/*
	 * initialize necessary parameters
	 */
	void init();
	
	//calculate and send the command through communication interface
	void update();
	
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
	 * WARNING the programmer should check the pos and torq limit by themselves
	 * pos: target position for each joint. in degree
	 * ff_torq: feedforward torque for each joint. in mN
	 */
	void setTargetPosition(std::vector<float> pos, std::vector<float> ff_torq);
	
	/*
	 * set target velocity for each joint
	 * WARNING the programmer should check the pos, vel and torq limit by themselves
	 * vel: target velocity for each joint. in degree/sec
	 * ff_torq: feedforward torque for each joint.  in mN
	 */
	void setTargetVelocity(std::vector<float> vel, std::vector<float> ff_torq);
	
	/*
	 * set target torque for each joint
	 * WARNING the programmer should check the pos and torq limit by themselves
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