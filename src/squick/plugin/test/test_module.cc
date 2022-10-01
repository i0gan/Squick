

//#include "third_party/googletest-release-1.8.0/googletest/include/gtest/gtest.h"
#include "test_module.h"

bool TestModule::Awake()
{
	int argc = 0;
	char* c = new char[1];
	//::testing::GTEST_FLAG(output) = "xml:hello.xml";
	//::testing::InitGoogleTest(&argc, &c);
	std::cout << "我已经运行了" << std::endl;
	std::list<IModule*> xModules = pPluginManager->Modules(); // 获取全部模块，
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		std::cout << "尝试查找：" << pModule->name  << std::endl;
		if(nullptr != pTestModule) {
			pTestModule->Awake();
		}else {
			std::cout << "查找模块出错，为空"  << std::endl;
		}
		
	}

	return true;
}

bool TestModule::Init()
{
	//find all plugins and all modules, then check whether they have a tester
	//if any module have't a tester for it then  can not start the application
	//this is a rule for NF's world to keep high quality code under TDD

	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->Init();
	}

    return true;
}

bool TestModule::AfterInit()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->AfterInit();
	}

	return true;
}

bool TestModule::CheckConfig()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->CheckConfig();
	}

	return true;
}

bool TestModule::ReadyExecute()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->ReadyExecute();
	}

	return true;
}

bool TestModule::Execute()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->Execute();
	}

    return true;
}

bool TestModule::BeforeShut()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->BeforeShut();
	}

	return true;
}

bool TestModule::Shut()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->Shut();
	}

	return true;
}

bool TestModule::Finalize()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->Finalize();
	}

	return true;
}

bool TestModule::OnReloadPlugin()
{
	std::list<IModule*> xModules = pPluginManager->Modules();
	for (auto it : xModules)
	{
		IModule* pModule = it;
		IModule* pTestModule = pPluginManager->FindTestModule(pModule->name);
		pTestModule->OnReloadPlugin();
	}

	return true;
}

int TestModule::Factorial(int n)
{
	if (1 == n)
	{
		return 1;
	}

	return n*Factorial(n-1);
}

// 测试用例
/*
TEST(FactorialTest, HandlesPositiveInput) {
    EXPECT_EQ(1, this->Factorial(1));
    EXPECT_EQ(2, this->Factorial(2));
    EXPECT_EQ(6, this->Factorial(3));
    EXPECT_EQ(40320, this->Factorial(8));
}
*/