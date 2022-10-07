
#include "hello_plugin_module.h"

bool HelloWorld1::Init()
{
	std::cout << typeid(HelloWorld1).name() << std::endl;

    
    std::cout << "Hello, world1, Init" << std::endl;

    return true;
}

bool HelloWorld1::AfterInit()
{
    
    std::cout << "Hello, world1, AfterInit" << std::endl;


	DataList dataList;
	dataList.Add("1");
	dataList.AddFloat(2.0f);
	dataList.AddObject(Guid(3,3));
	dataList.AddVector2(Vector2(4.0f, 4.0f));

	for (int i = 0; i < dataList.GetCount(); ++i)
	{
		std::cout << dataList.ToString(i) << std::endl;
	}


    return true;
}

// Update
bool HelloWorld1::Update()
{
    
    //std::cout << "Hello, world1, Update" << std::endl;

    return true;
}

bool HelloWorld1::BeforeShut()
{
    std::cout << "Hello, world1, BeforeShut1111" << std::endl;

    system("PAUSE");

    
    std::cout << "Hello, world1, BeforeShut" << std::endl;

    return true;
}

bool HelloWorld1::Shut()
{
    
    std::cout << "Hello, world1, Shut" << std::endl;

    return true;
}
