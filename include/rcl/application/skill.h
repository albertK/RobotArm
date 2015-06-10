#ifndef SKILL
#define SKILL

#include "rcl/common/robot_arm.h"

//Ref http://stackoverflow.com/questions/2133250/does-not-name-a-type-error-in-c
class RobotArm;

namespace rcl
{
    class Skill
    {
    protected:
	RobotArm* root_;
    public:
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init(RobotArm* root);
	virtual void quit();
    };
};

#endif