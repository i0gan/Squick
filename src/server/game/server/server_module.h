#pragma once

#include <memory>
#include <squick/struct/struct.h>
#include <squick/plugin/net/i_net_module.h>
#include <squick/plugin/net/i_net_client_module.h>
#include <squick/plugin/log/i_log_module.h>
#include <squick/plugin/kernel/i_kernel_module.h>

#include <squick/plugin/kernel/i_event_module.h>
#include <squick/plugin/kernel/i_scene_module.h>
#include <squick/plugin/kernel/i_schedule_module.h>
#include <squick/plugin/kernel/i_thread_pool_module.h>

#include <squick/plugin/config/i_class_module.h>
#include <squick/plugin/config/i_element_module.h>

#include <squick/core/i_module.h>
#include "i_server_module.h"
#include "../scene/i_scene_process_module.h"
#include "../scene/i_sync_pos_module.h"
#include "../client/i_world_module.h"
////////////////////////////////////////////////////////////////////////////



class GameServerNet_ServerModule
    : public IGameServerNet_ServerModule
{
public:
    GameServerNet_ServerModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual bool Start();
    virtual bool Destory();
    virtual bool Update();
    virtual bool AfterStart();

    virtual void SendMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const Guid& self);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const int sceneID, const int groupID);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, google::protobuf::Message& xMsg, const int sceneID, const int groupID, const Guid exceptID);

	virtual void SendMsgToGate(const uint16_t msgID, const std::string& msg, const Guid& self);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, const std::string& msg, const int sceneID, const int groupID);
	virtual void SendGroupMsgPBToGate(const uint16_t msgID, const std::string& msg, const int sceneID, const int groupID, const Guid exceptID);

    // 发送消息到Pvp服务器，由Pvp Manager作为代理
    void SendMsgPBToPvp(const uint16_t msgID, google::protobuf::Message& xMsg, const Guid& self);
    void SendMsgToPvp(const uint16_t msgID, const std::string& msg, const Guid& self);

    // 发送消息到Pvp Manager服务器，内部实现是选择第一个注册的PVP Manager 服务器
    void SendMsgToPvpManager(const uint16_t msgID, const std::string& msg);
    void SendMsgPBToPvpManager(const uint16_t msgID, google::protobuf::Message& xMsg);

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
    // 代理服务器注册
    void OnProxyServerRegisteredProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnProxyServerUnRegisteredProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnRefreshProxyServerInfoProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

    // PVP管理服务器注册
    void OnPvpManagerServerRegisteredProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnPvpManagerServerUnRegisteredProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnRefreshPvpManagerServerInfoProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

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

    // PVP Manager 服务器连接表
    MapEx<int, GateServerInfo> mPvpManagerMap;

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

