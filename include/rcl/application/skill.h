#ifndef SKILL
#define SKILL

#include "rcl/common/robot_arm.h"

namespace rcl
{
    class Skill
    {
    protected:
	
    public:
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init();
	virtual void quit();
    };
};

#endif