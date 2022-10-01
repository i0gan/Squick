#include "security_module.h"
#include "squick/struct/protocol_define.h"
#include "squick/base/event.h"

bool SecurityModule::Init()
{
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	
	return true;
}

bool SecurityModule::AfterInit()
{
	SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Security::ThisName());
	if (xLogicClass)
	{
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList();
		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];
			const std::string& strSecurityData = m_pElementModule->GetPropertyString(strId, SquickProtocol::Security::SecurityData());

		}
	}

	return true;
}

const std::string SecurityModule::GetSecurityKey(const std::string & account)
{
	return account;
}

bool SecurityModule::VerifySecurityKey(const std::string & account, const std::string & strSecurityKey)
{
	//you would implement this function by yourself
	//if (account == strSecurityKey)
	{
		return true;
	}

	return false;
}

std::string SecurityModule::EncodeMsg(const std::string & account, const std::string & strSecurityKey, const int nMessageID, const char * strMessageData, const int len)
{
	return std::string(strMessageData, len);
}

std::string SecurityModule::EncodeMsg(const std::string & account, const std::string & strSecurityKey, const int nMessageID, const std::string & strMessageData)
{
	return strMessageData;
}

std::string SecurityModule::DecodeMsg(const std::string & account, const std::string & strSecurityKey, const int nMessageID, const char * strMessageData, const int len)
{
	return std::string(strMessageData, len);
}

std::string SecurityModule::DecodeMsg(const std::string & account, const std::string & strSecurityKey, const int nMessageID, const std::string & strMessageData)
{
	return strMessageData;
}

bool SecurityModule::Shut()
{

	return true;
}

bool SecurityModule::Execute()
{
	return true;
}
