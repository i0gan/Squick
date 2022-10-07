
#ifndef SQUICK_LOGINNET_CLIENT_MODULE_H
#define SQUICK_LOGINNET_CLIENT_MODULE_H

//  the cause of sock'libariy, thenfore "Net.h" much be included first.

#include "squick/base/kernel.h"

#include "squick/base/log.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/net.h"

#include "../server/if_server_module.h"
#include "../logic/if_logic_module.h"
#include "if_master_module.h"


class LoginToMasterModule
    : public ILoginToMasterModule
{
public:
    LoginToMasterModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
		mLastReportTime = 0;
    }


    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();
    virtual bool BeforeShut();

    virtual void LogReceive(const char* str) {}
    virtual void LogSend(const char* str) {}

	virtual INetClientModule* GetClusterModule();
    virtual MapEx<int, SquickStruct::ServerInfoReport>& GetWorldMap();

protected:
    void OnSocketMSEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

protected:

    //////////////////////////////////////////////////////////////////////////
	void OnSelectServerResultProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnWorldInfoProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

    //////////////////////////////////////////////////////////////////////////
    void Register(INet* pNet);
	void ServerReport();

private:
	INT64 mLastReportTime;
    MapEx<int, SquickStruct::ServerInfoReport> mWorldMap;

    ILoginNet_ServerModule* m_pLILoginNet_ServerModule;
    IElementModule* m_pElementModule;
    IKernelModule* m_pKernelModule;
    IClassModule* m_pClassModule;
    ILogModule* m_pLogModule;
	INetClientModule* m_pNetClientModule;
};

#endif