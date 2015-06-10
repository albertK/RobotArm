#ifndef INTUIVETEACH
#define INTUIVETEACH

#include "rcl/application/skill.h"
#include "rcl/application/free_mode.h"
#include "rcl/application/translation_mode.h"
#include "rcl/application/rotation_mode.h"
#include "rcl/application/linear_mode.h"
#include "rcl/application/planar_mode.h"

namespace rcl
{
    class IntuiveTeach : public Skill
    {
    protected:
    public:
	//inherited member functions from the class Skill.
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init();
	virtual void quit();
	
	changeTeachMode();
	
	Skill* skill;
	FreeMode free_mode;
	TranslationMode translation_mode;
	RotationMode rotation_mode;
	LinearMode linear_mode;
	PlanarMode planar_mode;
    };
};

#endif