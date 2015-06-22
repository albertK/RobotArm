#include "rcl/basic_utility/motor_joint.h"
#include "rcl/common/parameters.h"
#include <../../LuoLitaArm/RobotLita.h>

using namespace rcl::Parameters::Common;
using namespace rcl::Parameters::MotorJoint;

rcl::MotorJoint::MotorJoint(rcl::RobotArm* root)
{
    root_ = root;
}

void rcl::MotorJoint::init()
{
    mode_ = 'p';
    
    target_pos_.resize(dof);
    target_vel_.resize(dof);
    target_torq_.resize(dof);
    
    current_pos_.resize(dof);
    current_vel_.resize(dof);
    current_torq_.resize(dof);
    
    accumulator_.resize(dof);
    diff_.resize(dof);
    
    for(unsigned int i = 0; i < dof; ++i)
    {
	target_pos_.at(i) = home[i];
	target_vel_.at(i) = home[i];
	target_torq_.at(i) = home[i];
	
	current_pos_.at(i) = home[i];
	current_vel_.at(i) = home[i];
	current_torq_.at(i) = home[i];
	
	accumulator_.at(i) = 0.0;
	diff_.at(i) = 0.0;
    }
}

void rcl::MotorJoint::update()
{
    //update motor state
    std::vector<float> pos_buff(dof, 0.0);
    std::vector<float> vel_buff(dof, 0.0);
    
    for(unsigned int i = 0; i < dof; ++i)
    {
	pos_buff.at(i) = root_->encoder.getCount() * deg_per_count[i] - home[i];
	vel_buff.at(i) = (pos_buff.at(i) - current_pos_.at(i)) / sampling_time;
	current_acc_.at(i) = (vel_buff.at(i) - current_vel_.at(i)) / sampling_time;
	current_vel_.at(i) = vel_buff.at(i);
	current_pos_.at(i) = pos_buff.at(i);
	current_torq_.at(i) = target_torq_.at(i);
    }

    //calculate the motor torque command
    std::vector<float> command(dof, 0.0);
    switch(mode_)
    {
	case 'p':
	{
	    //calculate the enc error
	    std::vector<float> enc_pos_error(dof, 0.0);
	    for(unsigned int i = 0; i < dof; ++i)
	    {
		enc_pos_error.at(i) = floor((target_pos_.at(i) - current_pos_.at(i)) * count_per_deg);
	    }

	    //calculate the PID gain
	    std::vector<float> P(dof, 0.0);
	    std::vector<float> I(dof, 0.0);
	    std::vector<float> D(dof, 0.0);
	    for(unsigned int i = 0; i < dof; ++i)
	    {
		//P gain
		P.at(i) = position_PID_P[i] * enc_pos_error.at(i);
		
		//I gain
		accumulator_.at(i) += enc_pos_error.at(i);
		if(accumulator_.at(i) > accu_max[i])
		    accumulator_.at(i) = accu_max[i];
		else if(accumulator_.at(i) < -accu_max[i])
		    accumulator_.at(i) = -accu_max[i];
		
		I.at(i) = position_PID_P[i] * position_PID_I2P[i] * accumulator_.at(i);
		
		//D gain
		D.at(i) = position_PID_P[i] * position_PID_D2P[i] * (enc_pos_error.at(i) - diff_.at(i));
		diff_.at(i) = enc_pos_error.at(i);
	    }
	    
	    //final motor torque command, including the torque feedforward
	    for(unsigned int i = 0; i < dof; ++i)
	    {
		command.at(i) = P.at(i) + I.at(i), D.at(i) + target_torq_.at(i);
	    }
	    break;
	}
	case 'v':
	    break;
	case 't':
	    for(unsigned int i = 0; i < dof; ++i)
	    {
		command.at(i) = target_torq_.at(i);
	    }
	    break;
    }
    
    //rotation direction
    //send the motor torque command
}

void rcl::MotorJoint::quit()
{
    halt();
}

void rcl::MotorJoint::halt()
{
    mode_ = 'p';
    
    for(unsigned int i = 0; i < dof; ++i)
    {
	target_pos_.at(i) = current_pos_.at(i);
	target_vel_.at(i) = 0;
    }
    
    update();
}

void rcl::MotorJoint::setControlMode(char mode)
{
    mode_ = mode;
}

void rcl::MotorJoint::setTargetPosition(std::vector< float > pos, std::vector< float > ff_torq)
{
    for(unsigned int i = 0; i < dof; ++i)
    {
	target_pos_.at(i) = pos.at(i);
	target_torq_.at(i) = ff_torq.at(i);
    }
}

void rcl::MotorJoint::setTargetVelocity(std::vector< float > vel, std::vector< float > ff_torq)
{
    for(unsigned int i = 0; i < dof; ++i)
    {
	target_vel_.at(i) = vel.at(i);
	target_torq_.at(i) = ff_torq.at(i);
    }
}

void rcl::MotorJoint::setTargetTorque(std::vector< float > torq)
{
    for(unsigned int i = 0; i < dof; ++i)
    {
	target_torq_.at(i) = torq.at(i);
    }
}


std::vector< float > rcl::MotorJoint::getCurrentPosition()
{
    return current_pos_;
}

std::vector< float > rcl::MotorJoint::getCurrentVelocity()
{
    return current_vel_;
}

std::vector< float > rcl::MotorJoint::getCurrentTorque()
{
    return current_torq_;
}

