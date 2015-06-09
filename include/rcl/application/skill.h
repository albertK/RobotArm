#ifndef SKILL
#define SKILL

#include "rcl/common/robot_arm.h"

class RobotArm;

namespace rcl
{
    class Skill
    {
    protected:
	RobotArm* root;
    public:
	Skill();//do not use this default constructor
	Skill(RobotArm* root);
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init();
	virtual void quit();
    };
};

#endif