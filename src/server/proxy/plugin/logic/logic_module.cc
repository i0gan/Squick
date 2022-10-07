
#include "plugin.h"
#include "logic_module.h"

bool ProxyLogicModule::Init()
{

    return true;
}

bool ProxyLogicModule::Shut()
{
    return true;
}

bool ProxyLogicModule::Execute()
{


    return true;
}


bool ProxyLogicModule::AfterInit()
{
    m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
    m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pNetModule = pPluginManager->FindModule<INetModule>();
	m_pNetClientModule = pPluginManager->FindModule<INetClientModule>();


	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_LAG_TEST, this, &ProxyLogicModule::OnLagTestProcess);

    return true;
}

void ProxyLogicModule::OnLagTestProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	std::string msgDatag(msg, len);
	m_pNetModule->SendMsgWithOutHead(SquickStruct::EGameMsgID::ACK_GATE_LAG_TEST, msgDatag, sockIndex);

	//TODO improve performance
	NetObject* pNetObject = m_pNetModule->GetNet()->GetNetObject(sockIndex);
	if (pNetObject)
	{
		const int gameID = pNetObject->GetGameID();
		m_pNetClientModule->SendByServerIDWithOutHead(gameID, msgID, msgDatag);
	}
}
