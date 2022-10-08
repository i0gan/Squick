
#include "plugin.h"
#include "game_module.h"
#include "world_module.h"
//
//

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, ProxyServerNet_ClientPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, ProxyServerNet_ClientPlugin)
};



const int ProxyServerNet_ClientPlugin::GetPluginVersion()
{
    return 0;
}

const std::string ProxyServerNet_ClientPlugin::GetPluginName()
{
	return GET_CLASS_NAME(ProxyServerNet_ClientPlugin);
}

void ProxyServerNet_ClientPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IProxyServerToWorldModule, ProxyServerToWorldModule)
    REGISTER_MODULE(pPluginManager, IProxyServerToGameModule, ProxyServerToGameModule)
}

void ProxyServerNet_ClientPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IProxyServerToGameModule, ProxyServerToGameModule)
    UNREGISTER_MODULE(pPluginManager, IProxyServerToWorldModule, ProxyServerToWorldModule)
}