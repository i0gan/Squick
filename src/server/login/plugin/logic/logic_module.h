
#ifndef SQUICK_LOGINLOGIC_MODULE_H
#define SQUICK_LOGINLOGIC_MODULE_H

#include "squick/struct/struct.h"
#include "squick/core/map.h"
#include "squick/base/kernel.h"
//#include "squick/base/login_net_server.h"
#include "squick/base/log.h"
#include "squick/base/net.h"

#include "if_logic_module.h"
#include "server/db/plugin/logic/if_account_redis_module.h"



class LoginLogicModule
    : public ILoginLogicModule
{
public:
    LoginLogicModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool ReadyExecute();
    virtual bool Execute();

    virtual bool AfterInit();

    virtual void OnLoginProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:
	INetModule* m_pNetModule;
	ILogModule* m_pLogModule;
	IAccountRedisModule* m_pAccountRedisModule;
private:
};

#endif