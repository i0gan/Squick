
#include "hello_navigation.h"

bool HelloWorld6::Init()
{ 

    std::cout << "Hello, world, Init" << std::endl;

    return true;
}

bool HelloWorld6::AfterInit()
{
	m_pNavigationModule = pPluginManager->FindModule<INavigationModule>();

	int sceneId = 1;
	Vector3 start(0, 0, 0);
	Vector3 end(23, 0, 5);
	vector<Vector3> pathResult;

	int ret = m_pNavigationModule->FindPath(sceneId, start, end, pathResult);
	if (ret > 0)
	{
		std::cout << "FindPath Success" << std::endl;
	}
	else
	{
		std::cout << "FindPath Fail" << std::endl;
	}
    return true;
}

bool HelloWorld6::Execute()
{
    return true;
}

bool HelloWorld6::BeforeShut()
{
    
    std::cout << "Hello, world2, BeforeShut" << std::endl;

    return true;
}

bool HelloWorld6::Shut()
{
    
    std::cout << "Hello, world2, Shut" << std::endl;

    return true;
}