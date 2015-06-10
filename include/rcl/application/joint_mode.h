#ifndef JOINTMODE
#define JOINTMODE

#include <vector>
#include <queue>

#include "rcl/application/skill.h"

namespace rcl
{
    class JointMode : public Skill
    {
    protected:
	//the commanded target queue. first in first out
	std::queue<std::vector<float> > targets_;
	
	//the current target that the robot is heading to
	std::vector<float> current_target_;
	
	//to see if the robot have reached the final target
	bool target_reached_;
    public:
	//inherited member functions from the class Skill.
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init(RobotArm* root);
	virtual void quit();
	
	//the robot start the motion only after the call of this function
	void startMotion();
	
	//the robot pause its motion when the call of this function. the commanded targets will not be cleaned. call startMotion() again if the user want to resume the motion.
	void pauseMotion();
	
	//the robot stop tits motion immediately and stay still afte the call of this function. any commanded targets will be cleaned.
	void stopMotion();
	
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
	void setSpeedRatio(float ratio = 0.5);
    };
};

#endif