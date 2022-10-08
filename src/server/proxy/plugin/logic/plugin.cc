

#include "plugin.h"
#include "logic_module.h"



SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, ProxyLogicPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, ProxyLogicPlugin)
};


const int ProxyLogicPlugin::GetPluginVersion()
{
    return 0;
}

const std::string ProxyLogicPlugin::GetPluginName()
{
	return GET_CLASS_NAME(ProxyLogicPlugin);
}

void ProxyLogicPlugin::Install()
{

    REGISTER_MODULE(pPluginManager, IProxyLogicModule, ProxyLogicModule)

}

void ProxyLogicPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IProxyLogicModule, ProxyLogicModule)
}
