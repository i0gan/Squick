

#ifndef SQUICK_PROXYSERVER_NETCLIENT_MODULE_H
#define SQUICK_PROXYSERVER_NETCLIENT_MODULE_H

#include "squick/struct/struct.h"

#include "squick/base/kernel.h"

#include "squick/base/net.h"
#include "squick/base/element.h"
#include "squick/base/log.h"
#include "squick/base/class.h"
#include "squick/base/net_client.h"
#include "squick/base/security.h"

#include "if_game_module.h"
#include "if_world_module.h"
#include "../server/if_server_module.h"
#include "../logic/if_logic_module.h"

class ProxyServerToWorldModule : public IProxyServerToWorldModule
{
public:

    ProxyServerToWorldModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
		mLastReportTime = 0;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();

    virtual void LogReceive(const char* str) {}
    virtual void LogSend(const char* str) {}

	virtual INetClientModule* GetClusterModule();
    virtual bool VerifyConnectData(const std::string& account, const std::string& strKey);

protected:

    void OnSocketWSEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

    void Register(INet* pNet);
	void ServerReport();

    void OnSelectServerResultProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnServerInfoProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

    void LogServerInfo(const std::string& strServerInfo);

	void OnOtherMessage(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
private:
    struct ClientConnectData
    {
        ClientConnectData()
        {
            account = "";
            strConnectKey = "";
        }

        std::string account;
        std::string strConnectKey;
    };


    MapEx<std::string, ClientConnectData> mWantToConnectMap;

private:
	INT64 mLastReportTime;

    ILogModule* m_pLogModule;
    IProxyLogicModule* m_pProxyLogicModule;
    IKernelModule* m_pKernelModule;
    IProxyServerNet_ServerModule* m_pProxyServerNet_ServerModule;
    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
	INetClientModule* m_pNetClientModule;
	ISecurityModule* m_pSecurityModule;

};

#endif