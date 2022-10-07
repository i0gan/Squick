

#ifndef SQUICK_LOGIN_NET_HTTP_MODULE_H
#define SQUICK_LOGIN_NET_HTTP_MODULE_H

#include <map>
#include <iostream>

#include "squick/struct/struct.h"
#include "squick/base/platform.h"
#include "squick/base/kernel.h"
#include "squick/base/element.h"
#include "squick/base/http_server.h"

#include "if_http_server_module.h"
#include "../client/if_master_module.h"
#include "../server/if_server_module.h"


class LoginNet_HttpServerModule
	: public ILoginNet_HttpServerModule
{
public:
	LoginNet_HttpServerModule(IPluginManager* p)
	{
		pPluginManager = p;
        m_bIsUpdate = true;
	}

	virtual bool Init();
	virtual bool Shut();

	virtual bool AfterInit();
	virtual bool Update();

protected:
	bool OnLogin(SQUICK_SHARE_PTR<HttpRequest> req);
	bool OnWorldView(SQUICK_SHARE_PTR<HttpRequest> req);
	bool OnWorldSelect(SQUICK_SHARE_PTR<HttpRequest>req);

	bool OnCommonQuery(SQUICK_SHARE_PTR<HttpRequest> req);

	WebStatus OnFilter(SQUICK_SHARE_PTR<HttpRequest> req);

	std::string GetUserID(SQUICK_SHARE_PTR<HttpRequest> req);
	std::string GetUserJWT(SQUICK_SHARE_PTR<HttpRequest> req);
	bool CheckUserJWT(const std::string & user, const std::string & jwt);


	std::map<std::string, std::string> mToken;

private:
	INetClientModule* m_pNetClientModule;
	IKernelModule* m_pKernelModule;
	IHttpServerModule* m_pHttpNetModule;
	ILoginNet_ServerModule* m_pLoginServerModule;
	ILoginToMasterModule* m_pLoginToMasterModule;
	IClassModule* m_pLogicClassModule;
	IElementModule* m_pElementModule;
};

#endif