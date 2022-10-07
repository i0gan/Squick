
#ifndef SQUICK_GAME_SERVER_TO_WORLD_MODULE_H
#define SQUICK_GAME_SERVER_TO_WORLD_MODULE_H

#include "squick/struct/struct.h"
#include "squick/base/net.h"
#include "squick/base/net_client.h"

#include "squick/base/kernel.h"
#include "squick/base/net.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/log.h"

#include "if_world_module.h"
#include "../logic/if_game_server_module.h"
#include "../server/if_server_module.h"
class GameServerToWorldModule : public IGameServerToWorldModule
{
public:
    GameServerToWorldModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
		mLastReportTime = 0;
    }
    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

    virtual void TransmitToWorld(const int nHashKey, const int msgID, const google::protobuf::Message& xData);

	virtual void SendOnline(const Guid& self);
	virtual void SendOffline(const Guid& self);

protected:

    void OnSocketWSEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

protected:
    void Register(INet* pNet);
	void ServerReport();
    void TransPBToProxy(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

    int OnObjectClassEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);
	
	void OnServerInfoProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:
	void OnWorldPropertyIntProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldPropertyFloatProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldPropertyStringProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldPropertyObjectProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldPropertyVector2Process(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldPropertyVector3Process(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnWorldRecordEnterProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char *msg, const uint32_t len);
	void OnWorldAddRowProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldRemoveRowProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldSwapRowProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldRecordIntProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldRecordFloatProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldRecordStringProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldRecordObjectProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldRecordVector2Process(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldRecordVector3Process(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
private:
	INT64 mLastReportTime;

    ILogModule* m_pLogModule;
    IKernelModule* m_pKernelModule;
    IClassModule* m_pClassModule;
    IElementModule* m_pElementModule;
	INetClientModule* m_pNetClientModule;
    IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
};

#endif