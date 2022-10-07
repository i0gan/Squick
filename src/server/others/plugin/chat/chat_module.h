

#ifndef SQUICK_CHAT_MODULE_H
#define SQUICK_CHAT_MODULE_H

#include <memory>
#include "squick/base/net.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"

#include "if_chat_module.h"
#include "squick/struct/protocol_define.h"
#include "server/game/plugin/server/if_server_module.h"
////////////////////////////////////////////////////////////////////////////


class ChatModule
    : public IChatModule
{
public:
	ChatModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual bool Init() override;
    virtual bool Shut() override;
    virtual bool Execute() override;

    virtual bool AfterInit() override;

private:
	void OnClientChatProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:

    //////////////////////////////////////////////////////////////////////////
    ILogModule* m_pLogModule;
	INetModule* m_pNetModule;
	IKernelModule* m_pKernelModule;
	IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
};
#endif
