#ifndef MOTORJOINT
#define MOTORJOINT

#include <vector>

#include "rcl/hardware/encoder.h"
#include "rcl/hardware/analog_output.h"

namespace rcl
{
    class MotorJoint
    {
    protected:
	//motor control mode
	char mode_;
	
	//check if the class has been initialized. avoid multiple initialization
	bool init_;
	
	//accumulation of PID integrator
	std::vector<float> accumulator_;
	
	//last PID diff
	std::vector<float> diff_;
	
	//target position command
	std::vector<float> target_pos_;//in deg
	std::vector<float> target_vel_;//in deg/s
	std::vector<float> target_torq_;//in Nm
	
	//current position read from encoder
	std::vector<float> current_pos_;//in deg
	std::vector<float> current_vel_;//in deg/s
	std::vector<float> current_acc_;//in deg/sec^2
	std::vector<float> current_torq_;//in Nm
    public:
	MotorJoint():init_(false){};
	
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
	
	//get current acceleration of each joint. in deg/sec^2
	std::vector<float> getCurrentAcceleration();
	
	//get current torque of each joint.  in mN
	std::vector<float> getCurrentTorque();

    };
    
    static MotorJoint motor_joint;
};

#endif