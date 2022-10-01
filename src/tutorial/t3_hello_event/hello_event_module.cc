

#include "HelloEventModule.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"
#include "NFComm/NFPluginModule/NFIEventModule.h"

bool HelloEventModule::Init()
{

	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pEventModule = pPluginManager->FindModule<NFIEventModule>();
	m_pScheduleModule = pPluginManager->FindModule<NFIScheduleModule>();


	std::cout << "Hello, world3, Init" << std::endl;

	return true;
}

int HelloEventModule::OnEvent(const Guid& self, const int event, const DataList& arg)
{
	std::cout << "OnEvent EventID: " << event << " self: " << self.nData64 << " argList: " << arg.Int(0) << " " << " " << arg.String(1) << std::endl;

	m_pKernelModule->SetPropertyInt(self, "Hello", arg.Int(0));
	m_pKernelModule->SetPropertyString(self, "Hello", arg.String(1));

	return 0;
}

int HelloEventModule::OnHeartBeat(const Guid& self, const std::string& heartBeat, const float time, const int count)
{

	int64_t unNowTime = NFGetTimeMS();

	std::cout << self.ToString() + " heartBeat: " << time << " Count: " << count << "  TimeDis: " << unNowTime - mLastTime << std::endl;

	mLastTime = unNowTime;

	return 0;
}

int HelloEventModule::OnClassCallBackEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT event, const DataList& arg)
{
	
	std::cout << "OnClassCallBackEvent ClassName: " << className << " ID: " << self.nData64 << " Event: " << event << std::endl;

	if (event == COE_CREATE_HASDATA)
	{
		m_pEventModule->AddEventCallBack(self, 1, this, &HelloEventModule::OnEvent);

		m_pScheduleModule->AddSchedule(self, "OnHeartBeat", this, &HelloEventModule::OnHeartBeat, 5.0f, 10 );

		mLastTime = NFGetTimeMS();
	}

	return 0;
}

int HelloEventModule::OnPropertyCallBackEvent( const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const int64_t reason)
{
	
	std::cout << "OnPropertyCallBackEvent Property: " << propertyName << " OldValue: " << oldVar.GetInt() << " NewValue: " << newVar.GetInt() << std::endl;

	return 0;
}

int HelloEventModule::OnPropertyStrCallBackEvent( const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const int64_t reason)
{
	
	std::cout << "OnPropertyCallBackEvent Property: " << propertyName << " OldValue: " << oldVar.GetString() << " NewValue: " << newVar.GetString() << std::endl;

	return 0;
}

bool HelloEventModule::AfterInit()
{
	
	std::cout << "Hello, world3, AfterInit" << std::endl;

	m_pKernelModule->CreateScene(1);

	m_pKernelModule->AddClassCallBack(SquickProtocol::Player::ThisName(), this, &HelloEventModule::OnClassCallBackEvent);
	m_pScheduleModule->AddSchedule(Guid(), "OnHeartBe22222", this, &HelloEventModule::OnHeartBeat, 6.0f, 10 );

	
	NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->CreateObject(Guid(0, 10), 1, 0, SquickProtocol::Player::ThisName(), "", DataList::Empty());
	if (!pObject)
	{
		return false;
	}

	pObject->GetPropertyManager()->AddProperty(pObject->Self(), "Hello", TDATA_STRING);
	pObject->GetPropertyManager()->AddProperty(pObject->Self(), "World", TDATA_INT);

	pObject->AddPropertyCallBack("Hello", this, &HelloEventModule::OnPropertyStrCallBackEvent);
	pObject->AddPropertyCallBack("World", this, &HelloEventModule::OnPropertyCallBackEvent);

	pObject->SetPropertyString("Hello", "hello,World");
	pObject->SetPropertyInt("World", 1111);


	m_pEventModule->DoEvent(pObject->Self(), 1, DataList() << int(100) << "200");

	return true;
}

bool HelloEventModule::Execute()
{
	
	//std::cout << "Hello, world3, Execute" << std::endl;

	return true;
}

bool HelloEventModule::BeforeShut()
{
	
	std::cout << "Hello, world3, BeforeShut" << std::endl;

	m_pKernelModule->DestroyAll();

	return true;
}

bool HelloEventModule::Shut()
{
	
	std::cout << "Hello, world3, Shut" << std::endl;

	return true;
}
