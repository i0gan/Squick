

#ifndef SQUICK_WORLDNET_SERVER_MODULE_H
#define SQUICK_WORLDNET_SERVER_MODULE_H

#include "squick/core/map.h"
#include "squick/struct/struct.h"
#include "squick/base/net.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/thread_pool.h"

//#include "squick/base/login_net_server.h"
#include "if_server_module.h"
#include "../logic/if_account_redis_module.h"
#include "../logic/if_player_redis_module.h"
#include "server/game/plugin/logic/if_scene_process_module.h"
#include "server/world/plugin/server/if_server_module.h"
#include "server/world/plugin/client/if_master_module.h"
//#include "server/world/plugin/logic/if_logic_module.h"


class DBNet_ServerModule
    : public IDBNet_ServerModule
{
public:
    DBNet_ServerModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

	virtual bool Awake();
    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();

protected:

    void OnSocketEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

	void OnClientDisconnect(const SQUICK_SOCKET nAddress);
	void OnClientConnected(const SQUICK_SOCKET nAddress);


	void OnRequireRoleListProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnCreateRoleGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnDeleteRoleGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnLoadRoleDataProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnSaveRoleDataProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);


protected:
	IPlayerRedisModule* m_pPlayerRedisModule;
	IAccountRedisModule* m_pAccountRedisModule;
    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
	INetModule* m_pNetModule;
	INetClientModule* m_pNetClientModule;
    IThreadPoolModule* m_pThreadPoolModule;
};

#endif
