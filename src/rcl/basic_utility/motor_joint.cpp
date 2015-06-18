#include "rcl/basic_utility/motor_joint.h"
#include "rcl/common/parameters.h"

rcl::MotorJoint::MotorJoint(rcl::RobotArm* root)
{
    root_ = root;
}

void rcl::MotorJoint::init()
{
    dof_ = rcl::Parameters::Common::dof;
    
    home_.resize(dof_);
    
    target_pos_.resize(dof_);
    target_vel_.resize(dof_);
    target_torq_.resize(dof_);
    
    current_pos_.resize(dof_);
    current_vel_.resize(dof_);
    current_torq_.resize(dof_);
    
    accumulator_.resize(dof_);
    
    reduction_ratio_.resize(dof_);
    
    for(unsigned int i = 0; i < dof_; ++i)
    {
	home_.at(i) = rcl::Parameters::MotorJoint::home[i];
	
	target_pos_.at(i) = home_.at(i);
	target_vel_.at(i) = home_.at(i);
	target_torq_.at(i) = home_.at(i);
	
	current_pos_.at(i) = home_.at(i);
	current_vel_.at(i) = home_.at(i);
	current_torq_.at(i) = home_.at(i);
	
	accumulator_.at(i) = 0.0;
	
	int reduction = rcl::Parameters::MotorJoint::enc_count[i] * rcl::Parameters::MotorJoint::gear_ratio[i];
	reduction_ratio_.at(i) = 360.0 / ((float) reduction);
    }
}

void rcl::MotorJoint::update()
{
    switch(mode_)
    {
	case 'p':
	    /*
	     * generate motor command
	     */
	    //position error
	    //joint space to motor space
	    //P gain
	    //I gain
	    //feedforward
	    //rotation direction
	    //send motor command
	    
	    /*
	     * update motor state
	     */
	    //motor space to joint space
	    //relative to the initial home pose
	    //update
	    break;
	case 'v':
	    break;
	case 't':
	    break;
    }
}

void rcl::MotorJoint::quit()
{
    halt();
}

void rcl::MotorJoint::halt()
{
    mode_ = 'p';
    
    for(unsigned int i = 0; i < dof_; ++i)
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
    for(unsigned int i = 0; i < dof_; ++i)
    {
	target_pos_.at(i) = pos.at(i);
	target_torq_.at(i) = ff_torq.at(i);
    }
}

void rcl::MotorJoint::setTargetVelocity(std::vector< float > vel, std::vector< float > ff_torq)
{
    for(unsigned int i = 0; i < dof_; ++i)
    {
	target_vel_.at(i) = vel.at(i);
	target_torq_.at(i) = ff_torq.at(i);
    }
}

void rcl::MotorJoint::setTargetTorque(std::vector< float > torq)
{
    for(unsigned int i = 0; i < dof_; ++i)
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

