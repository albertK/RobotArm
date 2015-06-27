#ifndef JOINTMODE
#define JOINTMODE

#include <vector>
#include <queue>

#include "ReflexxesAPI.h"
#include "RMLPositionFlags.h"
#include "RMLPositionInputParameters.h"
#include "RMLPositionOutputParameters.h"

#include "rcl/application/skill.h"
#include "rcl/common/parameters.h"

namespace rcl
{
    class JointMode : public Skill
    {
    protected:
	//the commanded target queue. first in first out. pop only when the target is reached
	std::queue<std::vector<float> > targets_;
	
	//the current target that the robot is heading to.
	std::vector<float> current_target_;
	
	//to see if the robot have reached the last target
	bool target_reached_;
	
	float speed_ratio_;
	float via_speed_ratio_;
	
	/*
	 * operation mode
	 * 2: moving
	 * 1: start
	 * 0: stop or pause
	 */
	short op_mode_;
	
	//Reflexxes OTG
	ReflexxesAPI* RML_;//need initialization
	RMLPositionInputParameters* IP_;//need initialization
	RMLPositionOutputParameters* OP_;//need initialization
	RMLPositionFlags Flags_;
	int OTG_result_;
	
    public:
	//inherited member functions from the class Skill.
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init();
	virtual void quit();
	
	//the robot start the motion only after the call of this function
	void startMotion();
	
	//the robot pause its motion once this function is called. the commanded targets will NOT be cleaned. call startMotion() again if the user want to resume the motion.
	void pauseMotion();
	
	//the robot stop its motion immediately and stay still once this function is called. any commanded targets will be cleaned.
	void stopMotion();
	
	//check if the target is out of bound. true outside, false inside
	bool isTargetOutOfBound(std::vector<float> target);
	
	//push and append the absolute taget in a queue
	bool pushTargetAbs(std::vector<float> target, std::vector<bool> mask);
	
	//push and append the relative target in a queue
	bool pushTargetRel(std::vector<float> target, std::vector<bool> mask);
	
	//clean the target queue and set current absolute target
	bool resetTargetAbs(std::vector<float> target, std::vector<bool> mask);
	
	//clean the target queue and set current relative target
	bool resetTargetRel(std::vector<float> target, std::vector<bool> mask);
	
	//check if the robot arm have reached the final target. used to determine to end of the motion
	bool isTargetReached();
	
	//get the current target that the robot arm is heading to
	std::vector<float> getCurrentTarget();
	
	//get all the commanded target queue
	std::vector<std::vector<float> > getAllTargets();
	
	//set the maximum speed of each joint
	void setSpeedRatio(float ratio = rcl::Parameters::JointMode::default_speed_ratio);
	
	//set the maximum speed of each joint
	void setViaSpeedRatio(float ratio = rcl::Parameters::JointMode::default_via_speed_ratio);
    };
    
    JointMode joint_mode;
};

#endif