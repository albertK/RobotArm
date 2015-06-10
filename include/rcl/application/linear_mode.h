#ifndef LINEARMODE
#define LINEARMODE

#include "rcl/application/skill.h"

namespace rcl
{
    class LinearMode : public Skill
    {
    protected:
	
    public:
	//inherited member functions from the class Skill.
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init(RobotArm* root);
	virtual void quit();
    };
};

#endif