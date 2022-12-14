#pragma once

#include <map>
#include <iostream>

#include <squick/struct/struct.h>
#include <squick/core/platform.h>
#include <squick/plugin/kernel/i_kernel_module.h>
#include <squick/plugin/config/i_element_module.h>
#include <squick/plugin/net/i_http_server_module.h>
#include "i_http_server_module.h"
#include "../client/i_master_module.h"
#include "../server/i_server_module.h"


class LoginNet_HttpServerModule
	: public ILoginNet_HttpServerModule
{
public:
	LoginNet_HttpServerModule(IPluginManager* p)
	{
		pPluginManager = p;
        m_bIsUpdate = true;
	}

	virtual bool Start();
	virtual bool Destory();

	virtual bool AfterStart();
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