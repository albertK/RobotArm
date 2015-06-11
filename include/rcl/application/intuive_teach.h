#ifndef INTUIVETEACH
#define INTUIVETEACH

#include <string>

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
	std::string mode_;
    public:
	//inherited member functions from the class Skill.
	virtual void startSkill();
	virtual void stopSkill();
	virtual void updateSkill();
	virtual void init(RobotArm* root);
	virtual void quit();
	
	/* change different teach mode
	 * free: free mode
	 * trans: translation mode
	 * rot: rotation mode
	 * line: linear mode
	 * plane: planar mode
	 */
	void changeTeachMode(std::string mode);
	
	Skill* skill;
	FreeMode free_mode;
	TranslationMode translation_mode;
	RotationMode rotation_mode;
	LinearMode linear_mode;
	PlanarMode planar_mode;
    };
};

#endif