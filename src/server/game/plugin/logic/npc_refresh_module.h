


#ifndef SQUICK_NPC_REFRESH_MODULE_H
#define SQUICK_NPC_REFRESH_MODULE_H

#include "squick/base/kernel.h"

#include "squick/base/element.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/log.h"
#include "squick/base/common_config.h"
#include "squick/base/event.h"
#include "squick/base/schedule.h"
#include "squick/base/event.h"

#include "squick/base/scene.h"


#include "if_npc_refresh_module.h"
#include "if_property_module.h"
#include "if_scene_process_module.h"
class NPCRefreshModule
    : public INPCRefreshModule
{
public:
    NPCRefreshModule( IPluginManager* p )
    {
        pPluginManager = p;
    }
    virtual ~NPCRefreshModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

protected:
    int OnObjectClassEvent( const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var );

    int OnObjectHPEvent( const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const INT64 reason);

	int OnNPCDeadDestroyHeart(const Guid& self, const std::string& heartBeat, const float time, const int count);
	int OnBuildingDeadDestroyHeart( const Guid& self, const std::string& heartBeat, const float time, const int count);

protected:
	int OnObjectBeKilled( const Guid& self, const Guid& killer );

private:
	IEventModule* m_pEventModule;
	IScheduleModule* m_pScheduleModule;
    IElementModule* m_pElementModule;
    IKernelModule* m_pKernelModule;
    ISceneProcessModule* m_pSceneProcessModule;
	ILogModule* m_pLogModule;
	IPropertyModule* m_pPropertyModule;
    ISceneModule* m_pSceneModule;
};


#endif
