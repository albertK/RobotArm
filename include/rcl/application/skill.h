#ifndef SKILL
#define SKILL

#include "rcl/common/robot_arm.h"

namespace rcl
{
    class Skill
    {
    protected:
	RobotArm* root;
    public:
	Skill(RobotArm* root);
	virtual void startSkill() = 0;
	virtual void stopSkill() = 0;
	virtual void updateSkill() = 0;
    };
};

#endif