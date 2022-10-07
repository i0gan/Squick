


#ifndef SQUICK_SYNC_MODULE_H
#define SQUICK_SYNC_MODULE_H

#include "squick/base/plugin_manager.h"
#include "squick/base/schedule.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/kernel.h"

#include "squick/base/scene.h"
#include "squick/base/class.h"
#include "squick/base/log.h"

#include "if_sync_pos_module.h"
#include "../server/if_server_module.h"
class SyncPosModule
    : public ISyncPosModule
{
public:
	SyncPosModule(IPluginManager* p)
	{
		pPluginManager = p;
		m_bIsExecute = true;
	}

	virtual ~SyncPosModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

    virtual bool RequireMove(const Guid scene_group, const PosSyncUnit& syncUnit) override;

protected:

	int OnNPCClassEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);
	int OnNPCGMPositionEvent(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar);

	int OnPlayerClassEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);
	int OnPlayerGMPositionEvent(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const INT64 reason);

private:

private:
	IScheduleModule* m_pScheduleModule;
	INetModule* m_pNetModule;
	IClassModule* m_pClassModule;
	ILogModule* m_pLogModule;
	IKernelModule* m_pKernelModule;
	IElementModule* m_pElementModule;
	ISceneModule* m_pSceneModule;
	IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
};


#endif
