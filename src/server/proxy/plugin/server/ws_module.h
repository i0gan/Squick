
#ifndef SQUICK_PROXYSERVER_SERVER_WS_MODULE_H
#define SQUICK_PROXYSERVER_SERVER_WS_MODULE_H

#include "squick/core/consistent_hash.h"
#include "squick/struct/struct.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"
#include "squick/base/log.h"
#include "squick/base/ws.h"
#include "squick/base/element.h"
#include "squick/base/net_client.h"
#include "squick/base/security.h"

#include "if_ws_module.h"
#include "../client/if_world_module.h"
#include "../client/if_game_module.h"

class ProxyServerNet_WSModule : public IProxyServerNet_WSModule
{
public:
    ProxyServerNet_WSModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();

protected:

    void OnSocketClientEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

    void OnClientDisconnect(const SQUICK_SOCKET nAddress);
    void OnClientConnected(const SQUICK_SOCKET nAddress);

    void OnWebSocketTestProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:

    MapEx<Guid, SQUICK_SOCKET> mxClientIdent;
protected:
    INetClientModule* m_pNetClientModule;
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
	IWSModule* m_pWSModule;
	ISecurityModule* m_pSecurityModule;
	IProxyServerToWorldModule* m_pProxyToWorldModule;
};

#endif