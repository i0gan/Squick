
#ifndef SQUICK_LOGINNET_SERVER_MODULE_H
#define SQUICK_LOGINNET_SERVER_MODULE_H

#include "squick/core/map.h"
#include "squick/struct/struct.h"
#include "squick/base/kernel.h"
#include "squick/base/log.h"
#include "squick/base/net.h"
#include "squick/base/element.h"
#include "squick/base/class.h"

#include "squick/base/thread_pool.h"
#include "squick/base/plugin_manager.h"

#include "if_server_module.h"
#include "../logic/if_logic_module.h"
#include "../client/if_master_module.h"


class LILoginNet_ServerModule
    : public ILoginNet_ServerModule
{
public:
    LILoginNet_ServerModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Update();


    virtual bool BeforeShut();
    virtual bool AfterInit();

    virtual void LogReceive(const char* str) {}
    virtual void LogSend(const char* str) {}

    virtual int OnSelectWorldResultsProcess(const int nWorldID, const Guid xSenderID, const int nLoginID, const std::string& account, const std::string& strWorldIP, const int nWorldPort, const std::string& strKey);

protected:
    void OnSocketClientEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

protected:
    void OnClientDisconnect(const SQUICK_SOCKET nAddress);
    void OnClientConnected(const SQUICK_SOCKET nAddress);

    void OnLoginProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnSelectWorldProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void OnViewWorldProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnHeartBeat(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnLogOut(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void InvalidMessage(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:

protected:
    void SynWorldToClient(const SQUICK_SOCKET nFD);

    MapEx<Guid, SQUICK_SOCKET> mxClientIdent;

private:

	INetModule* m_pNetModule;
	INetClientModule* m_pNetClientModule;
    IClassModule* m_pClassModule;
    IElementModule* m_pElementModule;
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
	ILoginToMasterModule* m_pLoginToMasterModule;
    IThreadPoolModule* m_pThreadPoolModule;
};

#endif