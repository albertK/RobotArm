#ifndef FREEMODE
#define FREEMODE

#include "rcl/application/skill.h"

namespace rcl
{
    class FreeMode : public Skill
    {
    protected:
	
    public:
	//inherited member functions from the class Skill.
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init();
	virtual void quit();
    };
};

#endif