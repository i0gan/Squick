#include "squick.h"
#include <squick/struct/struct.h>

int main(int argc, char* argv[])
{
	//std::cout << "__cplusplus:" << __cplusplus << std::endl;

	// 强制加载squick_struct依赖
	void *libLoad = (void *)&SquickStruct::_Ident_default_instance_;
	std::cout << libLoad << std::endl;


	std::vector<SQUICK_SHARE_PTR<PluginServer>> serverList;

	std::string strArgvList;
	for (int i = 0; i < argc; i++)
	{
		strArgvList += " ";
		strArgvList += argv[i];
	}

	if (argc == 1) // 如果没加参数运行
	{
		//IDE
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=MasterServer id=3 plugin=master_server.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=WorldServer id=7 plugin=world_server.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=LoginServer id=4 plugin=login_server.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=DBServer id=8 plugin=db_server.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=ProxyServer id=5 plugin=proxy_server.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=GameServer id=16001 plugin=game_server.xml")));
	}
	else
	{
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList)));
	}

	for (auto item : serverList)
	{
		item->SetBasicWareLoader(BasicPluginLoader);
		item->SetMidWareLoader(MidWareLoader);
		item->Start();
	}

	////////////////
	uint64_t nIndex = 0;
	while (true)
	{
		nIndex++;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		for (auto item : serverList)
		{
			item->Update();
		}
	}

	////////////////

	for (auto item : serverList)
	{
		item->Final();
	}

	serverList.clear();


	

    return 0;
}