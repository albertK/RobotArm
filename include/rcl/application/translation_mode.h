#ifndef TRANSLATIONMODE
#define TRANSLATIONMODE

#include "rcl/application/skill.h"

namespace rcl
{
    class TranslationMode : public Skill
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