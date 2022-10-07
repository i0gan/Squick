
#ifndef SQUICK_PROXYLOGIC_MODULE_H
#define SQUICK_PROXYLOGIC_MODULE_H

#include "squick/core/map.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"
#include "squick/base/log.h"
#include "squick/base/net.h"
#include "squick/base/net_client.h"


#include "if_logic_module.h"
class ProxyLogicModule
    : public IProxyLogicModule
{
public:
    ProxyLogicModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();

protected:

	void OnLagTestProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:
    IClassModule* m_pClassModule;
    IKernelModule* m_pKernelModule;
	INetModule* m_pNetModule;
	INetClientModule* m_pNetClientModule;
private:
};

#endif