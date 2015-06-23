#ifndef DEFAULTMODE
#define DEFAULTMODE

#include "rcl/application/skill.h"

namespace rcl
{
    class DefaultMode : public Skill
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