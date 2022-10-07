#include "squick.h"

int main(int argc, char* argv[])
{
	//std::cout << "__cplusplus:" << __cplusplus << std::endl;

	std::vector<SQUICK_SHARE_PTR<PluginServer>> serverList;

	std::string strArgvList;
	for (int i = 0; i < argc; i++)
	{
		strArgvList += " ";
		strArgvList += argv[i];
	}

	if (argc == 1)
	{
		//IDE
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=MasterServer ID=3 plugin=plugin.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=WorldServer ID=7 plugin=plugin.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=LoginServer ID=4 plugin=plugin.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=DBServer ID=8 plugin=plugin.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=ProxyServer ID=5 plugin=plugin.xml")));
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList + " server=GameServer ID=16001 plugin=plugin.xml")));
	}
	else
	{
		serverList.push_back(SQUICK_SHARE_PTR<PluginServer>(SQUICK_NEW PluginServer(strArgvList)));
	}

	for (auto item : serverList)
	{
		item->SetBasicWareLoader(BasicPluginLoader);
		item->SetMidWareLoader(MidWareLoader);
		item->Init();
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