


#ifndef SQUICK_SKILL_CONSUME_MANAGER_MODULE_H
#define SQUICK_SKILL_CONSUME_MANAGER_MODULE_H

#include <iostream>
#include "squick/core/map_ex.h"

#include "if_skill_consume_manager_module.h"

class SkillConsumeManagerModule
    : public ISkillConsumeManagerModule
{
public:
    SkillConsumeManagerModule( IPluginManager* p )
    {
        pPluginManager = p;
    }
    virtual bool Init() override;
    virtual bool Shut() override;
    virtual bool Update() override;
    virtual bool AfterInit() override;

    virtual bool SetConsumeModule(const int skillType, ISkillConsumeProcessModule* pModule);
	virtual bool SetConsumeModule(const int skillType, const int skillSubType, ISkillConsumeProcessModule* pModule);

	virtual ISkillConsumeProcessModule* GetConsumeModule( const int skillType);
	virtual ISkillConsumeProcessModule* GetConsumeModule( const int skillType, const int skillSubType);

private:
	std::map<Guid, ISkillConsumeProcessModule*> mSkillConsumeProcess;
};

#endif
