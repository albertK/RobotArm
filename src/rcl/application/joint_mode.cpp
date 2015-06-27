#include "rcl/application/joint_mode.h"
#include "rcl/common/parameters.h"
#include "rcl/basic_utility/robot_states.h"
#include "rcl/basic_utility/motor_joint.h"


using namespace rcl::Parameters::Common;
using namespace rcl::Parameters::JointMode;

void rcl::JointMode::init()
{
    speed_ratio_ = default_speed_ratio;
    
    motor_joint.setControlMode('p');
    
    RML_ = new ReflexxesAPI(dof, sampling_time);
    IP_ = new RMLPositionInputParameters(dof);
    for(unsigned int i = 0; i < dof; ++i)
    {
	IP_->MaxAccelerationVector->VecData[i] = max_acc[i];
	IP_->SelectionVector->VecData[i] = true;
    }
    
    OP_ = new RMLPositionOutputParameters(dof);
    Flags_.SynchronizationBehavior = RMLPositionFlags::PHASE_SYNCHRONIZATION_IF_POSSIBLE;
    OTG_result_ = 0;
}

void rcl::JointMode::updateSkill()
{
    std::vector<float> next_cycle_target_pos(dof, 0.0);//in degree
    switch(op_mode_)
    {
	case 2://moving
	{
	    if(OTG_result_ != ReflexxesAPI::RML_FINAL_STATE_REACHED)//not yet reach the current_target_
	    {
		for(unsigned int i = 0; i < dof; ++i)
		{
		    IP_->TargetPositionVector->VecData[i] = current_target_.at(i);
		    if(targets_.size() > 1)
		    {
			IP_->TargetVelocityVector->VecData[i] = speed_ratio_ * via_speed_ratio_ * max_vel[i];
		    }
		    else
		    {
			IP_->TargetVelocityVector->VecData[i] = 0.0;
		    }
		}
		
		OTG_result_ = RML_->RMLPosition(*IP_, OP_, Flags_);
		
		for(unsigned int i = 0; i < dof; ++i)
		{
		    next_cycle_target_pos.at(i) = OP_->NewPositionVector->VecData[i];
		}
		
		*IP_->CurrentPositionVector = *OP_->NewPositionVector;
		*IP_->CurrentVelocityVector = *OP_->NewVelocityVector;
	    }
	    else//already reach the current_target_
	    {
		targets_.pop();
		if(targets_.size() > 0)//go to the next target
		{
		    current_target_ = targets_.front();
		    for(unsigned int i = 0; i < dof; ++i)
		    {
			IP_->TargetPositionVector->VecData[i] = current_target_.at(i);
			if(targets_.size() > 1)
			{
			    IP_->TargetVelocityVector->VecData[i] = speed_ratio_ * via_speed_ratio_ * max_vel[i];
			}
			else
			{
			    IP_->TargetVelocityVector->VecData[i] = 0.0;
			}
		    }
		    
		    OTG_result_ = RML_->RMLPosition(*IP_, OP_, Flags_);
		    
		    for(unsigned int i = 0; i < dof; ++i)
		    {
			next_cycle_target_pos.at(i) = OP_->NewPositionVector->VecData[i];
		    }
		    
		    *IP_->CurrentPositionVector = *OP_->NewPositionVector;
		    *IP_->CurrentVelocityVector = *OP_->NewVelocityVector;
		}
		else//already reached the final target
		{
		    next_cycle_target_pos = current_target_;
		    target_reached_ = true;
		    op_mode_ = 0;
		}
	    }
	    
	    break;
	}
	case 1://start
	{
	    for(unsigned int i = 0; i < dof; ++i)
	    {
		std::vector<float> current_joint_pos = robot_states.getCurrentJointPosition();
		IP_->CurrentPositionVector->VecData[i] = current_joint_pos.at(i);
		IP_->CurrentVelocityVector->VecData[i] = 0.0;
		
		IP_->TargetPositionVector->VecData[i] = current_target_.at(i);
		if(targets_.size() > 1)
		{
		    IP_->TargetVelocityVector->VecData[i] = via_speed_ratio_ * speed_ratio_ * max_vel[i];
		}
		else
		{
		    IP_->TargetVelocityVector->VecData[i] = 0.0;
		}
	    }
	    
	    OTG_result_ = RML_->RMLPosition(*IP_, OP_, Flags_);
	    
	    for(unsigned int i = 0; i < dof; ++i)
	    {
		next_cycle_target_pos.at(i) = OP_->NewPositionVector->VecData[i];
	    }
	    
	    *IP_->CurrentPositionVector = *OP_->NewPositionVector;
	    *IP_->CurrentVelocityVector = *OP_->NewVelocityVector;
	    
	    op_mode_ = 2;
	    break;
	}
	case 0://stop or pause
	{
	    next_cycle_target_pos = current_target_;
	    break;
	}
    }
    
    //TODO add gravity compensation
    motor_joint.setTargetPosition(next_cycle_target_pos, std::vector<float>(dof, 0.0));
}

void rcl::JointMode::startMotion()
{
    op_mode_ = 1;
    target_reached_ = false;
    
    current_target_ = targets_.front();
}

void rcl::JointMode::pauseMotion()
{
    op_mode_ = 0;
    target_reached_ = false;
    
    current_target_ = robot_states.getCurrentJointPosition();
}

void rcl::JointMode::stopMotion()
{
    op_mode_ = 0;
    target_reached_ = true;
    
    //clear the targets queue
    std::queue<int> empty_queue;
    std::swap(targets_, empty_queue);
    
    current_target_ = robot_states.getCurrentJointPosition();
}

bool rcl::JointMode::isTargetReached()
{
    return target_reached_;
}

bool isTargetOutOfBound(std::vector<float> target)
{
    bool out_of_bound = false;
    for(unsigned int i = 0; i < dof; ++i)
	if(target.at(i) > joint_limit_upper[i] || target.at(i) < joint_limit_lower[i])
	    out_of_bound = true;
	
    return out_of_bound;
}

bool rcl::JointMode::pushTargetAbs(std::vector< float > target, std::vector< bool > mask)
{
    std::vector<float> masked_target = target;
    std::vector<float> current_joint_pos = robot_states.getCurrentJointPosition();
    
    for(unsigned int i = 0; i < mask.size(); ++i)
	if(!mask.at(i))
	    masked_target.at(i) = current_joint_pos.at(i);
	
    if(isTargetOutOfBound(masked_target))
    {
	return false;
    }
    else
    {
	targets_.push(masked_target);
	return true;
    }
}

bool rcl::JointMode::pushTargetRel(std::vector< float > target, std::vector< bool > mask)
{
    std::vector<float> masked_target = target;
    std::vector<float> current_joint_pos = robot_states.getCurrentJointPosition();
    
    for(unsigned int i = 0; i < mask.size(); ++i)
    {
	if(!mask.at(i))
	    masked_target.at(i) = current_joint_pos.at(i);
	else
	    masked_target.at(i) += current_joint_pos.at(i);
    }
    
    if(isTargetOutOfBound(masked_target))
    {
	return false;
    }
    else
    {
	targets_.push(masked_target);
	return true;
    }
}

bool rcl::JointMode::resetTargetAbs(std::vector< float > target, std::vector< bool > mask)
{
    //clear the targets queue
    std::queue<int> empty_queue;
    std::swap(targets_, empty_queue);
    
    std::vector<float> masked_target = target;
    std::vector<float> current_joint_pos = robot_states.getCurrentJointPosition();
    
    for(unsigned int i = 0; i < mask.size(); ++i)
	if(!mask.at(i))
	    masked_target.at(i) = current_joint_pos.at(i);
	
    if(isTargetOutOfBound(masked_target))
    {
	current_target_ = current_joint_pos;
	return false;
    }
    else
    {
	current_target_ = masked_target;
	return true;
    }
}

bool rcl::JointMode::resetTargetRel(std::vector< float > target, std::vector< bool > mask)
{
    //clear the targets queue
    std::queue<int> empty_queue;
    std::swap(targets_, empty_queue);
    
    std::vector<float> masked_target = target;
    std::vector<float> current_joint_pos = robot_states.getCurrentJointPosition();
    
    for(unsigned int i = 0; i < mask.size(); ++i)
    {
	if(!mask.at(i))
	    masked_target.at(i) = current_joint_pos.at(i);
	else
	    masked_target.at(i) += current_joint_pos.at(i);
    }
    
    if(isTargetOutOfBound(masked_target))
    {
	current_target_ = current_joint_pos;
	return false;
    }
    else
    {
	current_target_ = masked_target;
	return true;
    }
}

std::vector< float > rcl::JointMode::getCurrentTarget()
{
    return current_target_;
}

std::vector< std::vector< float > > rcl::JointMode::getAllTargets()
{
    std::queue< std::vector<float> > targets_copy = targets_;
    std::vector< std::vector<float> > return_targets;
    return_targets.resize(targets_copy.size());
    for(unsigned int i = 0; i < targets_copy.size(); ++i)
    {
	return_targets.at(i) = targets_copy.front();
	targets_copy.pop();
    }
    
    return return_targets;
}

void rcl::JointMode::setSpeedRatio(float ratio)
{
    speed_ratio_ = ratio;
    
    for(unsigned int i = 0; i < dof; ++i)
	IP_->MaxVelocityVector->VecData[i] = speed_ratio_ * max_vel[i];
}

void rcl::JointMode::setViaSpeedRatio(float ratio)
{
    via_speed_ratio_ = ratio;
}
