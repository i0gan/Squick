

#ifndef SQUICK_MASTERNET_HTTP_MODULE_H
#define SQUICK_MASTERNET_HTTP_MODULE_H

#include "squick/struct/struct.h"
#include "squick/base/platform.h"
#include "squick/base/kernel.h"
#include "squick/base/element.h"

#include <squick/base/http_server.h>

#include "if_http_server_module.h"
#include "../server/if_server_module.h"
#include "../logic/if_master_module.h"

class MasterNet_HttpServerModule
	: public IMasterNet_HttpServerModule
{
public:
	MasterNet_HttpServerModule(IPluginManager* p)
	{
        m_bIsUpdate = true;
		pPluginManager = p;
	}

	virtual bool Init();
	virtual bool Shut();

	virtual bool AfterInit();
	virtual bool Update();

protected:
	bool OnCommandQuery(SQUICK_SHARE_PTR<HttpRequest> req);

	WebStatus OnFilter(SQUICK_SHARE_PTR<HttpRequest> req);

private:
	IKernelModule* m_pKernelModule;
	IHttpServerModule* m_pHttpNetModule;
	IMasterNet_ServerModule* m_pMasterServerModule;
	IClassModule* m_pLogicClassModule;
	IElementModule* m_pElementModule;
};

#endif