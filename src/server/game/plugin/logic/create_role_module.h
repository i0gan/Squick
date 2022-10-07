

#ifndef SQUICK_CREATEROLE_MODULE_H
#define SQUICK_CREATEROLE_MODULE_H

#include "squick/core/consistent_hash.h"
#include "squick/base/kernel.h"
#include "squick/base/no_sql.h"
#include "squick/base/element.h"

#include "squick/base/schedule.h"
#include "squick/base/data_tail.h"
#include "squick/base/scene.h"
#include "squick/base/event.h"


#include "if_scene_process_module.h"
#include "if_create_role_module.h"
#include "../server/if_server_module.h"
#include "../client/if_db_module.h"

class NFCreateRoleModule
    : public ICreateRoleModule
{
public:
    NFCreateRoleModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~NFCreateRoleModule() {};

    virtual bool Init();
    virtual bool Shut();
	virtual bool ReadyExecute();
    virtual bool Execute();
    virtual bool AfterInit();

	virtual void SetDefaultSceneID(const int sceneID);

protected:
	void OnRequireRoleListProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnResponseRoleListProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	
	void OnCreateRoleGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnDeleteRoleGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientEnterGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	
	void OnDBLoadRoleDataProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

	int OnObjectPlayerEvent(const Guid & self, const std::string & className, const CLASS_OBJECT_EVENT classEvent, const DataList & var);


private:

	void AttachData(const Guid& self);
	void SaveData(const Guid& self);

	int SaveDataOnTime(const Guid& self, const std::string& name, const float fIntervalTime, const int count);

private:

	int defaultSceneID = 1;
	std::map<Guid, SquickStruct::RoleDataPack> mxObjectDataCache;

private:
	INetModule* m_pNetModule;
	IClassModule* m_pClassModule;
	IElementModule* m_pElementModule;
	IKernelModule* m_pKernelModule;
	ISceneModule* m_pSceneModule;
	IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
	IGameServerToDBModule* m_pGameToDBModule;
	ISceneProcessModule* m_pSceneProcessModule;
	INetClientModule* m_pNetClientModule;
	IScheduleModule* m_pScheduleModule;
	IDataTailModule* m_pDataTailModule;
	IEventModule* m_pEventModule;
};

#endif