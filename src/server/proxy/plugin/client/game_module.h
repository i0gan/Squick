

#ifndef SQUICK_PROXYSERVER_TO_GAME_MODULE_H
#define SQUICK_PROXYSERVER_TO_GAME_MODULE_H

#include <string>
#include <squick/struct/struct.h>
#include <squick/base/kernel.h>
#include <squick/base/net.h>
#include <squick/base/element.h>
#include <squick/base/log.h>
#include <squick/base/class.h>
#include <squick/base/net_client.h>


#include "if_game_module.h"
#include "../server/if_server_module.h"
#include "../logic/if_logic_module.h"

class ProxyServerToGameModule : public IProxyServerToGameModule
{
public:

    ProxyServerToGameModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Update();

    virtual bool AfterInit();

protected:

    void OnSocketGSEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

    void Register(INet* pNet);

    void OnAckEnterGame(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
    void LogServerInfo(const std::string& strServerInfo);

	void Transport(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

private:

    ILogModule* m_pLogModule;
    IKernelModule* m_pKernelModule;
    IProxyServerNet_ServerModule* m_pProxyServerNet_ServerModule;
    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
	INetClientModule* m_pNetClientModule;

};

#endif