#pragma once

#include <memory>
#include "squick/struct/struct.h"
#include "squick/base/net.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/event.h"
#include "squick/base/scene.h"
#include "squick/base/schedule.h"
#include "squick/base/thread_pool.h"
#include "squick/base/module.h"

#include "if_server_module.h"
#include "../logic/if_scene_process_module.h"
#include "../logic/if_sync_pos_module.h"
#include "../client/if_world_module.h"
////////////////////////////////////////////////////////////////////////////



class GameServerNet_ServerModule
    : public IGameServerNet_ServerModule
{
public:
    GameServerNet_ServerModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

    virtual void SendMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const Guid& self);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const int sceneID, const int groupID);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const int sceneID, const int groupID, const Guid exceptID);

	virtual void SendMsgToGate(const uint16_t msgID, const std::string& msg, const Guid& self);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, const std::string& msg, const int sceneID, const int groupID);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, const std::string& msg, const int sceneID, const int groupID, const Guid exceptID);

    virtual bool AddPlayerGateInfo(const Guid& roleID, const Guid& clientID, const int gateID);
    virtual bool RemovePlayerGateInfo(const Guid& roleID);
    virtual SQUICK_SHARE_PTR<GateBaseInfo> GetPlayerGateInfo(const Guid& roleID);

    virtual SQUICK_SHARE_PTR<GateServerInfo> GetGateServerInfo(const int gateID);
    virtual SQUICK_SHARE_PTR<GateServerInfo> GetGateServerInfoBySockIndex(const SQUICK_SOCKET sockIndex);


protected:
    void OnSocketPSEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);
    void OnClientDisconnect(const SQUICK_SOCKET sockIndex);
    void OnClientConnected(const SQUICK_SOCKET sockIndex);

protected:
    void OnProxyServerRegisteredProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnProxyServerUnRegisteredProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnRefreshProxyServerInfoProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:
    void OnClientLeaveGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char *msg, const uint32_t len);
	void OnClientSwapSceneProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char *msg, const uint32_t len);
	void OnClientReqMoveProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char *msg, const uint32_t len);
	void OnClientEnterGameFinishProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char *msg, const uint32_t len);

	void OnLagTestProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

    ///////////WORLD_START///////////////////////////////////////////////////////////////
    void OnTransWorld(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

private:
    
    MapEx<Guid, GateBaseInfo> mRoleBaseData;

    //gateid,data
    MapEx<int, GateServerInfo> mProxyMap;

    //////////////////////////////////////////////////////////////////////////
	ISyncPosModule* m_pSyncPosModule;
	IKernelModule* m_pKernelModule;
    IClassModule* m_pClassModule;
    ILogModule* m_pLogModule;
    ISceneProcessModule* m_pSceneProcessModule;
    IElementModule* m_pElementModule;
	INetModule* m_pNetModule;
	IEventModule* m_pEventModule;
	ISceneModule* m_pSceneModule;
	INetClientModule* m_pNetClientModule;
	IScheduleModule* m_pScheduleModule;
    IThreadPoolModule* m_pThreadPoolModule;
};

