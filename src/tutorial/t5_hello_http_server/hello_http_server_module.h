

#ifndef SQUICK_HELLO_WORLD_H
#define SQUICK_HELLO_WORLD_H

#include <iostream>

#include "squick/core/object.h"
#include "squick/core/data_list.h"
#include "squick/struct/define.pb.h"
#include "squick/base/module.h"
#include "squick/base/platform.h"
#include "squick/base/http_client.h"
#include "squick/base/http_server.h"
#include "squick/base/ws.h"
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/schedule.h"
#include "squick/base/net.h"


class IHelloWorld5
	: public IModule
{

};

class HelloWorld5
    : public IHelloWorld5
{
public:
    HelloWorld5(IPluginManager* p)
    {
	m_bIsUpdate = true;
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool AfterInit();

    virtual bool Update();

    virtual bool BeforeShut();
    virtual bool Shut();

protected:
	bool OnCommandQuery(SQUICK_SHARE_PTR<HttpRequest> req);

	WebStatus OnFilter(SQUICK_SHARE_PTR<HttpRequest> req);

	int OnHeartBeat(const Guid& self, const std::string& heartBeat, const float time, const int count);

	void OnGetCallBack(const Guid id, const int state_code, const std::string& strRespData);
	void OnPostCallBack(const Guid id, const int state_code, const std::string& strRespData, const std::string& strMemoData);

    void OnWebSocketTestProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnTCPEvent(const SQUICK_SOCKET fd, const SQUICK_NET_EVENT event, INet* pNet);

	void OnLoginProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

private:

	IClassModule* m_pLogicClassModule;
	IHttpServerModule* m_pHttpNetModule;
	IHttpClientModule* m_pHttpClientModule;
	IWSModule* m_pWSModule;
	IElementModule* m_pElementModule;
	IScheduleModule* m_pScheduleModule;
	INetModule* m_pNetModule;
};

#endif
