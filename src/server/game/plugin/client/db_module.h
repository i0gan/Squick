

#ifndef SQUICK_GAME_SERVER_TO_DB_MODULE_H
#define SQUICK_GAME_SERVER_TO_DB_MODULE_H

#include "squick/struct/struct.h"
#include "squick/base/net.h"
#include "squick/base/net_client.h"
#include "squick/base/kernel.h"
#include "squick/base/net.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/log.h"


#include "if_db_module.h"
#include "../server/if_server_module.h"

class GameServerToDBModule : public IGameServerToDBModule
{
public:
	GameServerToDBModule(IPluginManager* p)
    {
        pPluginManager = p;
		mLastReportTime = 0;
    }
    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

    virtual void TransmitToDB(const int nHashKey, const int msgID, const google::protobuf::Message& xData);

protected:

    void OnSocketWSEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

protected:
    void TransPBToProxy(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

	INT64 mLastReportTime;

    ILogModule* m_pLogModule;
    IKernelModule* m_pKernelModule;
    IClassModule* m_pClassModule;
    IElementModule* m_pElementModule;
	INetClientModule* m_pNetClientModule;
    IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
};

#endif