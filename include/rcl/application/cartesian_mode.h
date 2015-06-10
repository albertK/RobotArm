#ifndef CARTESIANMODE
#define CARTESIANMODE

#include <eigen3/Eigen/Dense>

#include "rcl/application/skill.h"

namespace rcl
{
    class CartesianMode : public Skill
    {
    protected:
	//the commanded target queue. first in first out
	std::queue<Eigen::Matrix4f> targets_;
	
	//the current target that the robot is heading to
	Eigen::Matrix4f current_target_;
	
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
	
	//the robot pause its motion once this function is called. the commanded targets will NOT be cleaned. call startMotion() again if the user want to resume the motion.
	void pauseMotion();
	
	//the robot stop its motion immediately and stay still once this function is called. any commanded targets will be cleaned.
	void stopMotion();
	
	//push and append the absolute taget in a queue
	bool pushTargetAbs(Eigen::Matrix4f target);
	
	//push and append the relative target in a queue
	bool pushTargetRel(Eigen::Matrix4f target);
	
	//clean the target queue and set current absolute target
	bool resetTargetAbs(Eigen::Matrix4f target);
	
	//clean the target queue and set current relative target
	bool resetTargetRel(Eigen::Matrix4f target);
	
	//check if the robot arm have reached the final target. used to determine to end of the motion
	bool isTargetReached();
	
	//get the current target that the robot arm is heading to
	Eigen::Matrix4f getCurrentTarget();
	
	//get all the commanded target queue
	std::vector<Eigen::Matrix4f> getAllTargets();
	
	//set the maximum speed of each joint
	void setSpeedRatio(float ratio = 0.5);
    };
};

#endif