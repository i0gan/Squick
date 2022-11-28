#pragma once

#include <squick/core/consistent_hash.h>
#include <squick/plugin/kernel/i_kernel_module.h>
#include <squick/plugin/no_sql/i_no_sql_module.h>

#include <squick/plugin/net/i_net_client_module.h>
#include <squick/plugin/kernel/i_schedule_module.h>
#include <squick/plugin/kernel/i_scene_module.h>
#include <squick/plugin/kernel/i_event_module.h>
#include <squick/plugin/kernel/i_data_tail_module.h>

#include <squick/plugin/config/i_element_module.h>

#include "i_scene_process_module.h"
#include "i_create_role_module.h"
#include "../server/i_server_module.h"
#include "../client/i_db_module.h"

class CreateRoleModule
    : public ICreateRoleModule
{
public:
    CreateRoleModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~CreateRoleModule() {};

    virtual bool Start();
    virtual bool Destory();
	virtual bool ReadyUpdate();
    virtual bool Update();
    virtual bool AfterStart();

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