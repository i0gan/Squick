#ifndef SQUICK_DB_NET_CLIENT_MODULE_H
#define SQUICK_DB_NET_CLIENT_MODULE_H

#include "squick/struct/struct.h"

#include "squick/base/net.h"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/base/log.h"

#include "squick/base/net_client.h"
#include "squick/base/security.h"

#include "server/world/plugin/client/if_master_module.h"
#include "server/world/plugin/server/if_server_module.h"
#include "if_world_module.h"
//#include "squick/base/world_logic.h"
//#include "squick/base/world_net_server.h"

class DBToWorldModule
	: public IDBToWorldModule
{
public:
	DBToWorldModule(IPluginManager* p)
	{
        m_bIsExecute = true;
		pPluginManager = p;
		mLastReportTime = 0;
	}

	virtual bool Init();
	virtual bool BeforeShut();
	virtual bool Shut();
	virtual bool Execute();
	virtual bool AfterInit();

protected:

	void OnSocketMSEvent(const SQUICK_SOCKET sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);
	
	void OnClientDisconnect(const SQUICK_SOCKET nAddress);
	
	void OnClientConnected(const SQUICK_SOCKET nAddress);

	virtual void LogServerInfo(const std::string& strServerInfo);


	void Register(INet* pNet);
	void ServerReport();
	void OnServerInfoProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);

	void InvalidMessage(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len);
private:
	INT64 mLastReportTime;

	ILogModule* m_pLogModule;
	IElementModule* m_pElementModule;
	IClassModule* m_pClassModule;
	INetClientModule* m_pNetClientModule;
	INetModule* m_pNetModule;
	ISecurityModule* m_pSecurityModule;
};

#endif