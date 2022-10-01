

#include "auto_broadcast_module.h"
#include "scene_auto_broadcast_module.h"
#include "server_module.h"
#include "game_manager_module.h"
#include "plugin.h"
//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, GameServerNet_ServerPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, GameServerNet_ServerPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int GameServerNet_ServerPlugin::GetPluginVersion()
{
    return 0;
}

const std::string GameServerNet_ServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(GameServerNet_ServerPlugin);
}

void GameServerNet_ServerPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, IGameManagerModule, GameManagerModule)
	REGISTER_MODULE(pPluginManager, IGameServerNet_ServerModule, GameServerNet_ServerModule)
	REGISTER_MODULE(pPluginManager, IAutoBroadcastModule, AutoBroadcastModule)
	REGISTER_MODULE(pPluginManager, ISceneAutoBroadcastModule, SceneAutoBroadcastModule)
}

void GameServerNet_ServerPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, ISceneAutoBroadcastModule, SceneAutoBroadcastModule)
	UNREGISTER_MODULE(pPluginManager, IAutoBroadcastModule, AutoBroadcastModule)
	UNREGISTER_MODULE(pPluginManager, IGameServerNet_ServerModule, GameServerNet_ServerModule)
	UNREGISTER_MODULE(pPluginManager, IGameManagerModule, GameManagerModule)
}