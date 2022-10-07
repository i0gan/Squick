

#include "plugin.h"
#include "game_server_module.h"
#include "scene_process_module.h"
#include "property_module.h"
#include "property_config_module.h"
#include "npc_refresh_module.h"
#include "sync_pos_module.h"
#include "create_role_module.h"


#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, GameServerPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, GameServerPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int GameServerPlugin::GetPluginVersion()
{
    return 0;
}

const std::string GameServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(GameServerPlugin);
}

void GameServerPlugin::Install()
{

    REGISTER_MODULE(pPluginManager, IGameServerModule, GameServerModule)
    REGISTER_MODULE(pPluginManager, ISceneProcessModule, SceneProcessModule)
    REGISTER_MODULE(pPluginManager, IPropertyModule, PropertyModule)
    REGISTER_MODULE(pPluginManager, IPropertyConfigModule, PropertyConfigModule)
	REGISTER_MODULE(pPluginManager, INPCRefreshModule, NPCRefreshModule)
	REGISTER_MODULE(pPluginManager, ISyncPosModule, SyncPosModule)
	REGISTER_MODULE(pPluginManager, ICreateRoleModule, CreateRoleModule)
}

void GameServerPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, ICreateRoleModule, CreateRoleModule)
	UNREGISTER_MODULE(pPluginManager, ISyncPosModule, NFSyncModule)
	UNREGISTER_MODULE(pPluginManager, INPCRefreshModule, NPCRefreshModule)
	UNREGISTER_MODULE(pPluginManager, IPropertyConfigModule, PropertyConfigModule)
    UNREGISTER_MODULE(pPluginManager, IPropertyModule, PropertyModule)
    UNREGISTER_MODULE(pPluginManager, ISceneProcessModule, SceneProcessModule)
    UNREGISTER_MODULE(pPluginManager, IGameServerModule, GameServerModule)
}
